; Akash Badshah, Final Project, Scratchpad
; This is just a file to use for scratchpad code in testing
; small circuits and quick code

.org 00h
start:
  loop: 
    djnz r0, loop
    djnz r1, loop
  cpl p1.0
  sjmp loop
