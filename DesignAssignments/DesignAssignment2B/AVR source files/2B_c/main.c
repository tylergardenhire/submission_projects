/*
 * 2B_c.c
 *
 * Created: 3/9/2019 9:41:36 PM
 * Author : Tyler
 */ 

#define F_CPU 8000000UL				//set cpu mhz for delay
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void)
{
		DDRB |= (1<<2);				//set pb2 as output
		PORTB &= (1<<2);			//clear pb2
		PORTD = 1<<2;				//enable pd2
		
		EICRA = 0x02;
		EIMSK = 1<<INT0;			//enable pc set 0 interrupt
		sei();						//enable global interrupt
		
		while (1);
}


ISR(INT0_vect)
{
	PORTB ^= (1<<2);				//toggle pb2 during interrupt
	_delay_ms(1250);				//delay for 1.25 seconds
	PORTB ^= (1<<2);				//toggle pb2 during interrupt
}
