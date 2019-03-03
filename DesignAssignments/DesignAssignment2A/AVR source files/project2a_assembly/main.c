/*
 * project2a_assembly.c
 *
 * Created: 3/2/2019 5:23:49 PM
 * Author : Tyler
 */ 

#include <avr/io.h>				//standard avr library
#define F_CPU 1000000UL			//set clock speed in MHz
#include <util/delay.h>			//delay library for above clock speed


int main(void)
{

	DDRB |= (1 << PB2);			//define portb2 as an output to blink the LED

	while(1)					//infinite loop to see the correct output on the board
	{
		PORTB |= (1 << PB2);	//turn led ON
		_delay_ms(435);			//delay for 435ms
		PORTB &= ~(1 << PB2);	//turn led OFF
		_delay_ms(290);			//delay for 290ms
	}

	return 1;					//return value for int main (never executed)
}

