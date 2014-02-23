; Akash Badshah, Lab 2, Exercise 2
; This is the reverse assembled version of the 
; hex code provided in the packet

.org 00h
start:
  mov a, #00h
  mov p1, acc
  setb p1.2
  sjmp start
  .db   36h, 2eh, 31h, 31h, 35h, 20h, 52h, 6fh, 63h, 6bh, 73h, 21h
  ;addc a, @r0
  ;add a, r6
  ;acall 131h
  ;addc a, 20h
  ;anl 6fh, a
  ;xrl 6bh, #73h
  ;.db 21h
