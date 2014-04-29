;===============================================================
; R31JP PSoC Peripheral Code
;===============================================================

.org 00h
ljmp main

.org 100h
main:
   lcall init
   mov dptr, #300h      ; pc of message
   mov a, #0h
   mov r0, #14d         ; length of message
   loop:
      push acc          ; save table position
      movc a, @a+dptr
      lcall sndchr
      inc dptr
      pop acc
      djnz r0, loop
        mov dptr, #300h
        mov r0, #14d
        mov a, #0h       ; reset counter
        sjmp loop 

.org 300h
.db "6.115 Rocks!! "     ; message to be displayed on LCD



;=================================================================
; subroutine init
; this routine initializes the hardware
; set up serial port with a 11.0592 MHz crystal,
; use timer 1 for 9600 baud serial communications
;=================================================================
init:
   mov   tmod, #20h       ; set timer 1 for auto reload - mode 2
   mov   tcon, #41h       ; run counter 1 and set edge trig ints
   mov   th1,  #0fdh      ; set 9600 baud with xtal=11.059mhz
   mov   scon, #50h       ; set serial control reg for 8 bit data
                          ; and mode 1
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
