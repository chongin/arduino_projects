import RPi.GPIO as GPIO    # Import Raspberry Pi GPIO library
import array

from time import sleep     # Import the sleep function from the time module
GPIO.setwarnings(False)    # Ignore warning for now
GPIO.setmode(GPIO.BOARD)   # Use physical pin numbering

#number=A00271732
a=2
b=3
c=7

a_lcd_pin = 13
b_lcd_pin = 16
c_lcd_pin = 23

lcd_pins = array.array('i', [12, 13, 16, 20, 21, 22, 23, 24, 25])

for pin in lcd_pins:
  GPIO.setup(pin, GPIO.OUT, initial=GPIO.LOW)   # Set pin 


def blink_lcd(pin, on_interval, off_interval):
    GPIO.setup(pin, GPIO.OUT, initial=GPIO.HIGH)
    sleep(on_interval) 
    GPIO.setup(pin, GPIO.OUT, initial=GPIO.LOW)
    sleep(off_interval) 

while True: # Run forever
    for pin in lcd_pins:
       GPIO.setup(pin, GPIO.OUT, initial=GPIO.HIGH)   # all on
    sleep(1)                  # Sleep for 1 second 

    for pin in lcd_pins:
       GPIO.setup(pin, GPIO.OUT, initial=GPIO.LOW)   # all off
    sleep(1)                  # Sleep for 1 second

     #a led blink a times
    i = 0
    for i in range(a):
      blink_lcd(a_lcd_pin, 1, 1)
      i = i + 1

     #b led blink b times
    i = 0
    for i in range(b):
       blink_lcd(b_lcd_pin, 1, 0.5)
       i = i + 1

    #c led blink c times
    i = 0
    for i in range(c):
       blink_lcd(c_lcd_pin, 0.5, 0.5)

    #all lcd blink 3 times
    for i in range(3):  
        for pin in lcd_pins:
            GPIO.setup(pin, GPIO.OUT, initial=GPIO.HIGH)   # all on
        sleep(1)

        for pin in lcd_pins:
           GPIO.setup(pin, GPIO.OUT, initial=GPIO.LOW)   # all off
        
        sleep(1)

    

    