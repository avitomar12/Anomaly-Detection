#!/usr/bin/env python3 -W ignore::DeprecationWarning

import operate as op
import csv
import time
import RPi.GPIO as IO
result=1
IO.setwarnings(False)
IO.setmode(IO.BOARD)
IO.setup(40,IO.OUT)

def lighton(signal):
	if signal==-1:
		IO.cleanup()
		IO.setmode(IO.BOARD)
		IO.setup(40,IO.OUT)
		IO.output(40,1)

	else:
		IO.cleanup()

with open('reading.txt','w') as csvfile:
	fieldname=['time','X-axis','Y-axis','Z-axis','anomaly_score']
	writer=csv.DictWriter(csvfile,fieldname)
	writer.writeheader()
	while(True):
		x=op.routine(b'2')
		y=op.routine(b'1')
		z=op.routine(b'0')
		print("X-axis, y-axis,Z-axis",x,y,z)
		if x>682 or x<641 or y>698 or y<595 or z>550 or z<490:
			result=-1
			lighton(-1)
		else:
			result=1
			lighton(1)
		writer.writerow({'time':time.ctime(),'X-axis': x, 'Y-axis': y, 'Z-axis': z,'anomaly_score': result})
