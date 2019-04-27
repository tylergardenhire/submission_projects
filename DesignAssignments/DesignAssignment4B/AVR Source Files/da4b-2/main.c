/*
 * da4b-2.c
 *
 * Created: 4/26/2019 5:38:24 PM
 * Author : Tyler
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	//initializations
	DDRC = 0x00;
	DDRD = 0xff;
	DDRB = 0xff;


	//timer initialization
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);  //Toggle on compare match
	TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS10);	   //set prescaler to 1
	ICR1 = 0xFFFF;

	while (1)
	{
		_delay_ms(250);
		OCR1A = 16000;
		_delay_ms(500);
		OCR1A = 8000;
		_delay_ms(250);
	}
}
