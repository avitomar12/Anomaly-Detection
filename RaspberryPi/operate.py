import serial
import sys

if len(sys.argv) > 1:
    serial_path = sys.argv[1]
else:
    serial_path = "/dev/serial0"

ser = serial.Serial(serial_path,4800)

def routine(x):
    ser.write(x)
    ret = ser.read(2)
    ret =int.from_bytes(ret,byteorder='big')
    return ret


# USAGE: routine(b"0") for value at channel 0
