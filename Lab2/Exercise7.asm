; =======================================================
; * Akash Badshah, Lab 2, Exercise 7                    * 
; * CFL Ballast Controller                              * 
; * February 26, 2014                                   * 
; *                                                     * 
; * This program scans through a range of frequencies   * 
; * looking for the resonant frequency of a connected   * 
; * CFL Ballast. It should hit close enough to the      * 
; * resonant frequency to strike the lamp and settle    * 
; * to a steady state.                                  * 
; *                                                     * 
; * This program assumes an 8254 is connected in a      * 
; * memory mapped configuration, using FE00h-FE03h to   * 
; * communicate with it's 4 registers. It also assumes  * 
; * a ttl feedback input is connected to  P3.x which    * 
; * will drop low near the resonant frequency and then  * 
; * pull high again after the lamp strike.              * 
; *                                                     * 
; =======================================================

.org 00h
start:
  setb P3.0             ; set the feedback pin high as input
  mov dptr, #0fe03h     ; The 8254 Control Word
  mov a, #36h           ; Set Counter 0 to Mode 3
                        ; and 2 byte loading
  movx @dptr, a         ; Set the control word
  mov dptr, #0fe00h     ; from now on we only address
                        ; the Counter 0 data register  

;========================================================
; rough_adjust - this routine does the first step in
; striking the lamp, getting close to the resonant
; frequency. It starts with a count of 00b0h which is a 
; starting frequency of 56.818kHz which is well above the
; resonant frequency of our ballast. We then increment
; the count by 16 at a time by adding 10h to the count.
; We repeat this until the feedback pin drops to low
; in which case we enter the fine adjustment loop.
;========================================================
rough_adjust:
  mov r0, #0b0h         ; start the low byte with 0b0h 
  mov r1, #00h          ; start the high byte with 00h
rough_loop:
  lcall clock_adjust    ; set the clock with the new count
  jnb P3.0, fine_adjust ; if the pin drops low, start fine adjust
  mov a, r0             ; move r0 to a to be incremented by 16
  add a, #10h           ; add 16 to the count
  mov r0, a             ; move the new r0 back
  jc increment_high     ; if we hit the carry we should increment high
  sjmp rough_loop       ; go back to loop and set new clock
increment_high:
  inc r1                ; increment high
  clr c                 ; clear the carry so we can come back
  sjmp rough_loop       ; go back to the main rough loop 

;========================================================
; fine_adjust - this routine does the next step in
; striking the lamp, which is finely getting to the
; resonant frequency and figuring out when it has been
; struck. We increment the count by 1 at a time here in
; order to have the best resolution. We assume that the 
; high byte will not change because our range of expected
; resonant frequencies specifies it would be 01h
;========================================================
fine_adjust:
  inc r0                ; increment r0 as a fine adjustment
  lcall clock_adjust    ; adjust the clock
  jb P3.0, loop         ; once we hit high again just loop
  sjmp fine_adjust      ; back to incrementing

;=======================================================
; loop - just a do nothing loop once the lamp is struck
;=======================================================
loop:
  sjmp loop             ; the lamp is struck, just spin

; ======================================================
; clock_adjust - this routine uses the value stored in
; R0 as the low byte of the Counter 0 data and the value
; in R1 as the high byte of the Counter 0 and then loads
; those values into the Counter 0 register, lsb first.
; It assumes that the DPTR is already at FE00h
; ======================================================
clock_adjust:
  mov a, r0             ; get the low byte ready to be sent
  movx @dptr, a         ; put the low byte in
  mov a, r1             ; get the high byte ready to be sent
  movx @dptr, a         ; put the high byte in
  ret                   ; return back to our caller
