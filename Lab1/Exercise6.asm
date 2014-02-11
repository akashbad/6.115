; Akash Badshah, Lab 1, Exercise 6
; This is the application to read in data from the 74C922 and
; either send it back to the computer, or use it as input
; for the calculator application built back in Exerise 5
; it is the exact same code as for Exercise 5, but replaces
; getchr with readpad and includes a new keytab function

; r0-r3 are used for scratchpad space within subroutines

; r4 and r5 are used as counters when receiving digits, r4 decrements from 3
; (to get a 3 digit number) and r5 decrements from 2 (to get 2 numbers)
; r6 and r7 are used for program counter space when the stack is being used
; for parameters or return variables

; The main loop or body of our calculator program:

.org 000h               ; power up and reset vector
  ljmp start            ; when the micro wakes up, jump to the beggining of
                        ; the main body or loop in the program, called "start"
                        ; and located at address location 100h in external mem
.org 100h
start:
  lcall init              ; Start the serial port by calling subroutine "init".

  start_calculation:
    lcall crlf		        ; a new line to delimit a calculation
    mov r5, #2		        ; put 2 in r5 to get 2 numbers
  start_number:
    mov r4, #3		        ; put 3 in r4 to get 4 digits
    mov a, #0		          ; clear the acc to get it ready for a new number
		
  loop:                   ; Now, endlessley repeat a loop that
    mov b, #10		        ; Put 10 into register b so we can multiply accumulator
    mul ab		            ; multiply the acc by 10 to decimal shift by 1
    xch a, r0		          ; swap r0 and a so we can keep our growing number as we
			                    ; get a new character in acc
    lcall readpad         ; <- gets a character from the keypad, puts it in acc
                          ; this returns the correct ascii character by using keytab
    lcall sndchr          ; -> and then echoes that character back from acc
    anl a, #0fh	          ; take the new character and mask it to get int value
    xch a, r0		          ; swap a and r0 again so we can keep accumulating
    add a, r0		          ; add the new digit to the acc
    djnz r4, loop         ; keep putting digits on the number if we dont have 3

  push acc		            ; push the number we've been working on onto the stack
  lcall crlf		          ; add a new line here because we have a 3 digit number
  djnz r5, start_number	  ; keep getting numbers until we have the amount we want
  lcall calculate	        ; our calculation function now goes and does what it needs to
  lcall print_answer	    ; print back our answer here
  sjmp start_calculation

init:
; set up the serial port with a 11.0592 MHz crystal
; use Timer 1 for 9600 baud serial communication
  mov tmod, #20h        ; set timer 1 for auto reload - mode 2
  mov tcon, #40h        ; run timer 1
  mov th1, #253         ; set 9600 baud with xtal=11.059mhz
  mov scon, #50h        ; set serial control reg for 8 bit data
                        ; and mode 1
  ret

sndchr:
; This routine "sends" or transmits a character to the PC, using the serial
; port. The character to be sent is stored in the accumulator. SCON.1 and
; TI are the same as far as the assembler is concerned.
  clr ti                ; clear the ti complete flag
  mov sbuf, a           ; move a character from the acc to the sbuf
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

readpad:
; This routine reads a character from the keypad hooked up to the 74C922
; It assumes the output 4 lines are hooked up to P1.0-P1.3 from LSB to MSB
; The data available pin should be hooked up to P3.4 and output enable to P3.5
  jnb p3.4, readpad     ; loop continuously until we have data available
  clr p3.5              ; set the output enable on
  mov a, p1             ; move the bits from the port into the accumulator
  anl a, #0fh           ; mask off the upper nibble
  lcall keytab          ; get the ascii character and put that in the acc
  setb p3.5             ; set the output enable back to off
  keyup:
    jb p3.4, keyup      ; wait until the data available flag is cleared
  ret

calculate:
; This routine assumes that the previous 2 registers in the stack before
; the return program counter are the 2 params which need to be calculated
; on. The calculator gets those numbers, pulls in another character from
; serial to see which kind of operation it needs, and then does the 
; correct calculation, displaying the result on the led bank
  pop acc		      ; pop the high part of the pc to acc
  mov r7, a		    ; move that to r7
  pop acc		      ; pop the low part of the pc to acc
  mov r6, a		    ; move that to r6
  
  pop acc		      ; pop the second number into acc
  mov r1, acc		  ; move that number into r1
  pop acc		      ; pop the first number into acc
  mov r0, acc		  ; move that number into r0

  lcall readpad		; get the character we need and put it in the acc
  lcall sndchr		; send back the character so the user can see it
  
  plus:
    cjne a, #2bh, minus	  ; check if the character is +, if not jump to the minus
    mov a, r0		          ; put the first value in the acc
    add a, r1		          ; add the value from r0 to the acc
    sjmp return		        ; return
  minus:
    cjne a, #2dh, return
    mov a, r0		  ; put the first value in the acc
    subb a, r1		; subtract the value from r1 from the acc
  return:
    push acc		  ; put the answer back on the stack to be printed

    mov a, r6		  ; put the low part of the pc into acc
    push acc		  ; put back the low part of the pc
    mov a, r7		  ; put the high part of the pc into acc
    push acc		  ; put back the high part of the pc
    lcall crlf
    ret	

print_answer:
; This routine takes the answer provided in the previous register before the 
; pc and prints it out in 3 digit readable decimal through serial
  pop acc		  ; pop the high part of the pc to acc
  mov r7, a		; move that to r7
  pop acc		  ; pop the low part of the pc to acc
  mov r6, a		; move that to r6

  pop acc		  ; pop the answer into acc

  mov b, #100		; put 100 into b so we can get the right digits
  div ab		    ; divide a by 100
  add a, #30h		; unmask the digit
  lcall sndchr	; send the quotient to serial
  mov a, b		  ; put the remainder into a
  mov b, #10		; put 10 into b so we can get the next digit
  div ab		    ; divide the remainder by 10
  add a, #30h		; unmask the digit
  lcall sndchr	; send the tens digit
  mov a, b		  ; put the 1's digit back in a
  add a, #30h		; unmask the digit
  lcall sndchr	; sends off the last digit

  mov a, r6		  ; put the low part of the pc into acc
  push acc		  ; put back the low part of the pc
  mov a, r7		  ; put the high part of the pc into acc
  push acc		  ; put back the high part of the pc
  lcall crlf
  ret	
    	
keytab:
; This is a table routine that contains the conversion between the keypad nibbles
; and the actually desired ascii character. It allows us to replace getchr with
; padread
  inc a              ; increment a to get over the ret instruction
  movc a, @a + pc    ; get the character from the db table and put in a
  ret
  .db   31h, 32h, 33h, 2bh, 34h, 35h, 36h, 2dh, 37h, 38h, 39h, 2ah, 2ah, 30h, 23h, 2fh
 
