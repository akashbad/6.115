'''
Launcher.py
Akash Badshah, Spring 2014 6.115 Final Project

This is an api to interact with the Dream Cheeky Thunder Missile launcher
'''

import usb
import sys
import serial
import time

class MissileLauncher:
  
  #acquire the launcher according to its product & vendor id
  def __init__(self):
    self.launcher = usb.core.find(idVendor=0x2123, idProduct=0x1010)
    if self.launcher is None:
      raise Error('Missile launcher was not found')

  def command(self, command):
    #Send a control transfer according to the usb protocol, commands are prefixed with 0x02 and padded
    #with 6 empty bytes
    self.launcher.ctrl_transfer(0x21, 0x09, 0, 0, [0x02, command, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])

  def led_on(self):
    #the led is controlled with a prefix of 0x03 and then the same padding bytes
    self.launcher.ctrl_transfer(0x21, 0x09, 0, 0, [0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])
      
  def led_off(self):
    #the led is controlled with a prefix of 0x03 and then the same padding bytes
    self.launcher.ctrl_transfer(0x21, 0x09, 0, 0, [0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])

  #each of the movement commands will cause the turret to move in that direction until it gets a stop
  def down(self):
    self.move_command(0x01)
  def up(self):
    self.move_command(0x02)
  def left(self):
    self.move_command(0x04)
  def right(self):
    self.move_command(0x08)
  def move_command(self, command):
    self.command(command)
    time.sleep(0.1)
    self.stop();
  def fire(self):
    self.command(0x10)
  def stop(self):
    self.command(0x20)

def __main__():
  launcher = MissileLauncher()
  ser = serial.Serial("/dev/tty.usbmodem1411",9600,timeout=1)
  previous_command = "";
  while True:
    try:
      line = ser.readline().strip()
      if line == previous_command:
        continue;
      previous_command = line;
      if line == "fire":
        launcher.fire()
        time.sleep(5);
        ser.flush();
      if line == "right":
        launcher.right() 
      if line == "left":
        launcher.left() 
      if line == "up":
        launcher.up() 
      if line == "down":
        launcher.down()
      if line == "stop":
        launcher.stop()
    except KeyboardInterrupt:
      print 'exiting'
      break
  ser.flush()
  ser.close()

__main__()
