import time
import RPi.GPIO as GPIO

PIN=36

GPIO.setmode(GPIO.BOARD)
GPIO.setup(PIN, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

def my_callback(channel):
    print("DING DONG")

GPIO.add_event_detect(PIN, GPIO.RISING, callback=my_callback, bouncetime=300)

print("dominusd is starting...")
while True:
    time.sleep(1)
