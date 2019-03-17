/*
 * part3.c
 *
 * Created: 3/16/2019 9:25:16 PM
 * Author : Tyler
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
    DDRB |= (1 << DDB2);					//pb2 as output
	OCR0A = 40;
	TCCR0B |= (1 << CS01 | 1 << CS00);		//internal clock
	TCCR0A |= (1 << WGM01);					//internal clock, ctc mode, no prescaler
	sei();
    while (1)								
    {
		//wait here
    }
}

ISR (TIMER0_COMPA_vect)
{
	PORTB ^= 0x02;							//toggle PORTB.2
	TIFR0 |= (1 << OCF0A);					//clear the compare A match flag
}