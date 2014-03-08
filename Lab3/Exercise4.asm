; Akash Badshah, Lab 3, Exercise 4
; This code will run the 16C450 as
; a connected serial port and interface
; with the AMULET module via serial.
; This basic code configures the UART to
; work and displays any bytes from the AMULET
; on the P1 LEDs

.org 00h
  ljmp start

.org 100h
start:
  lcall init
loop:
  mov dptr, #0fe25h    ; Check the line status register to see if a byte has
  movx a, @dptr        ; been received
  anl a, #01h          
  jz loop

  mov dptr, #0fe20h    ; Read in a byte from the receiver buffer register
  movx a, @dptr
  mov p1, a            ; and display it on the lights

sjmp loop

init:
  mov a, #83h          ; set 8-bit character, no parity, 1 stop bit, DLAB=1
  mov dptr, #0fe23h    ; line control address
  movx @dptr, a

  mov a, #13           ; set division for 9600 baud with xtal=2MHz
  mov dptr, #0fe20h    ; divisor latch address
  movx @dptr, a
  mov a, #00h
  mov dptr, #0fe21h
  movx @dptr, a

  mov a, #03h          ; set DLAB = 0
  mov dptr, #0fe23h    ; line control address
  movx @dptr, a

  mov a, #00h          ; disable interrupts
  mov dptr, #0fe21h    ; interrupt enable register
  movx @dptr, a
  ret
