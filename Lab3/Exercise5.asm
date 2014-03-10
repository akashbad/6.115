; =========================================================
; * Akash Badshah, Lab 3, Exercise 5                       * 
; * LazerDillo Controller                                  * 
; * March 9, 2014                                          * 
; *                                                        * 
; * This program runs the Laserdillo and generates         * 
; * lissajous figures using its laser output. It does so   * 
; * by stepping through a stored table of values for a sin * 
; * wave at different rates. This essentially produces     * 
; * sine waves of different frequencies which can be used  * 
; * to create these figures. It also uses either a keypad  * 
; * or the Amulet module (depending on how it feels on a   * 
; * given day) to control which figure is shown and how    * 
; * rotates. The laserdillo is memory mapped to fe3*h and  * 
; * the laser on switch is on p3.2                         * 
; =========================================================

.org 00h
start:
  lcall init     ; Immediately jump to the initialization
  ljmp main      ; Once initialized we can jump to the main

.org 000Bh
  ljmp t0isr     ; Jump to our isr, too big to put here

; =========================================================
; sin_table- This is 256 bytes of storage for our ideal sin
;   wave. We will use the sin_table literal to store the
;   table base and access the bytes here.
; =========================================================
.org 100h
sin_table:
  .db 080h  , 083h , 086h , 089h , 08ch , 08fh , 092h , 095h
  .db 098h  , 09ch , 09fh , 0a2h , 0a5h , 0a8h , 0abh , 0aeh
  .db 0b0h  , 0b3h , 0b6h , 0b9h , 0bch , 0bfh , 0c1h , 0c4h
  .db 0c7h  , 0c9h , 0cch , 0ceh , 0d1h , 0d3h , 0d5h , 0d8h
  .db 0dah  , 0dch , 0deh , 0e0h , 0e2h , 0e4h , 0e6h , 0e8h
  .db 0eah  , 0ech , 0edh , 0efh , 0f0h , 0f2h , 0f3h , 0f5h
  .db 0f6h  , 0f7h , 0f8h , 0f9h , 0fah , 0fbh , 0fch , 0fch
  .db 0fdh  , 0feh , 0feh , 0ffh , 0ffh , 0ffh , 0ffh , 0ffh
  .db 0ffh  , 0ffh , 0ffh , 0ffh , 0ffh , 0ffh , 0feh , 0feh
  .db 0fdh  , 0fch , 0fch , 0fbh , 0fah , 0f9h , 0f8h , 0f7h
  .db 0f6h  , 0f5h , 0f3h , 0f2h , 0f0h , 0efh , 0edh , 0ech
  .db 0eah  , 0e8h , 0e6h , 0e4h , 0e2h , 0e0h , 0deh , 0dch
  .db 0dah  , 0d8h , 0d5h , 0d3h , 0d1h , 0ceh , 0cch , 0c9h
  .db 0c7h  , 0c4h , 0c1h , 0bfh , 0bch , 0b9h , 0b6h , 0b3h
  .db 0b0h  , 0aeh , 0abh , 0a8h , 0a5h , 0a2h , 09fh , 09ch
  .db 098h  , 095h , 092h , 08fh , 08ch , 089h , 086h , 083h
  .db 080h  , 07dh , 07ah , 077h , 074h , 071h , 06eh , 06bh
  .db 068h  , 064h , 061h , 05eh , 05bh , 058h , 055h , 052h
  .db 050h  , 04dh , 04ah , 047h , 044h , 041h , 03fh , 03ch
  .db 039h  , 037h , 034h , 032h , 02fh , 02dh , 02bh , 028h
  .db 026h  , 024h , 022h , 020h , 01eh , 01ch , 01ah , 018h
  .db 016h  , 014h , 013h , 011h , 010h , 0eh  , 0dh  , 0bh
  .db 0ah   , 09h  , 08h  , 07h  , 06h  , 05h  , 04h  , 04h
  .db 03h   , 02h  , 02h  , 01h  , 01h  , 01h  , 01h  , 01h
  .db 00h   , 01h  , 01h  , 01h  , 01h  , 01h  , 02h  , 02h
  .db 03h   , 04h  , 04h  , 05h  , 06h  , 07h  , 08h  , 09h
  .db 0ah   , 0bh  , 0dh  , 0eh  , 010h , 011h , 013h , 014h
  .db 016h  , 018h , 01ah , 01ch , 01eh , 020h , 022h , 024h
  .db 026h  , 028h , 02bh , 02dh , 02fh , 032h , 034h , 037h
  .db 039h  , 03ch , 03fh , 041h , 044h , 047h , 04ah , 04dh
  .db 050h  , 052h , 055h , 058h , 05bh , 05eh , 061h , 064h
  .db 068h  , 06bh , 06eh , 071h , 074h , 077h , 07ah , 07dh

