import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CompressedImage
from geometry_msgs.msg import Point
import cv2
import pyrealsense2 as rs
import numpy as np

class D435Node(Node):
    def __init__(self):
        super().__init__('d435_node')
        
        self.image_pub = self.create_publisher(CompressedImage, '/image_out/compressed', 10)
        self.subscription = self.create_subscription(Point, '/depth_request', self.depth_callback, 10)

        self.pipeline = rs.pipeline()
        self.config = rs.config()

        self.config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 15)
        self.config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 15)
        self.pipeline.start(self.config)
        
        self.colorizer = rs.colorizer()

        webcam_path = "/dev/v4l/by-id/usb-Innomaker_Innomaker-U20CAM-1080p-S1_SN0001-video-index0"
        self.cap = cv2.VideoCapture(webcam_path)
        
        if not self.cap.isOpened():
            self.get_logger().error(f"Can't open webcam: {webcam_path}")

        self.timer = self.create_timer(0.1, self.timer_callback)
        self.get_logger().info("D435 Node started!")

    def timer_callback(self):
        try:
            frames = self.pipeline.wait_for_frames()
            color_frame = frames.get_color_frame()
            if not color_frame:
                return

            depth_color_frame = np.asanyarray(color_frame.get_data())

            ret, webcam_frame = self.cap.read()
            if not ret:
                return

            webcam_resized = cv2.resize(webcam_frame, (640, 480))
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
        self.get_logger().info(f"Depth request: x={msg.x}, y={msg.y}")

def main(args=None):
    rclpy.init(args=args)
    node = D435Node()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.pipeline.stop()
        node.cap.release()
        rclpy.shutdown()

if __name__ == '__main__':
    main()