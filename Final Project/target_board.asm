;==================================================================
; * Akash Badshah, Final Project, Target Board                    * 
; *                                                               * 
; * This is the code which runs on the r31jp for my final project * 
; * It scans through pairs of LEDs and Phototransistors and makes * 
; * a voltage measurement on the phototransistor when the LED is  * 
; * off and again after the LED has been turned on. It then uses  * 
; * this difference as the value for that spot and computes the   * 
; * centroid of the measurements. The centroid is the coordinate  * 
; * of some projectile which passes through the target board.     * 
;==================================================================

.org 00h
;==================================================================
; main - this is the main subroutine that runs on the target-board
;   it first sets up the 8051 to communicate over serial to the
;   PSoC and then observes pin 3.3 for a signal on whether or not
;   to gather frames from the target. Each frame has its position
;   data transmitted over serial according to the predetermined
;   format
;==================================================================
main:
  ;setb 00h                 ; set debug flag
  mov tmod, #20h            ; set timer 1 for auto-reload, mode 2
  mov tcon, #41h            ; run timer 1
  mov th1, #0fdh            ; set 9600 baut rate with 11.059MHz clock
  mov scon, #50h            ; start serial with 8 bit data

  mov p1, #00h              ; initiate the address port to 0
  clr p3.2                  ; turn off the LED bank
loop:
  jnb p3.3, loop            ; do nothing as long as p3.3 is low 
  lcall measure_frame       ; measure one frame
  lcall position_print      ; analyze the frame and print the position
  sjmp loop   

;==================================================================
; measure_frame - this function loops through the 32 led/sensor 
;   pairs and measures each one according to the process
;   measure single. It uses external memory from 1000h-101Fh to
;   store each of the single measurements
;==================================================================
measure_frame:
  mov dptr, #1000h          ; reset the data point to base of stack
frame_loop:
  mov p1, dpl               ; update the reference bank
  lcall stall               ; allow time for switching
  lcall measure_single      ; measure a single LED/Phototransistor pair
  inc dptr                  ; increment data pointer 
  mov r6, dpl               ; move the low of data pointer to r6
  cjne r6, #32, frame_loop  ; until we measure all 32 keep looping

;==================================================================
; measure_single - this function measures a single sensor led pair
;   by first measuring the sensor with the light off, then with
;   the light on and computing the difference between those two
;   voltages. It treats negative differences as 0 and then inverts
;   the values according to some threshold to only obtain non-zero
;   values for actual occlusion events. In debug mode thresholding
;   is not used so as to observe the actual values
;==================================================================
measure_single:
  lcall adc_measure         ; measure from the adc
  clr p3.2                  ; immediately light LED
  mov r0, a                 ; scratchpad store the low value
  lcall stall               ; give time to respond to light
  lcall adc_measure         ; make a measurement
  setb p3.2                 ; turn off the LED now
  clr c                     ; clear the carry for subtraction
  subb a, r0                ; subtract low from high
  jnc threshold             ; if it didn't overflow then threshold
  mov a, #0                 ; if negative we treat it as a 0
threshold:
  jb 00h, store             ; if in debug mode skip the thresholding
  clr c                     ; clear the carry for another subtraction
  mov r0, a                 ; store a into r0
  mov a, #5                 ; put the threshold into a
  subb a, r0                ; subtract the difference from 5
  jnc store                 ; if it didn't overflow then store
  mov a, #00h               ; if negative then store a 0
store:
  movx @dptr, a             ; store the value in the memory bank
  ret 

;==================================================================
; position_print - this function takes a frame of data and prints
;   the values according to the format expected by the listener. In
;   debug mode this consists of space seperated hex values which
;   are all on one line. In run mode it only prints non-zero values
;   and prints the position of that value along with the value
;   itself, seperated by a colon. This saves time by not sending 
;   unnecessary characters for zero data. It still sends blank
;   newlines for empty frames as a seperator for glitches and so
;   the PSoC knows it is still collecting frames.
;==================================================================
position_print:
  mov dptr, #1000h          ; reset dptr to base of stack
  mov r6, #32               ; use r6 to count 32 steps
position_loop:
  movx a, @dptr             ; get value from memory
  jb 00h, value_print       ; if in debug mode print value only
  jz position_loop_end      ; direct to end if value is 0
  lcall prthex              ; print that value
  mov a, #3ah               ; print a colon
  lcall sndchr              ; send the colon
  mov a, dpl                ; put the position in acc
value_print: 
  lcall prthex              ; print that position
  mov a, #20h               ; print a space
  lcall sndchr              ; send space
position_loop_end:  
  inc dptr                  ; increment the data pointer
  djnz r6, position_loop    ; keep count and repeat
  lcall crlf                ; newline for framing
  ret

;==================================================================
; adc_measure - this function makes a single measurement of the 
;   adc0820 and maintains the dptr value by temporarily storing it
;   on the stack. It reads one instruction after initiating
;   conversion because the adc0820 performs a single conversion
;   in 1us which is less than a single external memory read or
;   write operation.
;==================================================================
adc_measure:
  push dpl                  ; save the old dptr
  push dph                  ; on the stack so we can address
  mov dptr, #0fe00h         ; the address of the adc0820
  movx @dptr, a             ; initiate a conversion
  movx a, @dptr             ; conversion complete
  pop dph                   ; return the old dptr
  pop dpl                   ; from what we had before
  ret

;==================================================================
; stall - this function spins the microcontroller for ~20us to
;   allow the sensors to respond to changes in values
;==================================================================
stall:
  mov r7, #10              ; initiate stall counter
  stall_loop:
    djnz r7, stall_loop
  ret

;===============================================================
; subroutine sndchr
; this routine takes the chr in the acc and sends it out the
; serial port.
;===============================================================
sndchr:
   clr  scon.1            ; clear the tx  buffer full flag.
   mov  sbuf,a            ; put chr in sbuf
txloop:
   jnb  scon.1, txloop    ; wait till chr is sent
   ret

;===============================================================
; subroutine getchr
; this routine reads in a chr from the serial port and saves it
; in the accumulator.
;===============================================================
getchr:
   jnb  ri, getchr        ; wait till character received
   mov  a,  sbuf          ; get character
   anl  a,  #7fh          ; mask off 8th bit
   clr  ri                ; clear serial status bit
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

;===============================================================
; subroutine crlf
; crlf sends a carriage return line feed out the serial port
;===============================================================
crlf:
   mov   a,  #0ah         ; print lf
   lcall sndchr
cret:
   mov   a,  #0dh         ; print cr
   lcall sndchr
   ret