; After the ISRs and the Sine Table we start at 200h for the main
; program
.org 300h
; =========================================================
; init - this is the startup function which configures the
;   hardware being used by the LazerDillo as well as the 
;   registers which store the table step information
; =========================================================
init:
; =========================================================
; init_timer - this function initializes timer 0 so that we
;   can generate 5120 interrupts per second. This means a
;   single step forward in the table produces a 20hz wave
;   and 4 steps gets us our maximum 80hz wave
; =========================================================
init_timer:
  mov tmod, #02h      ; Timer 0 in mode 2
  mov th0, #4ch       ; an Interrupt frequency of 5120hz
  setb tr0            ; run timer 0
  mov ie, #82h        ; enable timer 0 interrupt
; =========================================================
; init_amulet - this function initalizes the 16c450 to be
;    the interface to the amulet module. This block can be
;    commented out  
; =========================================================
init_amulet:
  mov a, #83h         ; set 8-bit character, no parity, 1 stop, DLAB=1
  mov dptr, #0fe23h   ; line control address
  movx @dptr, a       ; send the configuration
 
  mov a, #13          ; the division for a 9600 baud, xtal=2Mhz
  mov dptr, #0fe20h   ; division latch address
  movx @dptr, a
  mov a, #00
  mov dptr, #0fe21h 
  movx @dptr, a

  mov a, #03h         ; set DLAB = 0
  mov dptr, #0fe23h   ; line control address
  movx @dptr, a

  mov a, #00h         ; disable interrupts
  mov dptr, #0fe21h   ; interrupt enable register
  movx @dptr, a
; =========================================================
; init_counters - this function initalizes the registers
;   to the count and incrementation values needed for the
;   the given shape. We assume that b will have a step
;   change of 03.Ch each time, so we only set the step
;   for a, and the counters for both. Additionally we use
;   r6 to store our current rotation offset
; =========================================================
  lcall tie_fighter     ; default to tie_fighter
  clr p3.2              ; turn off the laser by default
  mov r6, #00h
  
ret

; =========================================================
; main - the main loop which pulls input data from either
;   the amulet module or the keypad and then processes the
;   appropriate command for the laserdillo. Thus changing
;   either the figure being shown or the rate of rotation 
; =========================================================
main:
; =========================================================
; amulet_read - this is the subprocess to read in data as 
;   it is sent from the amulet module. This assumes that
;   the amulet is programmed with a custom file which
;   specifies the right values for each button
; =========================================================
amulet_read: 
  ;mov dptr, #0fe25h      ; Check the line status register to see if a byte has
  ;movx a, @dptr          ; been received
  ;anl a, #01h          
  ;jz main

  ;mov dptr, #0fe20h      ; Read in a byte from the receiver buffer register
  ;movx a, @dptr
  ;mov r7, a              ; move it to r7 to be used
; =========================================================
; keypad_read - this is the subprocess to read in data as 
;   it is sent from the keypad module. It also takes care of
;   mapping from the keypad to the appropriate values
; =========================================================
keypad_read:
  jnb p3.4, main          ; loop continuously until we have data available
  clr p3.5                ; set the output enable on
  mov a, p1               ; move the bits from the port into the accumulator
  anl a, #0fh             ; mask off the upper nibble
  lcall keypad_dictionary ; map the keypad to the bytes we expect
  mov r7, a               ; store this value on r7  
  setb p3.5               ; set the output enable back to off
keyup:
  jb p3.4, keyup          ; wait until the data available flag is cleared

