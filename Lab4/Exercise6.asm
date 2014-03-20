;===============================================================
; * Akash Badshah, Lab 4, Exercise 6                           * 
; * Robot Arm Controlloer                                      * 
; * March 18, 2014                                             * 
; *                                                            * 
; * This program controls a five-axis robot arm which is       * 
; * connected through an 8255 and buffered by multiple 18293   * 
; * chips to provide ample current. The input comes from a set * 
; * of 5 switches which are read as input also through the     * 
; * 8255. This program allows users to select out of 3 speeds  * 
; * of movement using an attached keypad controller.           * 
; * Speed selection is also done through the 8255, using the   * 
; * lower nibble on Port C for the keypad                      * 
;===============================================================

.org 00h
start:
  ljmp init      ; immediately jump to our initialization

.org 03h
  lcall read_keypad     ; Handle incoming keypresses
  reti

.org 0bh
  lcall pwm             ; PWM Timer
  reti

.org 01bh
  lcall read_controller ; Simply read
  reti

.org 100h
;===============================================================
; init - this procedure sets up all of the registers for the 
;   hardware we need. This includes configuring the 8255 with
;   Group A as output and Group B as input, starting Timer 0
;   in mode 2 for PWM, Timer 1 in mode 2 for the controller poll,
;   configuring our data registers, and finally enabling the 3
;   interrupts we use in this program.   
;===============================================================
init:
  mov dptr, #0fe13h     ; location of the 8255 control register
  mov a, #83h           ; Group A is output, Group B is input
  movx @dptr, a         ; push out the 8255
  mov r0, #00h          ; use r0 for the first byte of control data
  mov r1, #00h          ; use r1 for the second byte of control data
  mov tmod #22h         ; Timers 0 & 1 in mode 2
  mov th1, #48h         ; interrupt frequency of 5kHz
  mov th0, #09ch        ; PWM Frequency of 8.3kHz
  setb tr1              ; Run Timer 1
  setb tr0              ; Run Timer 0
  setb it0              ; External Interrupt on Transition
  mov ie, #8Bh          ; enable timer 0,1 & external interrupts
  mov r4, #0ceh         ; high count for pwm
  mov r5, #6ah          ; low count for pwm
  setb 00h              ; start in 100% mode 
loop:
  sjmp loop

;===============================================================
; read_keypad - this procedure reads in the results from a key
;   pad press and updates the speed of the robot arm accordingly
;===============================================================
read_keypad:
  mov dptr, #0fe12h     ; location of 8255 Port C register
  movx a, @dptr         ; grab the keypad byte
  anl a, #03            ; mask off high 6 bits
  jz slow               ; if 0, we are at lowest speed
  cjne a, #01h, fast    ; if 1 we are at middle speed, otherwise fast
medium:
  clr 00h               ; use pwm
  mov r4, #9ch          ; high and low counts are equal for
  mov r5, #9ch          ; a 50% duty cycle
  ret
fast: 
  setb 00h              ; simply ignore the pwm processes
  ret
slow:
  clr 00h               ; use pwm
  mov r4, #0ceh         ; high and low counts are
  mov r5, #6ah          ; these for a 25% duty cycle
  ret

;===============================================================
; pwm - this procedure does the necessary logic to either drive
;   the correct robot arm motors, or pulse them with the duty
;   cycle. To avoid some off-time when doing 100% duty cycle
;   we simply skip the pwm logic in those cases. The correct
;   motors to drive are stored in r2 and r3 while the current
;   state is kept in r0 and r1
;===============================================================
pwm:
  jb 00h, max_duty      ; if we expect 100% duty cycle
  jnb 01h, low          ; if we are in the high part
high:
  mov th0, r4           ; the high count in r4
  clr 01h               ; ready for low
  sjmp max_duty         ; from here same as 100%
low:
  mov th0, r5           ; the low count in r5
  setb 01h              ; ready for high
  mov r0, #00h          ; clear the motors
  mov r1, #00h          ; driving them all low
  lcall update_arm      ; push these nulls out to motors
  ret
max_duty:
  mov a, r2             ; grab the correct states
  mov r0, a             ; from r2 and r3
  mov a, r3             ; and update r0 and r1 with that
  mov r1, a             ; so the motors are driven
  lcall update_arm      ; correctly
  ret

;===============================================================
; update_arm - This procedure takes the current state of the 
;   arm, as represented by r0 & r1 and pushes it out to the arm
;===============================================================
update_arm:
  mov dptr, #0fe10h     ; location of 8255 Port A register
  mov a, r0             ; low byte of control data
  movx @dptr, a         ; update Port A
  mov dptr, #0fe12h     ; location of 8255 Port C register
  mov a, r1             ; high byte of control data
  movx @dptr, a         ; update Port C
  ret

;===============================================================
; read_controller - This procedure reads what the arm controller
;   is currently telling the arm to do. It does so by driving
;   one of the rails high, reading Port B where the controller
;   is connected, then switching which rail is high and reading
;   again. These two bytes are then formatted to be in the same
;   2 byte format as the arm connected to Port A & B, storing
;   this two byte format in r2 & r3. 
;===============================================================
read_controller:
  mov dptr, #0fe11h     ; location of 8255 Port B register
  clr p3.4              ; configure the power pins for cw
  setb p3.5             ; detection on the controller
  movx a, @dptr         ; read in the control pad
  clr p3.5              ; configure the power pins for ccw
  mov r2, a             ; store the clockwise byte in r2
  setb p3.4             ; detection on the controller
  movx a, @dptr         ; read in the control pad
  clr p3.4              ; clear p3.4 so it is normally low
  rr a                  ; rotate the recent byte to the
  rr a                  ; right 3 times so that we can
  rr a                  ; split its pieces to r2 and r3
  mov r3, a             ; store this rotated version in r3 for now
  anl a, #0e0h          ; mask off bottom 5 bits 
  add a, r2             ; add the top 3 bits to r2
  mov r2, a             ; giving us the correct byte
  mov a, r3             ; move r3 to a to process
  anl a, #03h           ; and mask off top 6 bits
  swap a                ; finally swap to get in correct position
  mov r3, a             ; and put it back in r3
  ret

;===============================================================
; rotate_on_motor - This procedure simply rotates the word which
;   represents the on state of the motors, as stored in r0 & r1
;   it does so assuming that there is only 1 on bit in the word.
;   It also accounts for the fact that the upper nibble of PC is
;   used so it swaps the nibbles of r1 before rotating and then
;   swaps back. This also produces 6 cycles of no motor on, when
;   the 1 is propogating through the unused part of port c 
;===============================================================
rotate_on_motor:
  mov a, r0             ; move r0 to a to be rotated
  rlc a                 ; rotate a to the left with the carry
  mov r0, a             ; store that back in r0
  mov a, r1             ; move r1 to a for swapping and rotation
  swap a                ; move the high nibble for port c forward
  rlc a                 ; rotate a to the left with carry
  swap a                ; swap a back again
  mov r1, a             ; store it back in r1  
  ret

