; Akash Badshah, Lab 4, Exercise 2
; This simple program switches the
; state of Pin A.0 on the attached
; 8255 every 5 seconds, driving a
; Relay through a 18293.
; It uses Timer 0 in Mode 1
; with a software counter to actuate
; the relay in such long intervals
.org 0
ljmp init

.org 000bh
ljmp TOISR

.org 30h
TOISR:
  djnz r0, exit     ; Exit if we haven't hit the software count
  mov r0, #46h      ; Reset the software count
  mov a, r1         ; move port a to acc
  xrl a, #01h       ; toggle the bit
  mov r1, a         ; store it back
  mov dptr, #0fe10h ; get dptr ready
  movx @dptr, a     ; send it out
exit:
  reti

.org 100h
init:
  mov dptr, #0fe13h  ; control byte for 8255
  mov a,  #80h       ; everything is output
  movx @dptr, a      ; program it
  mov dptr #0fe10h   ; Port A address
  mov r1, #00h       ; clear port a
  mov a, r1
  movx @dptr, a      ; sync r2 with port a
  mov tmod, #01h     ; Timer 0 in mode 1  
  mov r0, #46h       ; software counts from 70 
  setb tr0           ; start timer 0  
  mov ie, #82h       ; enable interrupts
loop:
  sjmp loop
