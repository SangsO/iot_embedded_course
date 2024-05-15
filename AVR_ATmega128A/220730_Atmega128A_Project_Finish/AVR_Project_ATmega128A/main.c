/*
 * GccApplication3.c
 * 
 * Created: 2022-07-27 오전 9:09:40
 * Author : OGS
 */ 

#define F_CPU 14745600L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD.h"
#include "my_UART.h"
#include "i2c.h"
#include "sht20.h"

void Receive_Ardu(void);	//Get Arduino Serial Data
void Dust_LCDshow(void);	//
void Servo(int);

char data;
int idx = 0, i = 0;
int m = 0, n = 0;
char msg[10] = {0x00};
	
int countingT = 0;
int AngleCount = 0;

char LCD_msg[4]	 = {0x00};
char LCD_msg2[4] = {0x00};
char LCD_hum[10] = {0x00};
char LCD_tem[10] = {0x00};

float humi, temp;
char ValueString[100];

void Servo(int Angle)
{
	if (Angle == -90 )
	AngleCount = 23; // PWM ON Time 2.3[ms]
	else if (Angle == 0)
	AngleCount = 15; // PWM ON Time 1.5[ms]
	else if(Angle == 90)
	AngleCount = 7; // PWM ON Time 0.7[ms]
}

// 0.1 [msec] Timer/Counter Interrupt Funtion
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 0x48; // Timer/Counter Init value Re-Load
	countingT++;
	if(countingT <= AngleCount)
	PORTB |= (1 << PORTB7); // PWM ON Time
	else
	//PORTB &= (0 << PORTB7); // PWM OFF Time
	PORTB &= ~(1 << PORTB7); // PWM OFF Time

	if(countingT >= 200)
	countingT = 0; // 20[ms] frequency PWM
}
	
void Receive_Ardu(void){
	
	char* pptr[2];
	
	do
	{
		data = UART1_receive();
		msg[idx] = data;
		
		UART0_transmit(msg[idx]);
		idx++;
		_delay_ms(10);
		
		if(msg[idx-1] == '@'){
			char* ptr = strtok(msg,"#"); //Using Parsing Point : #
			while(ptr != NULL){
				pptr[i]=ptr;
				ptr = strtok(NULL, "@"); // Second data : n get -> End Clearly  by @
				i++;
			}
			m = atoi(pptr[0]);
			n = atoi(pptr[1]);
			idx = 0;
			i = 0;			
			
		}
	}while(data != '@');
}

void Dust_LCDshow(void)
{		
	sprintf(LCD_hum, "h : %d", (int)humi);
	sprintf(LCD_tem, "t : %d", (int)temp);
	LCD_clear();
	LCD_goto_XY(0, 0);
	LCD_write_string("S: ");				// S = Small Size Dust
	LCD_goto_XY(0, 3);
	sprintf(LCD_msg, "%d", m);
	LCD_write_string(LCD_msg);
	LCD_goto_XY(0, 8);
	LCD_write_string("L: ");				// L = Large Size Dust
	LCD_goto_XY(0, 11);
	sprintf(LCD_msg2, "%d", n);				
	LCD_write_string(LCD_msg2);
	LCD_goto_XY(1, 0);
	LCD_write_string(LCD_hum);
	LCD_goto_XY(1, 8);
	LCD_write_string(LCD_tem);
}


int main(void)
{		
	//Servo Motor Initialization
	DDRB |= (1<<DDB7);
	DDRB |= (1<<DDB1);
		
	ASSR = 0;			// Using Inner Clock
	TCCR0 = 0x02;		// /8 prescaler
	TIMSK = 0x01;		// Using Timer/Count 0 Interrupt 
	AngleCount = 15;	// Init Servo Position = 0 setting
	TCNT0 = 0x48;		// 0.1 [msec] Timer/Interrupt value Setting
	TIFR = 0;
	
	UART_INIT();
	LCD_init();		
	
	sei();
	
	int window_flag = 1;
    
	/* Replace with your application code */
    while (1) 
	{		
		// if weather not clean...
		if((m > 150) && (n >150) && (window_flag==0))
		{
			UART0_transmit('\n');
			UART0_transmit('\r');
			Dust_LCDshow();
			humi = readHumidity();
			temp = readTemperature();
			
			Servo(0);
			_delay_ms(500);
			PORTB &= (0 << PORTB1);					
			Receive_Ardu();
			
			window_flag = 1;				
		}
		// else outside of window is not clean 
		else if((m <= 150) || (n <= 150))
		{
			UART0_transmit('\n');	//For Serial Putty Readability 
			UART0_transmit('\r');
			
			humi = readHumidity();
			temp = readTemperature();
			
			Receive_Ardu();
			Dust_LCDshow();
			
			Servo(90);			// close the door
			_delay_ms(500);			
			PORTB |= (1 << PORTB1);		
			window_flag = 0;
			_delay_ms(500);					
		}		
    }/* END OF application code */	
}