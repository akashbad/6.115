; Akash Badshah Lab 2, Exercise 5
; This program explores 3 different ways of creating
; a variable frequency square wave with the 8051
; you select which of the methods you want by changing
; which subroutine the entry point points to

.org 0
ljmp interrupt_proc      ; program entry point, will jump to the
                         ; chosen subroutine

.org 000Bh               ; location of timer 0 isr
TOISR:
  cpl P1.0               ; toggle the pin
  reti                   ; return from interrupt

.org 0030h               ; set up the timer after the interrupt space
interrupt_proc:          
  mov TMOD, #02h         ; using timer 1 in mode 2
  mov dptr, #2000h       ; get the external byte from #2000h
  movx a, @dptr
  mov TH0, a             ; use that as our count
  setb TR0,              ; start the timer
  mov IE, #82h           ; enable interrupts
  interrupt_loop:        ; loop
    sjmp interrupt_loop

.org 8100h               ; put these routines later in memory for G8000h
byte_proc:
; This subroutine uses the byte stored in external memory at location
; A000h as the count initializer and counts down from that number
; repeatedly toggling P1.0 when it reaches 0
  mov dptr, #0A000h     ; Point to memory location A000h
  movx a, @dptr         ; move the byte in external memory to acc
  byte_loop_init:
    mov r0, a           ; make r0 the storage location for our counter
  byte_loop:
    djnz r0, byte_loop  ; loop while decrementing r0 
  cpl p1.0              ; toggle p1.0
  sjmp byte_loop_init   ; start it over again

word_proc:
; This subroutine uses the bytes stored in external memory at location
; A000h and A001h as the count initializer. A0001h is the high byte in
; typical little endian style. It counts down from the value indicated
; by both of those bytes combined and toggles P1.0 when reaching 0
  mov dptr, #0A000h              ; Point to memory location A000h
  movx a, @dptr                  ; move the low byte into a
  mov b, a                       ; store that low byte in b for long term
  inc dptr                       ; increment the data pointer
  movx a, @dptr                  ; move the high byte into a
  word_loop_init:
    mov r1, a                    ; make r1 the storage location for our outer counter
    mov r0, b                    ; make r0 the storage location for our inner counter
  word_loop:
    djnz r0, word_loop           ; decrement r0 and jump to the loop
    djnz r1, word_loop           ; decrement r1 and jump to set up r0 again
  cpl p1.0                       ; toggle p1.0
  sjmp word_loop_init            ; start it over again by initializing r1
 
