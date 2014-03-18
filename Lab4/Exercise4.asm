; Akash Badshah, Lab 4, Exercise 4
; This simple program generates a
; PWM wave on PA.0 of the attached
; 8255, with a duty cycle of 50% 
; and a frequency of either .5Hz
; or 5000Hz using Timer 0 Interrupts
; we store the current state of Port A
; inside of r2 and the software counter
; reset value in r1
.org 0
ljmp init

.org 000bh
ljmp TOISR

.org 30h
TOISR:
  djnz r0, exit     ; Exit if we haven't hit the software count
  mov a, r1         ; get the reset value
  mov r0, a         ; Reset the software count
  mov a, r2         ; move port a to acc
  xrl a, #01h       ; toggle the bit
  mov r2, a         ; store it back
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
  mov r2, #00h       ; clear port a
  mov a, r2
  movx @dptr, a      ; sync r2 with port a
  lcall fast         ; pick our frequency
  mov a, r1          ; set up our software count
  mov r0, a          ; put it in r0
  setb tr0           ; start timer 0  
  mov ie, #82h       ; enable interrupts
loop:
  sjmp loop

; This procedure configures the Timer and
; the internal software count for a 0.5Hz
; PWM signal
slow:
  mov tmod, #01h        ; using timer 0 in mode 1
  mov r1, #0Eh          ; software counts from 14
  ret
; This procedure configures the Timer and
; the internal software count for a 5000Hz
; PWM Signal
fast:
  mov tmod, #02h        ; using timer 0 in mode 2
  mov th0, #164         ; count to get 5000Hz 
  mov r1, #1h           ; count 1 cycle to f
  ret
