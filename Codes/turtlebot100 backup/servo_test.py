from gpiozero import AngularServo, Button
from signal import pause
import logging

# 1. 서보모터 설정 (SG90/MG90S 표준 사양 적용)
# 펄스 폭을 0.5ms ~ 2.5ms로 설정해야 180도 전 영역을 활용 가능합니다.
servo = AngularServo(18, min_angle=0, max_angle=180, 
                     min_pulse_width=0.0005, max_pulse_width=0.0025)

# 2. 버튼 설정 (GPIO 21번, 내부 풀업 저항 사용)
button = Button(21)

def on_button_pressed():
    print("입력 확인: 180도 회전 시도")
    servo.angle = 180

def on_button_released():
    print("입력 해제: 0도 복귀")
    servo.angle = 0

# 이벤트 연결
button.when_pressed = on_button_pressed
button.when_released = on_button_released

print("--- 터틀봇 서보 전력 테스트 시작 ---")
print("버튼을 누르면 180도, 떼면 0도로 움직입니다.")
print("종료하려면 Ctrl+C를 누르세요.")

try:
    pause()
except KeyboardInterrupt:
    print("\n테스트를 종료합니다.")