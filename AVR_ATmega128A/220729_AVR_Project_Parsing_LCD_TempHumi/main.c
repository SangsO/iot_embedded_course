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

void Receive_Ardu(void);
void Dust_LCDshow(void);

char data;
int idx = 0, i = 0;
int m = 0, n = 0;
char msg[10] = {0x00};
	
char LCD_msg[4]	 = {0x00};
char LCD_msg2[4] = {0x00};
char LCD_hum[10] = {0x00};
char LCD_tem[10] = {0x00};
	
float humi, temp;
char ValueString[100];

void Receive_Ardu(void){
	char* pptr[2];
	do
	{
		data = UART1_receive();
		msg[idx] = data;
		UART0_transmit(msg[idx]);
		idx++;
		_delay_ms(30);
		if(msg[idx-1] == '@'){
			char* ptr = strtok(msg,"#");
			while(ptr != NULL){
				pptr[i]=ptr;
				ptr = strtok(NULL, "@"); // 두번째인 n값까지 받고 "@"를 사용하여 끝을 확실히함
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
	sprintf(LCD_msg, "%d", m);
	LCD_write_string(LCD_msg);
	LCD_goto_XY(0, 8);
	sprintf(LCD_msg2, "%d", n);
	LCD_write_string(LCD_msg2);
	LCD_goto_XY(1, 0);
	LCD_write_string(LCD_hum);
	LCD_goto_XY(1, 8);
	LCD_write_string(LCD_tem);
}


int main(void)
{
	
	
	UART_INIT();
	LCD_init();
	
	
    /* Replace with your application code */
    while (1) 
    {		
		//DHT Sensor START	

		humi = readHumidity();
		temp = readTemperature();
		 Receive_Ardu();
		 UART0_transmit('\n');
		
		 Dust_LCDshow();
		 _delay_ms(1000);
		 
    }/* END OF application code */
	
}