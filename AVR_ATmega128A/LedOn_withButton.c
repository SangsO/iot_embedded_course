/*
 * GccApplication2.c
 *
 * Created: 2022-07-26 오전 9:26:54
 * Author : KCCI27
 */ 

#define F_CPU 14745600L
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRE = 0x00; //	0b 0000 0000 //// 0b 0000(입력) 0000(출력) 하면?
	DDRD = 0xff; // 0b 1111 1111
	
    /* Replace with your application code */
    while (1) 
    {
		PORTD = PINE; //DDRE가 입력이면 -> PINE : digital read를 의미
					  //
    }
}
