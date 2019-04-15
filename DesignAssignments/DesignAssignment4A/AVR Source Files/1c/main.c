/*
 * 1c.c
 *
 * Created: 4/15/2019 2:24:47 PM
 * Author : Tyler
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define ENABLE 6
#define MTR_1 1
#define MTR_2 2
#define SW (PINC&(1<<1))

int main()
{
	PORTC |= (1<<1);				//Enable pull-up
	DDRB |= 0b00000111;				//PB0, PB1, and PB2 as outputs
	PORTD &= ~(1<<ENABLE);			//Enable = 0
	PORTB &= ~(1<<MTR_1);			//MTR_1 = 0
	PORTB &= ~(1<<MTR_2);			//MTR_2 = 0
	DDRD |= (1<<6);					//OC0A as output
	OCR0A = 50;
	
	//Fast PWM, non-inverted
	TCCR0A = (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
	TCCR0B = 0x02;					//N = 8
	while(1)
	{
		PORTD |= (1<<ENABLE);		//Enable = 1
		if(SW != 0)					//if PD7 is high
		{
			//Clockwise Rotation
			_delay_ms(20);
			PORTB |= (1<<MTR_1);	//MTR_1 = 1
			PORTB &= (~(1<<MTR_2));	//MTR_2 = 0
		}
		else
		{
			//Off
			_delay_ms(20);
			PORTB &= (~(1<<MTR_1));	//MTR_1 = 0
			PORTB &= (~(1<<MTR_2));	//MTR_2 = 0
		}
		_delay_ms(1000);
		if (OCR0A > 250)
		OCR0A = 50;
		else
		OCR0A = OCR0A + 25;
	}
}

