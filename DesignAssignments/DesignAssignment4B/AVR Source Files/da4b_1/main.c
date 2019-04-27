/*
 * da4b_1.c
 *
 * Created: 4/26/2019 5:37:50 PM
 * Author : Tyler
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	//initialization
	DDRC = 0x00;
	DDRD = 0xff;
	DDRB = 0xff;
	int f1 = 0;
	int f2 = 0;
	int delay = 100;

	while (1)
	{
		for (f1 = 0; f1 <=4; f1++)
		{
			PORTB |= (1<<PB0);
			_delay_ms(delay);
			PORTB &= ~(1<<PB0);
			_delay_ms(delay);
			PORTB |= (1<<PB1);
			_delay_ms(delay);
			PORTB &= ~(1<<PB1);
			_delay_ms(delay);
			PORTB |= (1<<PB2);
			_delay_ms(delay);
			PORTB &= ~(1<<PB2);
			_delay_ms(delay);
			PORTB |= (1<<PB3);
			_delay_ms(delay);
			PORTB &= ~(1<<PB3);
			_delay_ms(delay);
		}
		f1 = 0;
		
		for (f2 = 0; f2 <=6; f2++)
		{
			PORTB |= (1<<PB3);
			_delay_ms(delay);
			PORTB &= ~(1<<PB3);
			_delay_ms(delay);
			PORTB |= (1<<PB2);
			_delay_ms(delay);
			PORTB &= ~(1<<PB2);
			_delay_ms(delay);
			PORTB |= (1<<PB1);
			_delay_ms(delay);
			PORTB &= ~(1<<PB1);
			_delay_ms(delay);
			PORTB |= (1<<PB0);
			_delay_ms(delay);
			PORTB &= ~(1<<PB0);
			_delay_ms(delay);
		}
		f2 = 0;
	}
}