; Choose one of the two above blocks and continue from here
tie_fighter_check:        ; now check what the command was
  cjne r7, #0ah, circle_check
  lcall tie_fighter       ; set the counters + steps for tie_fighter
  sjmp main
circle_check:         
  cjne r7, #0bh, a1b4_check
  lcall circle            ; set the counters + steps for circle
  sjmp main
a1b4_check:
  cjne r7, #0ch, rotation_check
  lcall a1b4              ; set the counters + steps for a=1, b=4
  sjmp main
rotation_check:           ; if we didn't have a new figure we can check
  mov a, #10h             ; if its a new rotation speed value
  anl a, r7
  cjne a, #10h, rotation
  cpl p3.2                 ; if its anything else we toggle the laser
  sjmp main              
rotation:
  mov a, r7               ; the rotation value by 2 and then store
  anl a, #0fh             ; once we know its a rotation we multiply
  mov b, #02h             ; it inside of r6
  mul ab
  mov r6, a
  sjmp main 

; =========================================================
; keypad_dictionary - this dictionary maps from the input
;   keypad values to the ones we expect
; =========================================================
keypad_dictionary:
  inc a                   ; increment a to get over the ret instruction
  movc a, @a + pc         ; get the character from the db table and put in a
  ret
  .db   1h, 2h, 3h, 0ah, 4h, 5h, 6h, 0bh, 7h, 8h, 9h, 0ch, 10h, 0h, 10h, 10h

; =========================================================
; tie_fighter - the tie fighter is created with a=1 b=3 and
;   we have the b stepover locked at 3.ch we set the a
;   stepover to 1.4h. 
; =========================================================
tie_fighter:
  mov r0, #40h          ; use step 1.4h for tie_fighter a
  mov r1, #01h
  mov r2, #00h      
  mov r3, #40h          ; start at 90 degrees out of phase
  mov r4, #00h
  mov r5, #00h
  ret

; =========================================================
; circle - the circle is created with a=1 b=1 and we have the
;   b stepover locked at 3.ch we set the a stepover to 3.ch
;   as well. We also set a 90 degree offset to make a circle 
; =========================================================
circle:
  mov r0, #0c0h         ; use step 3.ch for circle a
  mov r1, #03h
  mov r2, #00h
  mov r3, #40h          ; start 90 degrees out of phase
  mov r4, #00h
  mov r5, #00h
  ret

; =========================================================
; a1b4 - this creates the values for a=1 and b=4 and since 
;   we have the b stepover locked at 3.ch we set the a
;   stepover to 0.fh
; =========================================================
a1b4:
  mov r0, #0f0h         ; use step 0.fh for a a1b4 a
  mov r1, #00h
  mov r2, #00h
  mov r3, #00h
  mov r4, #00h
  mov r5, #00h
  ret

; =========================================================
; t0isr - this is the interrupt routine that is serviced
;   5120 times per second. It uses the step values to step
;   through the table and update the value on the two DACs
;   which control the laserdillo 
; =========================================================
t0isr:
  mov a, r2             ; add the low byte of the count
  add a, r0             ; to the low byte of the step
  mov r2, a             ; and store it back
  mov a, r3             ; add the high byte of the count
  addc a, r1            ; to the high byte of the step + carry
  mov r3, a             ; and store it back

  mov a, r6             ; stock a with the rotation offset
  add a, #0c0h          ; default step of 3.ch for b
  add a, r4             ; add in the count value
  mov r4, a
  mov a, r5
  addc a, #03h
  mov r5, a
  
  mov dptr, #sin_table  ; store the base of the sin table in dptr
  mov a, r3             ; the index is stored in r0
  movc a, @a + dptr     ; get the value from the table
  mov dptr, #0fe30h     ; the address of the first axis
  mov b, #2             ; divide by 2 and add 40h
  div ab                ; to keep in the linear range
  add a, #40h           ; of the laserdillo motors
  movx @dptr, a         ; push the value out to motors
  mov dptr, #sin_table  ; repeat again for the other mirror
  mov a, r5             ; the other index in r1
  movc a, @a + dptr
  mov dptr, #0fe31h     ; the address of the second axis
  mov b, #2
  div ab
  add a, #40h
  movx @dptr, a
  reti 
