/*
 * part1.c
 *
 * Created: 3/16/2019 9:13:22 PM
 * Author : Tyler
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << DDB2);				//pb2 as output
	TCCR0A = 0;							//normal operation
	TCNT0 = 0x00;						//start the timer
	TCCR0B |= (1<<CS01) | (1<<CS00);	//set prescaler to 64 and start the timer
    while (1) 
    {
		while ((TIFR0 & 0x01)==0);
		PORTB ^= (1<<DDB1);
		TCNT0 = 0x00;
		TIFR0 = 0x01;					//reset the overflow flag
    }
}

