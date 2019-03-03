;
; project2a.asm
;
; Created: 3/2/2019 1:16:38 AM
; Author : Tyler
;

.org 0
sbi ddrb, 2		;set portb2 as output
ldi r20, 5
sts tccr1b, r20	;set clock prescaler to 1024

begin: sbi portb, 2	;set portb2 to high
	ldi r21, 0x00
	sts tcnt1h, r21 ;set high bits of timer to 0
	sts tcnt1l, r21 ;set low bits of timer to 0
	rcall delayon	;call first delay function
	cbi portb, 2	;clear portb2
	ldi r21, 0x00	
	sts tcnt1h, r21	;set high bits of timer to 0
	sts tcnt1l, r21 ;set low bits of timer to 0
	rcall delayoff	;call second delay function
	rjmp begin		;infinite loop


delayon:
	lds r29, tcnt1h	;load high bits of timer1
	lds r28, tcnt1l ;load low bits of timer1
	cpi r28, 0xa9	;compare low bits of timer1 to 0x01a9 (representing 0.435 seconds)
	brsh bodyon
	rjmp delayon
bodyon:
	cpi r29, 0x01	;compare high bits of timer1 to 0x01a9
	brlt delayon
	ret

delayoff:
	lds r29, tcnt1h	;load high bits of timer1
	lds r28, tcnt1l	;load low bits of timer1
	cpi r28, 0x1b	;compare low bits of timer1 to 0x011b (representing 0.290 seconds)
	brsh bodyoff
	rjmp delayoff
bodyoff:
	cpi r29, 0x01	;compare high bits of timer1 to 0x01a9
	brlt delayoff
	ret