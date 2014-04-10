; Akash Badshah, Lab 5, Exercise 2
; This is an experiment with software feedback loops
; Setting a value on the DAC and seeing how the plant
; Of an RC circuit responds to this voltage. We use
; the ADC to measure the output voltage, as well as
; The LCD to display this value. An external gain
; is set using the byte in 1000h
; Register usage:
; r0 - second counter
; r1 - second counter
; r2- second counter
; r3 - lcd delay counter
; r4 - lcd s line reference 
; r5 - prthex scratchpad
; r6 - feedback scratchpad
; r7 - reference voltage


.org 00h
start:
  ljmp init               ; jump to initialization

.org 000Bh
  ljmp T0ISR              ; jump to timer 0 isr

.org 100h
init:
  mov tmod, #01h          ; use timer 0 in mode 1
  mov th0, #0e3h          ; ms byte of counter
  mov tl0, #33h           ; ls byte of counter
  setb tr0                ; start the timer
  mov ie, #82h            ; enable interrupts
  mov dptr, #2000
  mov dptr, #0fe13h       ; configure the 8255
  mov a, #80h             ; all ports output
  movx @dptr, a           ; push to the 8255
  lcall init_lcd          ; initialize the lcd
loop:  
  lcall two_second_stall
  mov r7, #80h            ; set reference to 128
  lcall update_lcd        ; update values on lcd
  lcall two_second_stall
  mov r7, #00h            ; set reference to 0
  lcall update_lcd        ; update values on lcd
  sjmp loop

T0ISR:
  mov th0, #0e3h          ; set timer back up
  mov tl0, #37h           ; set back up, with offset for this
  lcall adc_read          ; read the adc
  mov r6, a               ; use r6 as scratchpad
  mov a, r7               ; move reference to a for subtraction
  clr c                   ; clear the carry for subtraction
  subb a, r6              ; subtract actual from ref
  jc negative             ; if it was negative jump to set 0
  setb p1.0
  mov dptr, #1000h        ; address of gain variable
  mov b, a                ; mov the error to b
  movx a, @dptr           ; get the gain
  mul ab                  ; multiply error by gain
  xch a, b                ; swap a and b
  jnz overflow            ; there is a value above 0 in upper byte 
  mov dptr, #0fe30h       ; dac address
  xch a, b                ; get back the value
  movx @dptr, a           ; push it out
  reti
negative:
  mov dptr, #0fe30h       ; dac address
  mov a, #00h             ; zero to be writter
  movx @dptr, a           ; push it out
  reti
overflow:
  mov dptr, #0fe30h       ; dac address
  mov a, #0ffh            ; maximum on dac
  movx @dptr, a           ; push it out       
  reti

; two_second_stall - this subroutine basically spins
;   the clock for 1 second at a time
two_second_stall:
  mov r0, #0eh             ; 14 total loops
two_second_loop:
  djnz r2, two_second_loop
  djnz r1, two_second_loop
  djnz r0, two_second_loop
  ret

; init_lcd - this subroutine runs the setup commands
;   necessary to program the lcd in the right modes
;   for our display. This includes the right data
;   settings, character set, and number of lines
;   also turning on the display and clearing it 
init_lcd:
  mov a, #38h             ; 8-bit, 5x7 char set, 2 lines
  lcall lcd_command       ; execute command
  mov a, #0Ch             ; turn display on, hide cursor
  lcall lcd_command       ; execute command
  mov a, #01h             ; clear display
  lcall lcd_command       ; execute command
  lcall lcd_reset         ; reset cursor
  ret

; lcd_reset - this subroutine runs the commands to
;   clear and reset the cursor of the lcd
lcd_reset:
  mov a, #80h             ; set RAM address to 0
  lcall lcd_command       ; execute command
  ret

; lcd_write - this subroutine does the necessary latching
;   of the enable lines using the data in a to write to
;   the lcd. The value of the r/s line is controlled by
;   adding the value of the r4 register
lcd_write:
  push acc                ; temporarily store the acc
  mov dptr, #0fe12h       ; e & r/s lines
  mov a, #00h             ; drive both lines low
  add a, r4               ; add in the state of the r/s line
  movx @dptr, a           ; push out
  mov dptr, #0fe10h       ; data location
  pop acc                 ; get back our command byte
  movx @dptr, a           ; push command out
  mov dptr, #0fe12h       ; e & r/s lines
  mov a, #01h             ; drive the e line high
  add a, r4               ; add in the state of the r/s line
  movx @dptr, a           ; push out
  mov a, #00h             ; pull e line low
  add a, r4               ; add in the state of the r/2 line
  movx @dptr, a           ; latch the command
  mov r3, #1h
lcd_stall:                ; allow the lcd to settle with this value
  nop
  djnz r3, lcd_stall
  ret

; lcd_command - this subroutine uses the lcd_write procedure
;   but makes sure the r/s line is low to send commands
lcd_command:
  mov r4, #00h            ; drive r/s low
  ljmp lcd_write          ; jump, it will do the ret

; lcd_data - this subroutine uses the lcd_write procedure
;   but makes sure the r/s line is high to send data
lcd_data:
  mov r4, #02h            ; drive r/s high
  ljmp lcd_write          ; jump, it will do the ret


; update_lcd - this subtroutine writes the ref value
;   and the gain value to the lcd in order to show 
;   what we are currently trying to do
update_lcd:
  lcall lcd_reset
  mov a, #'R'
  lcall lcd_data
  mov a, #'E'
  lcall lcd_data
  mov a, #'F'
  lcall lcd_data
  mov a, #':'
  lcall lcd_data
  mov a, r7
  lcall prthex
  mov a, #' '
  lcall lcd_data
  mov a, #'G'
  lcall lcd_data
  mov a, #'A'
  lcall lcd_data
  mov a, #'I'
  lcall lcd_data
  mov a, #'N'
  lcall lcd_data
  mov a, #':'
  lcall lcd_data
  mov dptr, #1000h
  movx a, @dptr
  lcall prthex
  ret 

;===============================================================
; subroutine prthex
; this routine takes the contents of the acc and prints it out
; as a 2 digit ascii hex number to the lcd
;===============================================================
prthex:
   push acc
   lcall binasc           ; convert acc to ascii
   lcall lcd_data         ; print first ascii hex digit
   mov   a,  r5           ; get second ascii hex digit
   lcall lcd_data         ; print it to lcd
   pop acc
   ret
;===============================================================
; subroutine binasc
; binasc takes the contents of the accumulator and converts it
; into two ascii hex numbers.  the result is returned in the
; accumulator and r5.
;===============================================================
binasc:
   mov   r5, a            ; save in r5
   anl   a,  #0fh         ; convert least sig digit.
   add   a,  #0f6h        ; adjust it
   jnc   noadj1           ; if a-f then readjust
   add   a,  #07h
noadj1:
   add   a,  #3ah         ; make ascii
   xch   a,  r5          ; put result in reg 2
   swap  a                ; convert most sig digit
   anl   a,  #0fh         ; look at least sig half of acc
   add   a,  #0f6h        ; adjust it
   jnc   noadj2           ; if a-f then re-adjust
   add   a,  #07h
noadj2:
   add   a,  #3ah         ; make ascii
   ret

; adc_read - this subroutine reads a value from the adc
;   putting the byte in a
adc_read:
  mov dptr, #0fe20h       ; address of the adc
  movx @dptr, a           ; initiate a conversion
adc_wait:
  jb p3.2, adc_wait       ; wait for conversion to finish
  movx a, @dptr           ; get the value of the adc to a
  ret

.org 1000h
  .db 2
