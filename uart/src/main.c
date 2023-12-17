#define F_CPU 16000000
#define BAUD 9600

#define UBRRL_value ((F_CPU / BAUD / 16) - 1)

#include <avr/io.h>
#include <util/delay.h>

void init_UART()
{
	//set Baud rate
	UBRR0L = UBRRL_value;
	UBRR0H = UBRRL_value >> 8;
	
	UCSR0A = 0x00;
	
	//enable transmitter
	UCSR0B |= 1 << TXEN0;
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}

void send_UART(char value)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = value;
}

int main (void)
{
	init_UART();
	while(1)
	{
		send_UART('t');
		send_UART('e');
		send_UART('x');
		send_UART('t');
		send_UART(0x0D);
		send_UART(0x0A);
		_delay_ms(1000);
	}

}
