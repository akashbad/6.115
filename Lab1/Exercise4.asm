; Akash Badshah, Lab 1, Exercise 4
; This is a basic calculator application that takes in 2
; numbers of exactly 3 digits and performs either addition
; or subtraction on those numbers

; r0-r3 are used for scratchpad space within subroutines

; r4 and r5 are used as counters when receiving digits, r4 decrements from 3
; (to get a 3 digit number) and r5 decrements from 2 (to get 2 numbers)
; r6 and r7 are used for program counter space when the stack is being used
; for parameters or return variables

; The main loop or body of our calculator program:

.org 000h                 ; power up and reset vector
  ljmp start              ; when the micro wakes up, jump to the beggining of
                          ; the main body or loop in the program, called "start"
                          ; and located at address location 100h in external mem
.org 100h
start:
  lcall init              ; Start the serial port by calling subroutine "init".

  start_calculation:
    mov r5, #2            ; put 2 in r5 to get 2 numbers
  start_number:
    mov r4, #3            ; put 3 in r4 to get 4 digits
    mov a, #0             ; clear the acc to get it ready for a new number
    
  loop:                   ; Now, endlessley repeat a loop that
    mov b, #10            ; Put 10 into register b so we can multiply accumulator
    mul ab                ; multiply the acc by 10 to decimal shift by 1
    xch a, r0             ; swap r0 and a so we can keep our growing number as we
                          ; get a new character in acc
    lcall getchr          ; <- gets a character from the PC keyboard, puts it in acc
    lcall sndchr          ; -> and then echoes that character back from acc
    anl a, #0fh           ; take the new character and mask it to get int value
    xch a, r0             ; swap a and r0 again so we can keep accumulating
    add a, r0             ; add the new digit to the acc
    djnz r4, loop         ; keep putting digits on the number if we dont have 3

  push acc                ; push the number we've been working on onto the stack
  lcall crlf              ; add a new line here because we have a 3 digit number
  djnz r5, start_number   ; keep getting numbers until we have the amount we want
  lcall calculate         ; our calculation function now goes and does what it needs to
  sjmp start_calculation

init:
; set up the serial port with a 11.0592 MHz crystal
; use Timer 1 for 9600 baud serial communication
  mov tmod, #20h          ; set timer 1 for auto reload - mode 2
  mov tcon, #40h          ; run timer 1
  mov th1, #253           ; set 9600 baud with xtal=11.059mhz
  mov scon, #50h          ; set serial control reg for 8 bit data
                          ; and mode 1
  ret

getchr:
; This routine "gets" or received a character from the PC, transmitted over
; the serial port. RI is the same as SCON.0 - the assembler recognizes
; either shorthand. The 7-bit ASCII code is returned in the accumulator
  jnb ri, getchr          ; wait till character received
  mov a, sbuf             ; get character and put it in the accumulator
  anl a, #7fh             ; mask off the 8th bit
  clr ri                  ; clear serial "receive status" flag
  ret

sndchr:
; This routine "sends" or transmits a character to the PC, using the serial
; port. The character to be sent is stored in the accumulator. SCON.1 and
; TI are the same as far as the assembler is concerned.
  clr ti                  ; clear the ti complete flag
  mov sbuf, a             ; move a character from the acc to the sbuf
  txloop:
    jnb ti, txloop        ; wait till chr is sent
  ret

crlf:
; This routine adds an autowrap by printing a carriage return character and then
; printing a new line character
  mov a, #10              ; add the CR character to the accumulator
  lcall sndchr            ; send off the CR character
  mov a, #13              ; add the newline character to the accumulator
  lcall sndchr            ; send off the NL character
  ret

calculate:
; This routine assumes that the previous 2 registers in the stack before
; the return program counter are the 2 params which need to be calculated
; on. The calculator gets those numbers, pulls in another character from
; serial to see which kind of operation it needs, and then does the 
; correct calculation, displaying the result on the led bank
  pop acc                 ; pop the high part of the pc to acc
  mov r7, a               ; move that to r7
  pop acc                 ; pop the low part of the pc to acc
  mov r6, a               ; move that to r6

  pop acc                 ; pop the second number into acc
  mov r1, acc             ; move that number into r1
  pop acc                 ; pop the first number into acc
  mov r0, acc             ; move that number into r0

  lcall getchr            ; get the character we need and put it in b
  lcall sndchr            ; send back the character so the user can see it
  
  plus:
   cjne a, #2bh, minus    ; check if the character is +, if not jump to the minus
   mov a, r0              ; put the first value in the acc
   add a, r1              ; add the value from r0 to the acc
   sjmp return            ; return
  minus:
   cjne a, #2dh, return
   mov a, r0              ; put the first value in the acc
   subb a, r1             ; subtract the value from r1 from the acc
  return:
   mov p1, a              ; put our calculation result in the led bank
   mov a, r6              ; put the low part of the pc into acc
   push acc               ; put back the low part of the pc
   mov a, r7              ; put the high part of the pc into acc
   push acc               ; put back the high part of the pc
   lcall crlf
   lcall crlf
   ret  

