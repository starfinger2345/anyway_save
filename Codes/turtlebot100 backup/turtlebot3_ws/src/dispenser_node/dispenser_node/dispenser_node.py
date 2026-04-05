#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import Empty, Float32  # Float32 추가
import pigpio
import time

class DispenserNode(Node):
    def __init__(self):
        super().__init__('dispenser_node')
        
        self.pi = pigpio.pi()
        if not self.pi.connected:
            self.get_logger().error('pigpiod is not running! Run "sudo pigpiod" first.')
            return

        # 서보 핀
        self.PIN_PUSHER = 18
        self.PIN_DOOR = 19
        
        # RGB LED 핀 (추가)
        self.PIN_RED = 17
        self.PIN_GREEN = 27
        self.PIN_BLUE = 22
        
        self.is_forward = False
        
        # 초기 설정: 서보 토크 해제 및 LED 끄기
        self.release_all()
        self.led_off()
        
        # 구독자 1: 서보 제어 (Empty)
        self.trigger_sub = self.create_subscription(
            Empty, '/dispenser_trigger', self.trigger_callback, 10)
        
        # 구독자 2: CDS 값 감시 (Float32) - 추가
        self.cds_sub = self.create_subscription(
            Float32, '/cds', self.cds_callback, 10)
        
        self.get_logger().info('Dispenser Node Ready with RGB LED Control (Threshold: 30)')

    def release_all(self):
        """모든 서보의 토크를 제거합니다."""
        self.pi.set_servo_pulsewidth(self.PIN_PUSHER, 0)
        self.pi.set_servo_pulsewidth(self.PIN_DOOR, 0)

    def led_off(self):
        """RGB LED를 모두 끕니다."""
        self.pi.write(self.PIN_RED, 0)
        self.pi.write(self.PIN_GREEN, 0)
        self.pi.write(self.PIN_BLUE, 0)

    def led_white(self):
        """RGB LED를 모두 켜서 흰색을 만듭니다."""
        self.pi.write(self.PIN_RED, 1)
        self.pi.write(self.PIN_GREEN, 1)
        self.pi.write(self.PIN_BLUE, 1)

    def cds_callback(self, msg):
        """수신된 데이터가 30 이하면 흰색, 아니면 끔"""
        # msg.data에 1~100 사이의 값이 들어옵니다.
        if msg.data <= 30.0:
            self.led_white()
        else:
            self.led_off()

    def trigger_callback(self, msg):
        self.get_logger().info('Signal Received! Action Start.')
        
        # 1. 문 열림 (Pulse 500)
        self.pi.set_servo_pulsewidth(self.PIN_DOOR, 500)
        time.sleep(0.5)
        self.pi.set_servo_pulsewidth(self.PIN_DOOR, 0)

        if not self.is_forward:
            # 2-A. 푸셔 전진 (Pulse 2400)
            self.pi.set_servo_pulsewidth(self.PIN_PUSHER, 2400)
            time.sleep(0.6)
            self.pi.set_servo_pulsewidth(self.PIN_PUSHER, 0)
            self.is_forward = True
        else:
            # 2-B. 푸셔 후진 (Pulse 600)
            self.pi.set_servo_pulsewidth(self.PIN_PUSHER, 600)
            time.sleep(0.6)
            self.pi.set_servo_pulsewidth(self.PIN_PUSHER, 0)
            self.is_forward = False
        
        # 3. 문 닫힘 (Pulse 1400)
        self.pi.set_servo_pulsewidth(self.PIN_DOOR, 1400)
        time.sleep(0.5)
        self.pi.set_servo_pulsewidth(self.PIN_DOOR, 0)
        
        self.get_logger().info('Sequence Complete & Torque Released.')

def main(args=None):
    rclpy.init(args=args)
    node = DispenserNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.release_all()
        node.led_off() # 종료 시 LED도 끄기
        node.pi.stop()
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
