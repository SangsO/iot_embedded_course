/*
 * LCD.c
 *
 * Created: 2022-07-28 오후 12:17:23
 *  Author: KCCI14
 */ 
#include "LCD.h"

void LCD_init(void) {
   _delay_ms(50);   //First operate time
   
   //연결 핀을 출력으로 설정
   DDR_DATA = 0xFF;										//DDRD Data Pin Data direction
   PORT_DATA = 0x00;                                    //PORTD Data pin link
   DDR_CONTROL |= (1 << RS_PIN) | (1 << RW_PIN) | (1 << E_PIN); 
														//DDRC Control Pin Data direction
   
   // R/W pin -> LOW output -> use write Only
   PORT_CONTROL &= ~(1 << RW_PIN);                          //PORTC Control Pin link
   
   LCD_write_command(COMMAND_8_BIT_MODE);					// 8bit Mode 0x38
   
   //display on/off control
   // Display on, Cursor off, Cursor Blink off
   uint8_t command = 0x08 | (1 << COMMAND_DISPLAY_ON_OFF_BIT);
   LCD_write_command(command);
   
   LCD_clear();
   
   // Entry Mode Set
   // Print and then Cursor move right : DDRAM Address plus -> No Dispaly Move
   LCD_write_command(0x06);
}

void LCD_pulse_enable(void) {
   PORT_CONTROL |= (1 << E_PIN);
   _delay_ms(1);
   PORT_CONTROL &= ~(1 << E_PIN);
   _delay_ms(1);
}

void LCD_write_data(uint8_t data) {
   PORT_CONTROL |= (1 << RS_PIN);
   PORT_DATA = data;
   LCD_pulse_enable();
   _delay_ms(2);
}

void LCD_write_command(uint8_t command) {
   PORT_CONTROL &= ~(1 << RS_PIN);
   PORT_DATA = command;
   LCD_pulse_enable();
   _delay_ms(2);
}

void LCD_write_string(char *string) {
   uint8_t i;
   for(i = 0; string[i]; i++)       // Before End String
   LCD_write_data(string[i]);		// String unit print...
}

void LCD_goto_XY(uint8_t row, uint8_t col) {
   col %= 16;						// [0 15]
   row %= 2;						// [0 1]
   
   uint8_t address = 0;
   
   if(row == 0) address = 0x80;
   else if(row == 1) address = 0xC0;
   
   if(col < 16) address += col;
   
   LCD_write_command(address);   // Cursor Move
}

void LCD_clear(void) {
   LCD_write_command(COMMAND_CLEAR_DISPLAY); //0x01
   _delay_ms(2);
}