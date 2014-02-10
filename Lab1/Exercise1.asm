; Akash Badshah, Lab1, Exercise 1
; This little program turns an LED on.

lcall pat
loop:
  sjmp loop

; Subroutine for Exercise 1.1, least significant bit lighting
lsb:
  mov p1, #00h       ; Clear the LED bank
  mov p1, #01h       ; Turn on a single light
  ret

; Subroutine for Exercise 1.2, most significant bit lighting
msb:
  mov p1, #00h        ; Clear the LED bank
  mov p1, #80h        ; Turn on the last light
  ret

; Subroutine for Exercise 1.3, bitwise operators
bit:
  mov p1, #80h        ; Fill the LED bank with 1 light on
  clr p1.7            ; Clear the light on the msb
  setb p1.0           ; set the light on the lsb
  ret

; Subroutine for Exercise 1.4, static pattern
; simply use the hexcode for 01010101b to make
; an alternating light pattern
stat:
  mov p1, #55h        ; Fill the LED bank with the binary pattern 01010101b
  ret

; Subroutine for Exercise 1.5, a dynamic pattern
pat:
  mov  a, #11         ; Start with a random seed of two LEDs on
  step:
    mov p1, a         ; move the contents of register a into p1
    pat_loop:
      djnz r0, pat_loop   ; increment 255 times using djnz to spend time
      djnz r1, pat_loop   ; repeat that loop 255 times to increase stall time
    rl a              ; rotate the bits in a left to mix up the pattern
    swap a            ; switch the nibbles in a for more pattern action
    sjmp step         ; jump back to the step to set the lights and keep the pattern going

