;
; 2B_assembly.asm
;
; Created: 3/9/2019 8:11:33 PM
; Author : Tyler
;


.org 0						;location for reset
	jmp start
.org 0x02					;location for ext_int0
	jmp ex0_isr

start:
	ldi r20, high(RAMEND)
	out sph, r20
	ldi r20, low(RAMEND)
	out spl, r20			;initialize stack

	ldi r16, 0x00			;initialize output
	ldi r20, 0x2			
	sts eicra, r20			;make INT0 falling edge triggered
	sbi ddrb, 2				;set portb2 as output (led)
	sbi portd, 2			;set pull up
	ldi r20, 1<<int0		;enable INT0
	out eimsk, r20			
	sei						;enable interrupt
off:
	out portb, r16			
	rjmp off				;turn led off until interrupt


delayon:					;delay for 1.25 seconds
	ldi r20, 100
delayon1:
	ldi r21, 100
delayon2:
	ldi r22, 200
delayon3:
	nop
	nop
	dec r22
	brne delayon3
	dec r21
	brne delayon2
	dec r20
	brne delayon1
	ret


ex0_isr:
	in r21, portb			
	ldi r22, (1<<2)			;toggles pb5
	eor r21, r22			;toggles led pb2
	out portb, r21			;turn led pb2 on
	rcall delayon			;call delay
	reti					;return here until interrupt