; Akash Badshah, Lab 4, Exercise 8
; This program reads an analog voltage in from the
; ADC0804 which is memory mapped into the FE2*h slot
; In addition, the ADC0804 interrupt is driven through
; the external interrupt 1, connected to P3.3

.org 0h
start:
  ljmp init

.org 013h
  ljmp IE1ISR

.org 100h:
init:
  mov ie, #84h      ; Enable external interrupt 1
  mov dptr, #0fe20h ; the ADC register
  movx @dptr, a     ; doesn't matter what we send, start conversion
loop:
  sjmp loop

IE1ISR:
; An external interrupt service routine which grabs the
; value from the ADC, puts it out to the port and then
; starts a new conversion
  mov dptr, #0fe20h
  movx a, @dptr     ; get the value from adc
  mov p1, a         ; display on p1
  movx @dptr, a     ; start another conversion
  reti
