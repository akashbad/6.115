; Akash Badshah, Lab 4, Exercise 5
; This code generates PWM waves on an external
; 8255 Port A. The PWM waves are generated using
; Timer 0 interrupts and by changing the th0 value
; The value for the duty cycle is grabbed from
; external memory so as to allow for easy changing
; without recompiling. Alternatively, if the program
; starts by jumping to external, it will use the
; connected 8254 to generate PWM, again using the
; external byte to select the duty cycle

.org 00h
lcall internal
loop:
  sjmp loop

.org 00bh
ljmp TOISR

.org 30h
TOISR:
  mov dptr, #0fe10h   ; get dptr ready
  jnc low             ; if the carry is not set we go low
high:  
  mov th0, r1         ; otherwise high 
  clr c               ; clear the carry
  mov a, #01          ; get a ready for high
  movx @dptr, a       ; send out to port
  reti
low:
  mov th0, r2         ; put low pwm counter in
  setb c              ; set the carry
  mov a, #00          ; get a ready for low
  movx @dptr, a       ; send out to port
  reti

.org 100h
; This procedure establishes PWM using the internal
; Timer 0 and interrupts as serviced by the T0ISR.
; It uses timer 0 in mode 2 and each interrupt switches
; the value in th0 so the count will be different
; on the next reload. It alternates between the count
; for high and low, giving a specified duty cycle.
; This can be chosen by setting the byte in 2000h
internal:
  mov dptr, #2000h    ; address of external count byte
  movx a, @dptr       ; get that into a
  mov r0, a           ; scratchpad into r0
  mov a, #255         ; subtract from 255 because the
  subb a, r0          ; timer counts up
  mov r1, a           ; Store rh in r1  
  mov a, #80          ; Time to get the low part
  subb a, r0          ; Low time of (80-r0)/80
  mov r0, a           ; scratchpag into r0
  mov a, #255         ; do it again because of
  subb a, r0          ; timer counting up
  mov r2, a           ; Store rl in r2
  mov dptr, #0fe13h   ; control byte for 8255
  mov a,  #80h        ; everything is output
  movx @dptr, a       ; program it
  mov dptr #0fe10h    ; Port A address
  mov a, #01h         ; start high
  mov tmod, #02h      ; timer 0 mode 2
  mov th0, r1         ; high counter
  movx @dptr, a       ; set the pin
  setb tr0            ; start timer
  mov ie, #82h        ; enable interrupts
  clr c               ; clear the carry so we go low
  ret

external:
  mov dptr, #0fe03h    ; address for control word
  mov a, #34h          ; Timer 0, Mode 2, 2 bytes
  movx @dptr, a        ; program the timer
  mov dptr, #0fe00h    ; Timer 0 count address
  mov a, #0e8h         ; low byte for 1000 count
  movx @dptr, a        ; Set low byte of count
  mov a, #03h          ; high byte for 1000 count
  movx @dptr, a        ; set high byte of count
  mov dptr, #0fe03h    ; control register again
  mov a, #72h          ; Timer 1, Mode 1, 2 bytes
  movx @dptr, a        ; program timer 1
  mov dptr, #2000h     ; external count byte
  movx a, @dptr        ; grab that count byte
  mov dptr, #0fe01h    ; Timer 1 count address
  movx @dptr, a        ; put low count byte
  mov dptr, #2001h     ; second external count byte
  movx a, @dptr        ; grab high byte into a
  mov dptr, #0fe01h    ; Timer 1 count address
  movx @dptr, a        ; put high count byte
  ret
  
