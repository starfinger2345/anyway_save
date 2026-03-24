import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CompressedImage
from custom_interfaces.msg import People, Person
import cv2
import numpy as np
from ultralytics import YOLO

class PersonTrackerNode(Node):
    def __init__(self):
      super().__init__('person_tracker_node')
      
      # Image topic subscription
      self.subscription = self.create_subscription(
          CompressedImage, 
          '/image_out/compressed', 
          self.image_callback, 
          10)
      
      # People points publisher
      self.publisher = self.create_publisher(People, '/point_out', 10)

      # YOLO model define
      model_path = "/home/ubuntu/project_ws/src/person_tracker_node/person_tracker_node/yolo11n-pose.pt"
      self.model = YOLO(model_path)
      
      # CLAHE filter initalize
      self.clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))

      self.get_logger().info('Person Tracker Node has been started')

    def image_callback(self, msg):
      # JPEG decode
      np_arr = np.frombuffer(msg.data, np.uint8)
      frame = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)

      if frame is None:
          return

      # Depth Image(right half)
      h, w, _ = frame.shape
      depth_roi = frame[:, w//2:] 

      # Apply median filter
      filtered = cv2.medianBlur(depth_roi, 3)

      # Y Channel CLAHE filtering
      yuv = cv2.cvtColor(filtered, cv2.COLOR_BGR2YUV)
      yuv[:, :, 0] = self.clahe.apply(yuv[:, :, 0])
      processed_img = cv2.cvtColor(yuv, cv2.COLOR_YUV2BGR)

      # YOLOv11n-Pose detection
      results = self.model(processed_img, verbose=False)
      people_msg = People()
      if len(results) == 0:
        self.publisher.publish(people_msg)
        return
      result = results[0]
      if result.keypoints is None:
        self.publisher.publish(people_msg)
        return
      
      # Points of shoulders and hip
      indices = [5, 6, 11, 12]
      keypoints = result.keypoints.xyn[:, indices, :].cpu().numpy() # (N, 4, 2)
      scores = result.keypoints.conf[:, indices].cpu().numpy() # (N, 4)
      boxes = result.boxes.xyxyn.cpu().numpy() # (N, 4)
      
      count = 0
      for i in range(len(keypoints)):
        x1, y1, x2, y2 = boxes[i]
        w_box = x2 - x1
        h_box = y2 - y1
        if w_box < 0.05 or h_box < 0.1:
          continue
        
        keypoint = keypoints[i] # (4, 2)
        conf = scores[i] # (4,)
        valid_mask = conf > 0.5
        if np.any(valid_mask):
          valid_points = keypoint[valid_mask]
          center = np.mean(valid_points, axis=0)
        else:
          continue
        
        if np.sum(valid_mask) == 4:
          shoulder_center = np.mean(keypoint[:2], axis=0)
          hip_center = np.mean(keypoint[2:], axis=0)
          
          dx, dy = shoulder_center - hip_center
          angle = abs(np.arctan2(dy, dx))
          state = 1.0 if angle > 1.0 else 2.0
        else:
          state = 0.0
        
        person = Person()
        person.x = float(center[0])
        person.y = float(center[1])
        person.state = float(state)
        
        people_msg.people.append(person)
        count += 1
        if count >= 5:
          break
      self.publisher.publish(people_msg)

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
