;
; Project1B.asm
;
; Created: 2/23/2019 6:31:12 PM
; Author : Tyler Gardenhire
;


	.include <m328pdef.inc> ;standard library
	.EQU STARTADDS = 0x0200 ;starting address
	.EQU DIVBY3 = 0x0400    ;starting address of numbers divisible by 3
	.EQU NOTDIVBY3 = 0x0600 ;starting address of numbers not divisible by 3


    ldi r20, 99 ;counter
	ldi r21, 11 ;numbers stored in memory
	ldi r22, 0  ;zero

	ldi XL, low(STARTADDS)  ;stores lower address value (0x00)
	ldi XH, high(STARTADDS) ;stores higher address value (0x02)
	ldi YL, low(DIVBY3)     ;stores lower address value (0x00)
	ldi YH, high(DIVBY3)    ;stores higher address value (0x04)
	ldi ZL, low(NOTDIVBY3)  ;stores lower address value (0x00)
	ldi ZH, high(NOTDIVBY3) ;stores higher address value (0x06)

	store: st X+, r21		;loop to store numbers
	inc r21					;increment the value to store
	dec r20					;decrement counter
	brne store				;if counter not equal to 0, loop to store

	ldi XL, low(STARTADDS)  ;load lower address value to read values from
	ldi XH, high(STARTADDS) ;load higher address value to read
	ldi r20, 99				;re-load counter

	check: ld r23, X+ ;checks for divisibility by 3
	mov r24, r23	  ;use r24 as temp value for divisibility

	divisibility: subi r24, 3	;subtract by 3
	breq divisibleby3			;if 0, value is divisible by 3
	brmi notdivisibleby3		;if negative, value is not divisible by 3
	rjmp divisibility			;if neither, loop back to divisibility

	divisibleby3: st Y+, r23	;store value in 0x0400 if divisible by 3
	add r16, r23				;add sum to r16
	adc r17, r22				;increase sum to 16 bits
	dec r20						;decrement counter
	breq done					;if counter equals 0, done
	rjmp check					;if not, check next value

	notdivisibleby3: st Z+, r23	;store value in 0x0600
	add r18, r23				;add sum to r18
	adc r19, r22				;increase sum to 16 bits
	dec r20						;decrement counter
	breq done					;if counter equals 0, done
	rjmp check					;if not, check next value

	done: rjmp done				;infinite loop for debugging