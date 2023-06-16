
import serial
import time
import signal
import sys
import os

running = True

ser = serial.Serial(port='/dev/cu.usbmodem11301', baudrate=9600, timeout=1)
file_path = "./data.csv"
if os.path.exists(file_path):
    os.remove(file_path)
    print(f"remove file '{file_path}' success")
    
f = open(file_path, "w+")

def save_data(data):
    f.write(data)
    
def signal_handler(sig, frame):
    print('You pressed Ctrl+C!')
    running = False
    ser.close()
    f.close()
    print("Handle Crtl+C completed")
    sys.exit()

signal.signal(signal.SIGINT, signal_handler)

while running:
    line = ser.readline()   # read a byte
    if line:
        data = line.decode()  # convert the byte string to a unicode string
        #data = data.strip() remove /r/n
        print(data)
        save_data(data)


ser.close()
f.close()
print("reading serial complete")

