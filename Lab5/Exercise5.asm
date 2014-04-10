;=================================================================
; * Akash Badshah, Lab 5, Exercise 5                             * 
; * Closed Loop Buck Regulator                                   * 
; * April 9, 2014                                                * 
; *                                                              * 
; * This program controls an external buck regulator and uses    * 
; * an ADC to sample the output voltage of this regulator,       * 
; * providing a closed loop feedback system that operates        * 
; * the regulator with pwm through the 8254. The 8245 uses PWM   * 
; * with a f = 40kHz and 250 selectable duty cycles. The voltage * 
; * is sampled at 2kHz and displayed on the LCD every 256 reads * 
; *                                                             * 
; * Register Usage Description:                                 * 
; * r0 -                                                        * 
; * r1 -                                                        * 
; * r2 - lcd update period                                      * 
; * r3 - lcd delay counter                                      * 
; * r4 - lcd s line reference                                   * 
; * r5 - second counter                                         * 
; * r6 - second counter                                         * 
; * r7 - second counter                                         * 
;=================================================================

.org 00h
start:
  ljmp init           ; immediatedly initialize

.org 000Bh
  ljmp t0isr          ; jump to our isr for timer 0

.org 100h
;=================================================================
; init - this is the initialization function which sets up the
;   8245 as a pwm generator, our interrupts, and our lcd
;=================================================================
init:
  mov tmod, #02h      ; using timer 0 in mode 2
  mov th0, #1ah       ; generate interrupts at 4kHz
  setb tr0            ; start the timer
  mov ie, #82h        ; enable timer 0 interrupt
  mov dptr, #0fe03h   ; 8254 config register
  mov a, #14h         ; Timer 0 in mode 2
  movx @dptr, a       ; push it out
  mov dptr, #0fe00h   ; address of timer 0
  mov a, #0fah        ; 40kHz waves
  movx @dptr, a       ; push it out
  mov dptr, #0fe03h   ; 8254 config register
  mov a, #52h         ; Timer 1 in mode 1
  movx @dptr, a       ; push it out
  mov dptr, #0fe01h    ; address of timer 1
  mov a, #7dh         ; duty cycle
  movx @dptr, a       ; set the duty cycle
  mov dptr, #0fe13h   ; configure the 8255
  mov a, #80h         ; all ports output
  movx @dptr, a       ; push to the 8255
  lcall init_lcd      ; initialize the lcd
  mov dptr, #1001h    ; gain variable address
  mov a, #2           ; gain value
  movx @dptr, a       ; store that gain 
loop:
  mov dptr, #1000h    ; location of reference voltage
  mov a, #80h         ; 1/2 of 5 volts
  movx @dptr, a       ; update reference voltage
  lcall two_second_stall
  mov dptr, #1000h    ; location of reference voltage
  mov a, #00h         ; 1/2 of 5 volts
  movx @dptr, a       ; update reference voltage
  lcall two_second_stall
  sjmp loop

;=================================================================
; t0isr - this is the timer 0 interrupt which is called at 4kHz,
;   it immediately flips and checks a bit to see if we should run
;   the routine because it need only run at 2kHz. It samples the
;   ADC, displays the output on the LCD and updates our PWM duty
;   cycle according to the gain and error
;=================================================================
t0isr:
  cpl 00h
  jb 00h, exit        ; if set then we immediately exit
  lcall adc_read      ; otherwise read the adc
  mov r0, a           ; store the value in r0 for arithmetic
  mov dptr, #1000h    ; get reference voltage
  movx a, @dptr       ; obtain from memory
  clr c               ; clear the carry for a subtraction
  subb a, r0          ; subtract actual value from reference
  jc negative         ; if it was negative jump to set 0
  mov dptr, #1001h    ; address of the gain variable
  mov b, a            ; move the error to b
  movx a, @dptr       ; get the gain variable
  mul ab              ; get the scaled gain
  xch a, b            ; swap a and b to see if overflowing
  jnz overflow        ; if we have greater than 1 byte we overflow
  mov dptr, #0fe01h   ; address of timer 1
  xch a, b            ; switch a and b back
  movx @dptr, a       ; push out the new duty cycle  
  sjmp lcd_updater    ; check if we need to update lcd
