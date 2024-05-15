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
	// (1<<UDRE0)은 안바뀌는 값이다 -> UDRE0 = 5;
	// UCSR0A
	// 비어있는 상태 1 & 1 = 1 -> 0   : 최종 0   =>   while문 빠져나옴
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