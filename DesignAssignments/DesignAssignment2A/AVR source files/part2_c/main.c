/*
 * part2_c.c
 *
 * Created: 3/2/2019 6:48:49 PM
 * Author : Tyler
 */ 

#include <avr/io.h>				//standard avr library
#define F_CPU 1000000UL			//set clock speed in MHz
#include <util/delay.h>			//delay library for above clock speed


int main(void)
{

	DDRB |= (1 << PB2);			//define portb2 as an output to blink the LED
	DDRC &= (0 << PB2);			//define portc2 as an input (switch)
	PORTC |= (1 << PB2);		//enable pull-up

	while(1)					//infinite loop
	{
		if (PINC)				//if there is input at portc2
		{
			PORTB |= (1 << PB2);//enable portb2
			_delay_ms(1250);	//delay for 1.25 seconds
		}
		else
		PORTB &= ~(1 << PB2);	//else clear portb2
	}

	return 1;
}

