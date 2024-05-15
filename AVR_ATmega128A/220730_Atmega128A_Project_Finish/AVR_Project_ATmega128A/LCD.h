/*
 * LCD.h
 *
 * Created: 2022-07-28 오후 12:17:00
 *  Author: KCCI14
 */ 
#ifndef LCD_H_
#define LCD_H_

#define F_CPU 14745600L
#include <avr/io.h>
#include <util/delay.h>

//LCD
#define PORT_DATA      PORTA		// Data Pin : PA
#define PORT_CONTROL   PORTC		// Control Pin : PC
#define DDR_DATA       DDRA			// Data Pin Direction
#define DDR_CONTROL    DDRC			// Control Pin Direction

#define RS_PIN         0      // RS Control Pin bit Number
#define RW_PIN         1      // R/W Control Pin bit Number
#define E_PIN          2      // E  Control Pin bit Number

#define COMMAND_CLEAR_DISPLAY   0x01
#define COMMAND_8_BIT_MODE      0x38   //8bit, 2line, 5x8font
#define COMMAND_4_BIT_MODE      0x28   //4bit, 2line, 5x8font

#define COMMAND_DISPLAY_ON_OFF_BIT   2
#define COMMAND_CURSOR_ON_OFF_BIT   1
#define COMMAND_BLINK_ON_OFF_BIT   0

void LCD_pulse_enable(void);			 // E : HIGH -> LOW
void LCD_write_data(uint8_t data);		 // Character print
void LCD_write_command(uint8_t command); // Command operate
void LCD_clear(void);
void LCD_init(void);					 //8 bit Mode Text LCD Init
void LCD_write_string(char *string);	 //string print, random position character print
void LCD_goto_XY(uint8_t row, uint8_t col);

#endif /* LCD_H_ */