//*******************************************************************************************************//
//                                                                                                       //
//Interrupt : Button1 -> plus the index  // Button2 -> minus the index2                                  //
//                                                                                                       //
//*******************************************************************************************************//

/*
 * GccApplication2.c
 *
 * Created: 2022-07-26 오전 9:26:54
 * Author : OGS
 */ 

#define F_CPU 14745600L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int count = 0;

uint8_t font[] = {0x3f, 0x06, 0x5b, 0x4f, 
				  0x66, 0x6d, 0x7c, 0x07, 
				  0x7f, 0x67, 0x77, 0x7c, 
				  0x39, 0x5e, 0x79, 0x71, 
				  0x08, 0x80};
				  				  
//unsigend char 와 같다

void segmnet( unsigned char n)
{
	unsigned char n10, n1;
	n10 = n / 10;
	n1 = n % 10;
	
	for (int idx  = 0; idx < 30; idx++)
	{
		PORTG = 0x0b;
		PORTB = font[n10];
		_delay_ms(1);
		PORTG = 0x07;
		PORTB = font[n1];
		_delay_ms(1);		
	}	
}
ISR(INT0_vect)
{
	count++;
}
ISR(INT4_vect)
{
	count--;
}

int main(void)
{	
	DDRB = 0xff;
	DDRE = 0x00; //안적었을때도 되는 이유는 데이터시트상 최초값이 0으로 이미 설정되어있어서 그럼
	DDRG = 0x0f;
	DDRD = 0x00;
	
	EIMSK |= (1 << INT0) | (1 << INT4) ; //0x01; //INT0 사용
	//EIMSK = 0x01;
	EICRA |= (1 << ISC00) | (1<<ISC01); //0x03; //INT0 RISING EDGE
	EICRB |= (1 << ISC40) | (1<<ISC41);
	//EICRA = 0x03;
	
	//SREG = 0x80; //sei();
	sei();					
    /* Replace with your application code */	
    while (1) 
    {			
		segmnet(count);
			
    }
}
