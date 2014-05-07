import sys, serial
from matplotlib import pyplot

ser = serial.Serial("/dev/tty.usbserial",9600)
pyplot.ion()
pyplot.ylim([0,20])
plot, = pyplot.plot([0 for x in range(32)])
while True:
  try:
    #ser.write(' ')
    line = ser.readline()
    data = [int(x,16) for x in line.split()]
    plot.set_ydata(data)
    pyplot.draw()
  except KeyboardInterrupt:
    print 'exiting'
    break
  except ValueError:
    print 'deformed data'
    continue
ser.flush()
ser.close()