negative:
  mov dptr, #0fe01h   ; timer 1 count address
  mov a, #01h         ; the all low value
  movx @dptr, a       ; push it out
  sjmp lcd_updater    ; check if we need to update lcd
overflow:
  mov dptr, #0fe01h   ; timer 1 count address
  mov a, #0fah        ; max duty cycle
  movx @dptr, a       ; push it out
  sjmp lcd_updater    ; check if we need to update lcd
lcd_updater:
  djnz r2, exit       ; countdown for lcd
  mov a, r0           ; get the read value back
  lcall prt_voltage   ; write it out
  inc r1
  mov a, r1           ; new value for duty cycle
  mov dptr, #0fe01h   ; timer 1 address
  movx @dptr, a       ; update
exit:
  reti

;=================================================================
; init_lcd - this subroutine runs the setup commands
;   necessary to program the lcd in the right modes
;   for our display. This includes the right data
;   settings, character set, and number of lines
;   also turning on the display and clearing it 
;=================================================================
init_lcd:
  mov a, #38h             ; 8-bit, 5x7 char set, 2 lines
  lcall lcd_command       ; execute command
  mov a, #0Ch             ; turn display on, hide cursor
  lcall lcd_command       ; execute command
  mov a, #01h             ; clear display
  lcall lcd_command       ; execute command
  lcall lcd_reset         ; reset cursor
  ret

;=================================================================
; lcd_reset - this subroutine runs the commands to
;   clear and reset the cursor of the lcd
;=================================================================
lcd_reset:
  mov a, #80h             ; set RAM address to 0
  lcall lcd_command       ; execute command
  ret

;=================================================================
; lcd_write - this subroutine does the necessary latching
;   of the enable lines using the data in a to write to
;   the lcd. The value of the r/s line is controlled by
;   adding the value of the r4 register
;=================================================================
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

;=================================================================
; lcd_command - this subroutine uses the lcd_write procedure
;   but makes sure the r/s line is low to send commands
;=================================================================
lcd_command:
  mov r4, #00h            ; drive r/s low
  ljmp lcd_write          ; jump, it will do the ret

;=================================================================
; lcd_data - this subroutine uses the lcd_write procedure
;   but makes sure the r/s line is high to send data
;=================================================================
lcd_data:
  mov r4, #02h            ; drive r/s high
  ljmp lcd_write          ; jump, it will do the ret


;=================================================================
; prt_voltage - this subroutine takes the value stored in acc and
;   prints out a decimal representation of a voltage between 0 & 5
;   volts with 1 decimal point of precision
;=================================================================
prt_voltage:
  push acc                 ; store the acc so we have a copy
  lcall lcd_reset          ; reset the lcd cursor to 0
  pop acc                  ; get back the acc
  mov b, #51               ; a single volt in b
  div ab                   ; divide a by b
  add a, #30h              ; turn a into its ascii equivalent
  lcall lcd_data           ; write that value 
  mov a, #2eh              ; period character
  lcall lcd_data           ; push out a digit
  mov a, b                 ; get the remainder into a
  mov b, #5                ; a tenth of a volt in b
  div ab                   ; divide a by b again
  add a, #30h              ; turn a to ascii equivalent
  lcall lcd_data
  ret

;=================================================================
; adc_read - this subroutine reads a value from the adc
;   putting the byte in a
;=================================================================
adc_read:
  mov dptr, #0fe20h       ; address of the adc
  movx @dptr, a           ; initiate a conversion
adc_wait:
  jb p3.2, adc_wait       ; wait for conversion to finish
  movx a, @dptr           ; get the value of the adc to a
  ret

;=================================================================
; two_second_stall - this subroutine basically spins
;   the clock for 2 second at a time
;=================================================================
two_second_stall:
  mov r5, #0eh             ; 14 total loops
two_second_loop:
  djnz r7, two_second_loop
  djnz r6, two_second_loop
  djnz r5, two_second_loop
  ret

