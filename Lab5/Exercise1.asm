; Akash Badshah, Lab 5, Exercise 1
; This simple program configures the LCD which is
; connected to Port A of the 8255 for data and PC.0-1
; of the same 8255 for the E and RS lines. This program
; either reads in a string of length 12 from stored
; memory starting at location 1000h or acts as
; a voltmeter, reading in the value from the ADC
; converting to correct characters and then displaying
; that on the LCD

.org 00h
start:
  mov dptr, #0fe13h       ; configure the 8255
  mov a, #80h             ; all ports output
  movx @dptr, a           ; push to the 8255
  lcall init_lcd          ; initialize the lcd
  ljmp voltmeter         ; change this value to run the right program

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
  mov a, #80h             ; set RAM address to 0
  lcall lcd_command       ; execute command
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
;   adding the value of the r7 register
lcd_write:
  push acc                ; temporarily store the acc
  mov dptr, #0fe12h       ; e & r/s lines
  mov a, #00h             ; drive both lines low
  add a, r7               ; add in the state of the r/s line
  movx @dptr, a           ; push out
  mov dptr, #0fe10h       ; data location
  pop acc                 ; get back our command byte
  movx @dptr, a           ; push command out
  mov dptr, #0fe12h       ; e & r/s lines
  mov a, #01h             ; drive the e line high
  add a, r7               ; add in the state of the r/s line
  movx @dptr, a           ; push out
  mov a, #00h             ; pull e line low
  add a, r7               ; add in the state of the r/2 line
  movx @dptr, a           ; latch the command
  mov r2, #1h
lcd_stall:                ; allow the lcd to settle with this value
  nop
  djnz r1, lcd_stall
  ret

; lcd_command - this subroutine uses the lcd_write procedure
;   but makes sure the r/s line is low to send commands
lcd_command:
  mov r7, #00h            ; drive r/s low
  ljmp lcd_write          ; jump, it will do the ret

; lcd_data - this subroutine uses the lcd_write procedure
;   but makes sure the r/s line is high to send data
lcd_data:
  mov r7, #02h            ; drive r/s high
  ljmp lcd_write          ; jump, it will do the ret

; table_string - this subroutine gets a 12 character string
;   from memory starting at location 1000h which will be 
;   displayed on the lcd screen
table_string:
  mov r0, #00             ; start at location 0
char_loop:  
  mov dptr, #1000h        ; location of the bytes
  mov a, r0               ; the offset in r0
  movc a, @a + dptr       ; get the value from the table
  lcall lcd_data          ; display the data on the screen
  inc r0                  ; increment up
  cjne r0, #12, char_loop ; loop if not 12
loop:
  sjmp loop

; adc_read - this subroutine reads a value from the adc
;   putting the byte in a
adc_read:
  mov dptr, #0fe20h       ; address of the adc
  movx @dptr, a           ; initiate a conversion
adc_wait:
  jb p3.2, adc_wait       ; wait for conversion to finish
  movx a, @dptr           ; get the value of the adc to a
  ret

; voltmeter - this subroutine polls the ADC for a value
;   and then displays that value to 2 significant digits
;   on the lcd screen
voltmeter:
  lcall lcd_reset
  lcall adc_read
  mov b, #51              ; a single volt in b
  div ab                  ; divide a by b
  add a, #30h             ; change to ascii
  lcall lcd_data          ; push the ones digit out
  mov a, #2eh             ; period character
  lcall lcd_data          ; push out a digit
  mov a, b                ; get the remainder in a
  mov b, #5               ; a single digit in b
  div ab                  ; divide a by b again
  add a, #30h             ; change to ascii
  lcall lcd_data          ; push the tens digit out  
  sjmp voltmeter

copier:
  lcall adc_read
  mov dptr, #0fe30h        ; address of the dac
  movx @dptr, a            ; push the value out to the dac
  mov r0, #200
copier_stall_0: djnz r0, copier_stall_0
  mov r0, #200
copier_stall_1: djnz r0, copier_stall_1
  sjmp copier 

.org 1000h
  .db "6.115 Rules!"           
