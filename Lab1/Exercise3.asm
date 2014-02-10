; Akash Badshah, Lab 1, Exercise 3
; This is basic serial echo code, which takes in characters
; echoes them back over serial. It also includes a crlf feature
; after 65 characters and displays characters on the led bank

; The main loop or body of our typewriter program:

.org 000h               ; power up and reset vector
  ljmp start            ; when the micro wakes up, jump to the beggining of
                        ; the main body or loop in the program, called "start"
                        ; and located at address location 100h in external mem
.org 100h
start:
  lcall init            ; Start the serial port by calling subroutine "init".
  setup:
    mov r0, #65         ; set up register 0 with the value 65
  loop:                 ; Now, endlessley repeat a loop that
    lcall getchr        ; <- gets a character from the PC keyboard
    lcall sndchr        ; -> and then echoes the character to the PC screen
    mov p1, a           ; put the stored character from the accumulator into the led bank
    djnz r0, loop       ; keep the loop up if we haven't hit 65 characters yet
  lcall crlf            ; add a new line once we have printed 65 characters
  sjmp setup

init:
; set up the serial port with a 11.0592 MHz crystal
; use Timer 1 for 9600 baud serial communication
  mov tmod, #20h        ; set timer 1 for auto reload - mode 2
  mov tcon, #40h        ; run timer 1
  mov th1, #253         ; set 9600 baud with xtal=11.059mhz
  mov scon, #50h        ; set serial control reg for 8 bit data
                        ; and mode 1
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
  mov a, #10         ; add the CR character to the accumulator
  lcall sndchr          ; send off the CR character
  mov a, #13         ; add the newline character to the accumulator
  lcall sndchr          ; send off the NL character
  ret

