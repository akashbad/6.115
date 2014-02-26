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
; * a ttl feedback input is connected to  P3.2 which    * 
; * will drop low near the resonant frequency and then  * 
; * pull high again after the lamp strike.              * 
; *                                                     * 
; =======================================================

.org 00h
start:
  setb P3.2             ; set the feedback pin high as input
  mov dptr, #0fe03h     ; The 8254 Control Word
  mov a, #36h           ; Set Counter 0 to Mode 3
                        ; and 2 byte loading
  movx @dptr, a         ; Set the control word
  mov dptr, #0fe00h     ; from now on we only address
                        ; the Counter 0 data register  
  sjmp rough_adjust     ; start the adjustment procedure

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
  mov r0, #0a0h         ; start the low byte with 0a0h
                        ; because we'll immediately add 10h 
  mov r1, #00h          ; start the high byte with 00h
rough_loop:  
  mov a, r0             ; move r0 to a to be incremented by 16
  add a, #10h           ; add 16 to the count
  mov r0, a             ; move the new r0 back
  jnc rough_skip_high   ; if we dont hit the carry we can skip
  lcall increment_high  ; otherwise increment the high
rough_skip_high:
  lcall clock_adjust    ; set the clock with the new count
  lcall wait            ; wait for the system to read the new value
  jnb P3.2, fine_adjust ; if the pin drops low, start fine adjust
  sjmp rough_loop       ; go back to loop and set new clock

;========================================================
; fine_adjust - this routine does the next step in
; striking the lamp, which is finely getting to the
; resonant frequency and figuring out when it has been
; struck. We increment the count by 1 at a time here in
; order to have the best resolution. 
;========================================================
fine_adjust:
  inc r0                ; increment r0 as a fine adjustment
  jnc fine_skip_high    ; if we dont hit the carry we can skipe
  lcall increment_high  ; otherwise increment the high
fine_skip_high:  
  lcall clock_adjust    ; adjust the clock
  lcall wait            ; wait for the system to adjust
  jb P3.2, loop         ; once we hit high again just loop
  sjmp fine_adjust      ; back to incrementing


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

;=======================================================
; increment_high - a proc to increment r1 and clear the
; carry which caused this call
;=======================================================
increment_high:
  inc r1                ; increment high
  clr c                 ; clear the carry so we can come back
  ret                   ; back from where we came 

;=======================================================
; wait - sit an spin for a specified amount of time so 
; system can propograte the new clock value. This uses
; r3 and r2 to store counters, allowing us to spin here.
; This procedure waits for (256*32+32)*2+1+2 = 16451us.
;=======================================================
wait:
  mov r3, #20h          ; fill r3 with the outer count value
wait_loop:
  djnz r2, wait_loop    ; spin on r2 for awhile
  djnz r3, wait_loop    ; spin on r3
  ret                   ; return home        

;=======================================================
; loop - just a do nothing loop once the lamp is struck
;=======================================================
loop:
  sjmp loop             ; the lamp is struck, just spin
