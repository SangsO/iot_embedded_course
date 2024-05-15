#include "my_UART.h"

void UART0_transmit(char data_com)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data_com	;
}

void UART1_transmit(char data_ardu)
{
	while(!(UCSR1A & (1<<UDRE1)));
	UDR1 = data_ardu;
}

uint8_t UART0_receive(void)
{
	while(!(UCSR0A & (1<<RXC1)));
	// (1<<UDRE0) : Not Change -> UDRE0 = 5;
	// UCSR0A
	// empty State 1 & 1 = 1 -> 0   : Final 0   => Get out while()
	return UDR0;
}

char UART1_receive(void)
{
	while(!(UCSR1A & (1<<RXC1)));
	return UDR1;
}

void UART_INIT(void)
{
	DDRE = 0xFE;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	//UCSR0C = 0x06;
	UBRR0L = 95;	//baudrate
	
	DDRD = 0xFE;
	UCSR1B = (1<<RXEN0) | (1<<TXEN0);
	UBRR1L = 95;
}