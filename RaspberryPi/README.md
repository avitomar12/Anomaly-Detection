flask-live-charts
=================

Live charting of the sensor data using flask and highcharts.

Simply run flask-live-charts.py and point your browser to http://127.0.0.1:5000


main.c - file consist of c which access the microcontroller.
operate.py - file consist of function which calls the microcontroller to provide the sensor data.
reading.txt - Sensor readings
graph_plot.py - Plot the reading of sensor data in 2d plane to get a better visualization.
reading_sensor.py - Read the data from the sensor and store them in reading.txt file.


A sample of reading 

<img src = "/images/screenshot.png">
