; Akash Badshah, Lab 3, Exercise 3
; This program outputs a sin wave to the
; DAC connected to memory address FE10 via
; our external chip interface. The sin wave
; is generated via a stored table

.org 00h
loop:
  inc r0            ; our counter location is r0
  mov a, r0         ; put that value of r0 in to a 
  lcall update_wave ; now we call away to actually update the sin wave
  ; This following table of data represents a single period of a sin wave
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

; This function uses the face that it was lcalled to get
; a reference to the table which is next up in memory
; It gets the offset in the table from a (which was in r0)
; and then pushes it out the DAC
update_wave:
  pop dph             ; get the pc into the dptr
  pop dpl             ; so we can find the sin table
  movc a, @a + dptr   ; get the value from the able and put in a
  mov dptr, #0fe10h   ; set up the dptr for the dac
  mov b, #10          ; divide the value by 10 as part of our extension
  div ab              ; perform the actual division
  movx @dptr, a       ; store the value in the dac
  ljmp loop           ; go back to the top of the loop
