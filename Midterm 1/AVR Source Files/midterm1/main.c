/*
 * midterm1.c
 *
 * Created: 4/7/2019 12:36:13 PM
 * Author : Tyler
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>

#define F_CPU 16000000UL
#define BAUD 115200
#define FOSC 16000000
#define UBRREQ FOSC/8/BAUD -1

volatile uint8_t ADCvalue;
volatile unsigned char ADCtemp[5];
volatile unsigned char CWMODE[] = "AT+CWMODE=3\r\n"; // WiFi mode = 3
volatile unsigned char WIFI[] = "AT+CWJAP=\"gardenhi\", \"BasketballStar23\"\r\n"; // Connects to local internet connection
volatile unsigned char ENABLE[] = "AT+CIPMUX=0\r\n"; // Connected to my 2.4GHz WiFi
volatile unsigned char CIPSTART[] = "AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n"; //TCP, strip remote IP, port = 80
volatile unsigned char CIPSEND[] = "AT+CIPSEND=45\r\n"; // Length of data = 45
volatile unsigned char SEND_DATA[] = "GET /update?key=1Q0Z8SVE7A1ONWS1&field1="; // Write API key
volatile unsigned char PAUSE[] = "\r\n\r\n"; // Go to left side, skip a line, go to left side, skip a line

void ADC_init (void);
void UART_init (void);
void signal_AT (volatile unsigned char c[]);

int main( void )
{
	ADC_init(); // Initializes ADC values
	UART_init(); // Initializes UART values
	
	// Calls functions to enable WiFi mode, connects to the specific WiFi, establishes single connection
	_delay_ms(1000);
	signal_AT(CWMODE);
	
	_delay_ms(1000);
	signal_AT(WIFI);
	
	_delay_ms(2000);
	signal_AT(ENABLE);

	while(1) // Constantly send values through the cloud until device turns off
	{

		// Calls functions to connect to thingspeak, sets length of data to be sent, sends the data values to cloud
		_delay_ms(1000);
		signal_AT(CIPSTART); // Connects to thingspeak
		
		_delay_ms(1000);
		signal_AT(CIPSEND); // Sets length of data

		_delay_ms(1000);
		signal_AT(SEND_DATA);
		signal_AT(ADCtemp); // Sends data
		
		signal_AT(PAUSE); // Pauses to load data
	}
}

void ADC_init (void)
{
	//ADC Multiplexer Selection Register
	ADMUX = (1 << REFS0) |				// Voltage reference during conversion, "AVcc with external capacitor at AREF pin"
	(1 << ADLAR);						// Left adjust ADC conversion result in ADC Data Register
	
	//ADC Control and Status Register A
	ADCSRA = (1 << ADEN) |		// ADC enable
	(1 << ADSC) |				// ADC Start Conversion
	(1 << ADATE) |				// ADC Auto Trigger enable
	(1 << ADIE) |				// ADC Interrupt enable
	(1 << ADPS2) |
	(1 << ADPS1) |
	(1 << ADPS0);		 // ADPS2:0 = 111 = 128 prescaler
}

void UART_init (void)
{
	//USART Baud Rate Registers
	UBRR0H = UBRREQ >> 8;		 // Shifts right to store upper 8 bits
	UBRR0L = UBRREQ;			 // Store lower 8 bits

	//USART Control and Status Register (A/B/C)
	UCSR0A |= (1 << U2X0);		 // Doubles USART transmission speed
	UCSR0B |= (1 << TXEN0);		 // Enables USART transmitter
	UCSR0C |= (1 << UCSZ01) |
	(1 << UCSZ00);	 // 8-bit character size
	
	sei();						 // Enable global interrupt
}

ISR(ADC_vect)
{
	volatile unsigned int j=0;
	char temp[5];
	
	ADCvalue = (ADCH << 1);		 // Shifts the value left to one place
	
	itoa(ADCvalue, temp, 10);	 // Converts integers to string
	
	while (j<5)					 // Transfers the temp string from itoa() to ADCtemp
	{
		ADCtemp[j] = temp[j];
		j++;
	}
}


void signal_AT(volatile unsigned char c[]) {
	volatile unsigned int i=0;
	volatile unsigned int j=0;
	
	j = 0;						 // Initializes counter
	
	while (c[j] != 0x00)		 // While not at end of string
	{
		j++;
	}
	
	while (i<j)					 // If UDRE0 = 1, buffer can be written to
	{
		while(!(UCSR0A & (1 << UDRE0)));
		UDR0 = c[i];
		i++;
	}
}

