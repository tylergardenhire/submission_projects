;
; part2_assembly.asm
;
; Created: 3/2/2019 5:45:29 PM
; Author : Tyler
;

.org 0
cbi ddrc, 2				;set portc2 as input (switch)
sbi ddrb, 2				;set portb2 as output (led)
ldi r20, 5				
sts tccr1b, r20			;set clock prescaler to 1024

again: sbic pinc, 2		;check if portc2 is receiving input from switch
	rjmp over			;if so, jump to over
	cbi portb, 2		;if not, clear portb2
	rjmp again			;infinite loop
over: sbi portb, 2		;set portb2 to high
	ldi r21, 0x00		
	sts tcnt1h, r21		;set high bits of timer1 to 0
	sts tcnt1l, r21		;set low bits of timer1 to 0
	rjmp delayon		;jump to delay (1.25 second delay)
	rjmp again			;infinte loop




delayon:
	lds r29, tcnt1h		;load high bits of timer1
	lds r28, tcnt1l		;load low bits of timer1
	cpi r28, 0xc5		;compare low bits of timer1 to 0x04c5 (representing 1.25 seconds)
	brsh bodyon
	rjmp delayon
bodyon:
	cpi r29, 0x04		;compare high bits of timer1 to 0x04c5
	brlt delayon
	ret