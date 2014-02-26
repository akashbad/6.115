; Akash Badshah, Lab 2, Exercise 3
; This simple program reads two bytes from
; sequential memory and performs a variety
; of arithmetic operations on those bytes
; specifically it reads from 9000h and 9001h
; and stores the sum, difference, product, and
; quotient in the next external memory locations

mov dptr, #9000h        ; move 9000h to the dptr
movx a, @dptr           ; get our first value and put in acc
mov r0, a               ; r0 is permanent storage for byte 1
inc dptr                ; increment the dptr
movx a, @dptr           ; get our first value and put in acc
mov r1, a               ; r1 is permanent storage for byte 2
; Addition
add a, r0               ; add the first value to r1 in acc
acall store
; Subtraction
mov a, r0               ; set up the acc with the first value
subb a, r1              ; subtract r1 from r0
acall store
; Multiplication
mov a, r0               ; reload a with r0
mov b, r1               ; set up b with r1
mul ab                  ; mutiply the two numbers
acall store
mov a, b                ; move the high byte of the multiplication to the location
acall store
; Division
mov a, r0               ; again set up a with r0
mov b, r1               ; set up b with r1
div ab                  ; divide a by b
acall store
mov a, b                ; put the remainder in a
acall store
; Reset the 8051
ljmp 0h                 ; reset and start from the beginning of the program again

store:
  inc dptr              ; increment the data pointer
  movx @dptr, a         ; store the accumulator into the external address
  ret
