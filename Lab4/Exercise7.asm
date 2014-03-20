; Akash Badshah, Lab 4, Exercise 7
; This program runs a stepper motor
; that is connected to a driver circuit through
; a connected 8255 and 18923 system. The motor
; is a unipolar stepper motor

.org 0h
start:
  ljmp init

.org 100h
motor_table:                ; the 4 motor values which
  .db 0eh, 0bh, 0dh, 07h    ; are looped through

init:
  mov tmod, #20h            ; set up timer 1 as a 
  mov tcon, #40h            ; baud rate clock which
  mov th1, #253             ; used 9600 baud
  mov scon, #50h            ; turn on the serial port
  mov dptr, #0fe13h         ; configure Port A as
  mov a, #80h               ; an output on the 8255
  movx @dptr, a             ; buffered through 18293
  mov r7, #00h              ; initialize stall values
  mov r6, #0b4h             ; 180 counts on middle loop
loop:
  lcall getchr              ; wait for input char
  lcall sndchr              ; echo back
  lcall process_input       ; get the speed + direction from key
  lcall rotation            ; do the rotation
  sjmp loop                 ; loop again

process_input:
; This procedure determines the speed + direction from the input
; character. It uses the lower 5 bits for the integer multiples
; of 100ms for the delay. It uses the 6th bit to specify
; direction, with 0 being clockwise
  push acc                  ; store a copy of a
  rl a                      ; rotate a to the left 2 times
  rl a                      ; and then once more so we can
  rlc a                     ; get bit 6 into the carry
  mov 00h, c                ; use that to set the direction
  pop acc                   ; get back the original
  anl a, #1fh               ; mask off the top 3 bits
  mov r3, a                 ; and use that as our count
  mov r2, a                 ; for integer number of 100ms
  ret

rotation:
; This routine runs one full rotation of the attached SpinDude
; platform, using 24 steps and a delay between the steps equal
; to the inital value in r3 * 100ms. It chooses direction
; based on the bit in 00h 
  mov r0, #24               ; 24 steps in a rotation
  mov r1, #0h               ; count starts at 0
rotation_loop:  
  mov dptr, #motor_table    ; point at the motor_table
  mov a, r1                 ; get the current count
  mov b, #04h               ; use mod 4 arithmetic
  div ab                    ; divide count by 4
  mov a, b                  ; get the remainder of the division
  movc a, @a + dptr         ; byte from the table
  mov dptr, #0fe10h         ; point at Port A
  movx @dptr, a             ; push that byte to the Port A
  jb 00h, counter_clockwise
clockwise:
  dec r1                    ; decrement count for clockwise
  sjmp rotation_stall
counter_clockwise:
  inc r1                    ; increment the count for counter
rotation_stall:
  djnz r7, rotation_stall   ; lowest loop stall for 256
  djnz r6, rotation_stall   ; middle loop stall for
  mov r6, #0b4h             ; 180 rounds
  djnz r2, rotation_stall   ; highest loop, variable and set by r3
  mov a, r3                 ; reset our counter
  mov r2, a                 ; for outermost loop
  djnz r0, rotation_loop    ; decrement our step counter   
  ret

getchr:
; This routine "gets" or received a character from the PC, transmitted over
; the serial port. RI is the same as SCON.0 - the assembler recognizes
; either shorthand. The 7-bit ASCII code is returned in the accumulator
  jnb ri, getchr        ; wait till character received
  mov a, sbuf           ; get character and put it in the accumulator
  anl a, #7fh           ; mask off the 8th bit
  clr ri                ; clear serial "receive status" flag
  ret

sndchr:
; This routine "sends" or transmits a character to the PC, using the serial
; port. The character to be sent is stored in the accumulator. SCON.1 and
; TI are the same as far as the assembler is concerned.
  clr ti                ; clear the ti complete flag
  mov sbuf, a           ; move a character from acc to the sbuf
  txloop:
    jnb ti, txloop      ; wait till chr is sent
  ret
