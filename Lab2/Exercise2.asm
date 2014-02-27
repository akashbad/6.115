; Akash Badshah, Lab 2, Exercise 2
; This is the reverse assembled version of the 
; hex code provided in the packet

.org 00h
start:
  mov a, #00h
  mov p1, acc
  setb p1.2
  sjmp start
  .db "6.115 Rocks!"
