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
	//DDRE = 0x0f;	//ob 0000(input) 1111(output)
	DDRE = 0xf0;	//0b 1111(output) 0000(input)
					//
	
    /* Replace with your application code */
    while (1) 
    {			
		//PORTE = PINE >> 4;
		PORTE = PINE << 4;
		
			
			
    }
}
