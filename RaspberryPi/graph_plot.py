import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
import numpy as np
import operate as op
style.use('fivethirtyeight')

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
xs=[]
ys=[]
def animate(i):
    xs.append(float(op.routine(b'2')))
    ys.append(float(op.routine(b'1')))
    ax1.clear()
    ax1.plot(xs, ys)

ani = animation.FuncAnimation(fig, animate, interval=100)
plt.show()
