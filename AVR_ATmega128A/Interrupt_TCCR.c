//*******************************************************************************************************//
//                                                                                                     	 //
// Interrupt : using TCCR                                                                                //
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

int t_cnt = 0, m_cnt = 0;

uint8_t font[] = {0x3f, 0x06, 0x5b, 0x4f, 
				  0x66, 0x6d, 0x7c, 0x07, 
				  0x7f, 0x67, 0x77, 0x7c, 
				  0x39, 0x5e, 0x79, 0x71, 
				  0x08, 0x80};
				  				  
//unsigend char 와 같다

void segmnet( unsigned char n)
{
	unsigned char n1000, n100, n10, n1;
	
	int buff;
	n1000 = n/ 1000;
	buff = n % 1000;
	n100 = buff / 100;
	buff = buff % 100;
	n10 = buff / 10;
	n1 = buff % 10;
	
	for (int idx  = 0; idx < 30; idx++)
	{
		PORTC = 0x0e;
		PORTA = font[n1000];
		_delay_ms(1);
		PORTC = 0x0d;
		PORTA = font[n100];
		_delay_ms(1);
		PORTC = 0x0b;		
		PORTA = font[n10];
		_delay_ms(1);
		PORTC = 0x07;
		PORTA = font[n1];
		_delay_ms(1);
	}	
}
ISR(TIMER2_COMP_vect)
{
	OCR2 = 144; //오버플로우로 값이 카운트 되면 값을 원래대로 되돌려놓아야 한다
	t_cnt++;
	if(t_cnt >= 1000)
	{		
		t_cnt = 0;
		m_cnt++;
	}
}

int main(void)
{	
	DDRA = 0xff;
	//DDRE = 0x00; //안적었을때도 되는 이유는 데이터시트상 최초값이 0으로 이미 설정되어있어서 그럼
	DDRC = 0x0f;
	DDRB = 0x80;
	PORTA = 0xff;
	PORTC = 0x0f;	
	
	//TCCR0 = (1<<0x07);
	TCCR2 |= (1<<CS20) | (1<<CS22); //0x07	
	//To See Graph
	TCCR2 |= (1<<WGM21);
	TCCR2 |= (1<<COM20);
	
	OCR2 = 144;
	//TIMSK = (1<<0x01);
	TIMSK |= (1<<OCIE2); //0x01;		
	//
	
	//TCNT0 = 242; //0xf2
	
	sei();					
    /* Replace with your application code */	
    while (1) 
    {			
		segmnet(m_cnt);
			
    }
}
