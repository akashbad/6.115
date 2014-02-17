; Akash Badshah, Lab 2, Exercise 2
; This is the reverse assembled version of the 
; hex code provided in the packet

.org 00h
start:
  mov a, #00h
  mov p1, acc
  setb p1.2
  sjmp start
  addc a, @r0
  add a, r6
  acall 131h
  addc a, 20h
  anl 6fh, a
  xrl 6bh, #73h
  .db 21h
