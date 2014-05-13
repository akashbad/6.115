'''
Launcher.py
Akash Badshah, Spring 2014 6.115 Final Project

This is an api to interact with the Dream Cheeky Thunder Missile launcher
It also includes a main function which will establish a connection with
Both the launcher and the PSoC and interpret the commands from the PSoC
as commands to the launcher
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

  #each of the movement commands will cause the turret to move in that direction for 100ms
  def down(self):
    self.move_command(0x01)
  def up(self):
    self.move_command(0x02)
  def left(self):
    self.move_command(0x04)
  def right(self):
    self.move_command(0x08)
  #We accomplish 100ms directions by issuing a stop
  # command quickly after
  def move_command(self, command):
    self.command(command)
    time.sleep(0.1)
    self.stop();
  def fire(self):
    self.command(0x10)
  def stop(self):
    self.command(0x20)

def __main__():
  #connect to the launcher
  launcher = MissileLauncher()
  #turn on the led for safety
  launcher.led_on();
  #connect to serial
  ser = serial.Serial("/dev/tty.usbmodem1411",9600,timeout=1)
  previous_command = "";
  while True:
    #do until we get a keyboard interrupt
    try:
      #pickup a line from the serial
      line = ser.readline().strip()
      #include the prints only for debugging
      #print line
      # use this statefullness to prevent from
      # issuing the same command again and again
      if line == previous_command:
        continue;
      previous_command = line;
      if line == "fire":
        launcher.fire()
        #because of the mechanics from the launcher
        #we need to give it enough time to fire
        #before issuing more commands
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
    #use this to gracefully exit the program
    except KeyboardInterrupt:
      print 'exiting'
      break
 #nicely close the serial port and turn off the light
  ser.flush()
  ser.close()
  launcher.led_off()

#run the main
__main__()
