import profile

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CompressedImage
from geometry_msgs.msg import Point
from std_msgs.msg import Float32
import cv2
import pyrealsense2 as rs
import numpy as np

class D435Node(Node):
    def __init__(self):
        super().__init__('d435_node')
        
        self.image_pub = self.create_publisher(CompressedImage, '/image_out/compressed', 10)
        self.depth_sub = self.create_subscription(Point, '/depth_request', self.depth_callback, 10)
        self.depth_pub = self.create_publisher(Point, '/depth_response', 10)
        self.cds_sub = self.create_subscription(Float32, '/cds', self.cds_callback, 10)

        self.pipeline = rs.pipeline()
        self.config = rs.config()
        
        self.width = 640
        self.height = 480

        self.config.enable_stream(rs.stream.depth, self.width, self.height, rs.format.z16, 15)
        self.config.enable_stream(rs.stream.color, self.width, self.height, rs.format.bgr8, 15)
        self.config.enable_stream(rs.stream.infrared, 1, self.width, self.height, rs.format.y8, 15)
        selection = self.pipeline.start(self.config)
        device = selection.get_device()
        depth_sensor = device.first_depth_sensor()
        if depth_sensor.supports(rs.option.emitter_enabled):
            depth_sensor.set_option(rs.option.emitter_enabled, 0)
        
        color_prof = selection.get_stream(rs.stream.color).as_video_stream_profile()
        ir_prof = selection.get_stream(rs.stream.infrared, 1).as_video_stream_profile()
        depth_prof = selection.get_stream(rs.stream.depth).as_video_stream_profile()
        
        # [수정된 부분 1] 개별 변수로 저장하여 구조체 선언 에러 방지
        self.depth_intrinsics = depth_prof.get_intrinsics()
        self.color_intrinsics = color_prof.get_intrinsics()
        self.ir_intrinsics = ir_prof.get_intrinsics()
        
        self.c2ir = color_prof.get_extrinsics_to(ir_prof)
        self.rgb_corners = np.array([[0, 0], [self.width-1, 0], [self.width-1, self.height-1], [0, self.height-1]], dtype=np.float32)
        self.cds = 100
        webcam_path = "/dev/v4l/by-id/usb-Innomaker_Innomaker-U20CAM-1080p-S1_SN0001-video-index0"
        self.cap = cv2.VideoCapture(webcam_path)
        
        if not self.cap.isOpened():
            self.get_logger().error(f"Can't open webcam: {webcam_path}")
            self.cap = None

        self.timer = self.create_timer(0.05, self.timer_callback)
        self.get_logger().info("D435 Node started!")

    def timer_callback(self):
        try:
            frames = self.pipeline.wait_for_frames()
            if self.cds < 30:
                ir_frame = frames.get_infrared_frame(1)
                depth_frame = frames.get_depth_frame()
                if not ir_frame:
                    depth_color_frame = np.zeros((self.height, self.width, 3), dtype=np.uint8)
                else:
                    ir_mapped_pts = []
                    for (u, v) in self.rgb_corners:
                        z = depth_frame.get_distance(int(u), int(v))
                        if z == 0: z = 3.0
                        # [수정된 부분 2] self.color_intrinsics 사용
                        pt_color = rs.rs2_deproject_pixel_to_point(self.color_intrinsics, [u, v], z)
                        pt_ir = rs.rs2_transform_point_to_point(self.c2ir, pt_color)
                        # [수정된 부분 3] self.ir_intrinsics 사용
                        u_ir, v_ir = rs.rs2_project_point_to_pixel(self.ir_intrinsics, pt_ir)
                        ir_mapped_pts.append((u_ir, v_ir))
                    ir_mapped_pts = np.array(ir_mapped_pts, dtype=np.float32)
                    M = cv2.getPerspectiveTransform(self.rgb_corners, ir_mapped_pts)
                    ir_aligned = cv2.warpPerspective(np.asanyarray(ir_frame.get_data()), M, (self.width, self.height))
                    depth_color_frame = cv2.cvtColor(ir_aligned, cv2.COLOR_GRAY2BGR)
            else:
                color_frame = frames.get_color_frame()
                if not color_frame:
                    depth_color_frame = np.zeros((self.height, self.width, 3), dtype=np.uint8)
                else:
                    depth_color_frame = np.asanyarray(color_frame.get_data())
            
            if self.cap is not None:
                ret, webcam_frame = self.cap.read()
                if ret:
                    webcam_resized = cv2.resize(webcam_frame, (self.width, self.height))
                else:
                    webcam_resized = np.zeros((self.height, self.width, 3), dtype=np.uint8)
            else:
                webcam_resized = np.zeros((self.height, self.width, 3), dtype=np.uint8)
                
            combined_image = np.hstack((webcam_resized, depth_color_frame))

            msg = CompressedImage()
            msg.header.stamp = self.get_clock().now().to_msg()
            msg.header.frame_id = "image_out/compressed"
            msg.format = "jpeg"
            msg.data = cv2.imencode('.jpg', combined_image, [cv2.IMWRITE_JPEG_QUALITY, 80])[1].tobytes()
            
            self.image_pub.publish(msg)

        except Exception as e:
            self.get_logger().error(f"Error occured: {e}")

    def depth_callback(self, msg):
        try:
            u, v = int(msg.x * self.width), int(msg.y * self.height)
            u = np.clip(u, 0, self.width - 1)
            v = np.clip(v, 0, self.height - 1)
            frames = self.pipeline.wait_for_frames()
            depth_frame = frames.get_depth_frame()
            if not depth_frame:
                return
            depth_sum = 0
            count = 0
            for i in range(u-1, u+2):
                for j in range(v-1, v+2):
                    if 0 <= i < self.width and 0 <= j < self.height:
                        dist = depth_frame.get_distance(i, j)
                        if dist > 0:
                            depth_sum += dist
                            count += 1
            avg_depth = depth_sum / count if count > 0 else 0.0
            
            # [수정된 부분 4] 숨은 버그 픽스 (self.depth_intrinsics 로 변경)
            fx = self.depth_intrinsics.fx
            cx = self.depth_intrinsics.ppx
            angle_rad = np.arctan((u - cx) / fx)
            
            res_msg = Point()
            res_msg.x = float(avg_depth)
            res_msg.y = float(angle_rad)
            self.depth_pub.publish(res_msg)
            self.get_logger().info(f"Input({msg.x:.2f}, {msg.y:.2f}) -> Dist: {avg_depth:.2f}m, Angle: {np.degrees(angle_rad):.2f}")
        except Exception as e:
            self.get_logger().error(f"Depth Callback Error: {e}")
            
    def cds_callback(self, msg):
        self.cds = msg.data
        self.get_logger().info(f"CDS updated: {self.cds}")
        
def main(args=None):
    rclpy.init(args=args)
    node = D435Node()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.pipeline.stop()
        if node.cap is not None:
            node.cap.release()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
