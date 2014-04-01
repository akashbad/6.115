; Akash Badshah, Lab 4, Exercise 9
; This program runs the spin dude system by stepping
; through each of the 24 positions on the spin dude
; and at each of those positions running through the 
; 16 LED/Phototransistor combinations and reading
; the analog voltage through the ADC. It outputs
; these bytes as a big space and line seperated matrix
; to serial, which is meant to be read by a Matlab script.
; Register usage:
;  r0 - motor position counter
;  r1 - led / photo transistor indicator
;  r2 - prthex processing register
;  r3 - phototransistor settle inner loop
;  r4 - phototransistor settle outer loop
;  r5 - innermost stall loop counter
;  r6 - middle stall loop counter
;  r7 - outermost stall loop counter

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
  mov r5, #0Ah              ; 10 counts on highest loop
loop:
  lcall getchr              ; wait for input char
  lcall rotation            ; do the rotation
  sjmp loop                 ; loop again

rotation:
; This routine runs one full rotation of the attached SpinDude
; platform, using 24 steps and a delay between the steps which
; is large enough to let the dowel's vibrations to settle to a
; stop. Before each step it also collects data from the 16 LED
; photo transistors and outputs those to serial.
  mov r0, #24               ; 24 steps in a rotation
rotation_loop:  
  mov dptr, #motor_table    ; point at the motor_table
  mov a, r0                 ; get the current count
  mov b, #04h               ; use mod 4 arithmetic
  div ab                    ; divide count by 4
  mov a, b                  ; get the remainder of the division
  movc a, @a + dptr         ; byte from the table
  mov dptr, #0fe10h         ; point at Port A
  movx @dptr, a             ; push that byte to the Port A
rotation_stall:
  djnz r7, rotation_stall   ; lowest loop stall for 256
  djnz r6, rotation_stall   ; middle loop stall for
  mov r6, #0b4h             ; 180 rounds
  djnz r5, rotation_stall   ; highest loop stall for 
  mov r5, #0ah              ; 10 rounds
  lcall measure             ; once we have settled, measure
  djnz r0, rotation_loop    ; decrement our step counter   
  ret

measure:
  mov r1, #00h              ; initialize our led address
single_measurement:
  mov p1, r1                ; turn on the light and start
  mov r3, #00h              ; start inner counter @ 0
  mov r4, #04h              ; 4 counts on outer counter
settle:
  djnz r3, settle           ; wait for a settle of 
  djnz r4, settle           ; 2000ms for the transistor
  mov dptr, #0fe20h         ; the address of the adc
  movx @dptr, a             ; initiate a conversion
adc_wait:
  jb p3.3, adc_wait         ; wait for a finished conversion
  movx a, @dptr             ; get the value from the adc
  lcall prthex              ; send the hex character to serial
  mov a, #20h               ; get a space character
  lcall sndchr              ; send the space
  inc r1                    ; increment r1
  cjne r1, #10h, single_measurement
  lcall crlf                ; crlf to cap it off
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

crlf:
; This routine adds an autowrap by printing a carriage return character and then
; printing a new line character
  mov a, #10            ; add the CR character to the accumulator
  lcall sndchr          ; send off the CR character
  mov a, #13            ; add the newline character to the accumulator
  lcall sndchr          ; send off the NL character
  ret

;===============================================================
; subroutine prthex
; this routine takes the contents of the acc and prints it out
; as a 2 digit ascii hex number.
;===============================================================
prthex:
   push acc
   lcall binasc           ; convert acc to ascii
   lcall sndchr           ; print first ascii hex digit
   mov   a,  r2           ; get second ascii hex digit
   lcall sndchr           ; print it
   pop acc
   ret
;===============================================================
; subroutine binasc
; binasc takes the contents of the accumulator and converts it
; into two ascii hex numbers.  the result is returned in the
; accumulator and r2.
;===============================================================
binasc:
   mov   r2, a            ; save in r2
   anl   a,  #0fh         ; convert least sig digit.
   add   a,  #0f6h        ; adjust it
   jnc   noadj1           ; if a-f then readjust
   add   a,  #07h
noadj1:
   add   a,  #3ah         ; make ascii
   xch   a,  r2           ; put result in reg 2
   swap  a                ; convert most sig digit
   anl   a,  #0fh         ; look at least sig half of acc
   add   a,  #0f6h        ; adjust it
   jnc   noadj2           ; if a-f then re-adjust
   add   a,  #07h
noadj2:
   add   a,  #3ah         ; make ascii
   ret
