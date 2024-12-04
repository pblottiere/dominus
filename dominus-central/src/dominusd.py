#!/usr/bin/env python3

import time
import subprocess
import RPi.GPIO as GPIO

PIN=36

GPIO.setmode(GPIO.BOARD)
GPIO.setup(PIN, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

def my_callback(channel):
    print("DING DONG", flush=True)
    subprocess.run(["/usr/bin/aplay", "/usr/share/dominus/christmas0.wav"])

GPIO.add_event_detect(PIN, GPIO.RISING, callback=my_callback, bouncetime=300)

print("dominusd is starting...", flush=True)
while True:
    time.sleep(1)
