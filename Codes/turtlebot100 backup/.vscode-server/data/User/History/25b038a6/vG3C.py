import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CompressedImage
import cv2
import pyrealsense2 as rs
import numpy as np
import cv_bridge
import mediapipe as mp
from mediapipe.tasks import python
from mediapipe.tasks.python import vision
from rclpy.node import Node
from rclpy.executors import MultiThreadedExecutor
from rclpy.callback_groups import ReentrantCallbackGroup

model_path = '/home/turtlebot100/turtlebot3_ws/src/d435_node/d435_node/pose_landmarker_lite.task'
points = [0, 11, 12, 13, 14, 15, 16, 23, 24, 25, 26, 27, 28]

class D435Node(Node):
  def __init__(self):
    super().__init__("d435_node")
    self.group = ReentrantCallbackGroup()
    self.combined_pub = self.create_publisher(CompressedImage, '/image_combined/compressed', 10)
    self.bridge = cv_bridge.CvBridge()
    self.cap = cv2.VideoCapture(0)
    self.clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8,8))
    try:
      BaseOptions = mp.tasks.BaseOptions
      self.PoseLandmarker = mp.tasks.vision.PoseLandmarker
      PoseLandmarkerOptions = mp.tasks.vision.PoseLandmarkerOptions
      VisionRunningMode = mp.tasks.vision.RunningMode

      self.options = PoseLandmarkerOptions(
          base_options=BaseOptions(model_asset_path=model_path),
          running_mode=VisionRunningMode.IMAGE)
      self.landmarker = self.PoseLandmarker.create_from_options(self.options)
      self.get_logger().info("MediaPipe Landmarker initialized.")
    except Exception as e:
      self.get_logger().error(f"Failed to initialize MediaPipe Landmarker: {str(e)}")
      raise e
    
    timer_period = 0.1
    self.timer = self.create_timer(timer_period, self.timer_callback, callback_group=self.group)

    self.pipeline = rs.pipeline()
    config = rs.config()
    self.width = 640
    self.height = 480
    self.pub_width = 320
    self.pub_height = 240
    
    config.enable_stream(rs.stream.depth, self.width, self.height, rs.format.z16, 15)
    config.enable_stream(rs.stream.color, self.width, self.height, rs.format.bgr8, 15)

    self.pipeline.start(config)

  def timer_callback(self):
    ret, webcam_frame = self.cap.read()
    try:
      frames = self.pipeline.wait_for_frames()
      color_frame = frames.get_color_frame()

      if not color_frame:
        return
      color_image = np.asanyarray(color_frame.get_data())
      #color_image = self.clahe.apply(color_image)
      #color_image = cv2.resize(color_image, (self.pub_width, self.pub_height))
      color_image = self.enhance_contrast(color_image)
      mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=color_image)
      landmarker_result = self.landmarker.detect(mp_image)
      if landmarker_result.pose_landmarks:
        landmarks = landmarker_result.pose_landmarks[0]
        landmarks = np.array([landmarks[i] for i in points])

        depth_x = int((landmarks[1].x + landmarks[2].x + landmarks[7].x + landmarks[8].x) / 4 * self.width)
        depth_y = int((landmarks[1].y + landmarks[2].y + landmarks[7].y + landmarks[8].y) / 4 * self.height)
        depth_x = np.clip(depth_x, 0, self.width - 1)
        depth_y = np.clip(depth_y, 0, self.height - 1)
        depth_frame = frames.get_depth_frame()
        depth = depth_frame.get_distance(depth_x, depth_y)
        cv2.circle(color_image, (depth_x, depth_y), 5, (255, 0, 0), -1)
        for point in landmarks:
          x = int(point.x * self.width)
          y = int(point.y * self.height)
          cv2.circle(color_image, (x, y), 5, (0, 255, 0), -1)
        cv2.putText(color_image, f"Depth: {depth:.2f}m", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
      else:
        cv2.putText(color_image, "No Person Detected", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
      color_image = cv2.resize(color_image, (self.pub_width, self.pub_height))
      self.combined_publish(webcam_frame, color_image)
      
    except Exception as e:
      self.get_logger().error(f"Error: {str(e)}")
  
  def enhance_contrast(self, img):
    lab = cv2.cvtColor(img, cv2.COLOR_BGR2LAB)
    l, a, b = cv2.split(lab)
    l = self.clahe.apply(l)
    lab = cv2.merge((l, a, b))
    return cv2.cvtColor(lab, cv2.COLOR_LAB2BGR)

  def combined_publish(self, webcam_frame, color_image):
    combined_image = np.hstack((cv2.resize(webcam_frame, (self.pub_width, self.pub_height)), color_image))
    msg = self.bridge.cv2_to_compressed_imgmsg(combined_image)
    self.combined_pub.publish(msg)

def main(args=None):
  rclpy.init(args=args)
  node = D435Node()
  rclpy.spin(node)
  node.pipeline.stop()
  node.destroy_node()
  rclpy.shutdown()

if __name__ == "__main__":
  main()
