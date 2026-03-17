import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CompressedImage
from geometry_msgs.msg import Point
import cv2
import numpy as np
import mediapipe as mp

class PersonTrackerNode(Node):
    def __init__(self):
        super().__init__('person_tracker_node')
        model_path = "/home/ubuntu/project_ws/src/person_tracker_node/person_tracker_node/pose_landmarker_lite.task"
        
        # 1. ROS 2 Topic 설정
        # /image_out/compressed 토픽 구독
        self.subscription = self.create_subscription(
            CompressedImage, 
            '/image_out/compressed', 
            self.image_callback, 
            10)
        
        # 사람 중심점 발행 (Point 메시지)
        self.publisher = self.create_publisher(Point, '/point_out', 10)

        # 2. MediaPipe Pose 설정
        try:
          BaseOptions = mp.tasks.BaseOptions
          self.PoseLandmarker = mp.tasks.vision.PoseLandmarker
          self.options = mp.tasks.vision.PoseLandmarkerOptions(
            base_options=BaseOptions(model_asset_path=model_path),
            running_mode=mp.tasks.vision.RunningMode.IMAGE)
          self.landmarker = self.PoseLandmarker.create_from_options(self.options)
          self.get_logger().info("MediaPipe Landmarker initialized.")
        except Exception as e:
          self.get_logger().error(f"Failed to initialize: {str(e)}")
          raise e

        # 3. CLAHE 객체 생성 (대비 제한 2.0, 그리드 8x8)
        self.clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))

        self.get_logger().info('Person Tracker Node has been started (Depth: Right Side)')

    def image_callback(self, msg):
        # A. 압축 이미지 디코딩
        np_arr = np.frombuffer(msg.data, np.uint8)
        frame = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)

        if frame is None:
            return

        # B. Depth 카메라 부분 추출 (오른쪽 절반)
        h, w, _ = frame.shape
        # [세로 전체, 가로 중간부터 끝까지]
        depth_roi = frame[:, w//2:] 

        # C. Median Filter (3x3) - 노이즈 제거
        filtered = cv2.medianBlur(depth_roi, 3)

        # D. CLAHE 적용 (Y채널만)
        # YUV 색공간으로 변환하여 밝기(Y) 채널만 선명하게 만듦
        yuv = cv2.cvtColor(filtered, cv2.COLOR_BGR2YUV)
        yuv[:, :, 0] = self.clahe.apply(yuv[:, :, 0])
        processed_img = cv2.cvtColor(yuv, cv2.COLOR_YUV2BGR)

        # E. MediaPipe 추론 (RGB 이미지 입력 필요)
        rgb_img = cv2.cvtColor(processed_img, cv2.COLOR_BGR2RGB)
        mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=rgb_img)
        results = self.landmarker.detect(mp_image)
        point_msg = Point()
        # F. 11, 12, 23, 24번 랜드마크를 이용한 중심점 계산
        if results.pose_landmarks:
            landmarks = results.pose_landmarks[0]
            
            # 인덱스 정의: 11(L.Shoulder), 12(R.Shoulder), 23(L.Hip), 24(R.Hip)
            target_indices = [11, 12, 23, 24]
            
            sum_x = 0.0
            sum_y = 0.0
            valid_points = 0

            for idx in target_indices:
                lm = landmarks[idx]
                # MediaPipe는 가시성(visibility) 점수도 제공합니다.
                sum_x += lm.x
                sum_y += lm.y
                valid_points += 1

            if valid_points > 0:
                # 정규화된 중심 좌표 (0.0 ~ 1.0)
                avg_x = sum_x / valid_points
                avg_y = sum_y / valid_points

                # ROS 2 메시지 발행
                point_msg.x = avg_x
                point_msg.y = avg_y
                point_msg.z = 0.0 # 필요 시 해당 좌표의 실제 거리값 할당
                
        else:
          point_msg.x = -1.0
          point_msg.y = -1.0
          point_msg.z = 0.0
        self.publisher.publish(point_msg)
    def visualize(self, img, x, y):
        cv2.circle(img, (x, y), 8, (0, 255, 0), -1)
        cv2.putText(img, "Center", (x + 10, y), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
        cv2.imshow("Depth ROI Tracking", img)
        cv2.waitKey(1)

def main(args=None):
    rclpy.init(args=args)
    node = PersonTrackerNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        cv2.destroyAllWindows()
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
