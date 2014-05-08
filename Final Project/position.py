import sys, serial

ser = serial.Serial("/dev/tty.usbserial",9600)
active = False
frames = []
while True:
  try: 
    data = ser.readline().split()
    if len(data) > 0:
      if active:
        frames.append(data)
      else:
        active = True
    else:
      active = False
      if len(frames) > 1:
        frame_positions = []
        for frame in frames:
          numerator = 0.0
          denominator = 0.0
          for coordinate in frame:
            (value, position) = coordinate.split(":")
            numerator += int(position,16) * int(value,16)
            denominator += int(value, 16)
          frame_positions.append(numerator/denominator)
        print sum(frame_positions)/len(frame_positions)
      frames = []
  except KeyboardInterrupt:
    print 'exiting'
    break
  except ValueError:
    print 'deformed data'
    continue
ser.flush()
ser.close()
