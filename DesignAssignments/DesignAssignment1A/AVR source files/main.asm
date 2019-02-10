;
; Project1A.asm
;
; Created: 2/9/2019 11:21:57 PM
; Author : Tyler Gardenhire

start:
ldi r25, 0xFF ;upper register used for multiplicand (16-bit value)
ldi r24, 0xFF ;lower register used for multiplicand (16-bit value)
ldi r22, 0xFF ;register used for multiplier (8-bit value)
ldi r23, 0    ;register used to hold 0

loop:         ;adds the multiplicand to itself multiplier number of times
add r18, r24  ;add bottom group of bits
adc r19, r25  ;if overflow, add next group of bits
adc r20, r23  ;if more overflow, add top group of bits
dec r22       ;r22 is now used as a "counter"
cp r22, r23   ;compare counter to zero
brne loop     ;if they are not equal, jump to start of loop

done: jmp done

