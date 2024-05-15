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
#define PORT_DATA      PORTB   //데이터 핀 연결
#define PORT_CONTROL   PORTC   //제어 핀 연결
#define DDR_DATA       DDRB   //데이터 핀의 데이터 방향
#define DDR_CONTROL    DDRC   //제어 핀의 데이터 방향

#define RS_PIN         0      //RS 제어 핀의 비트 번호
#define RW_PIN         1      //R/W 제어 핀의 비트 번호
#define E_PIN          2      //E 제어 핀의 비트 번호

#define COMMAND_CLEAR_DISPLAY   0x01
#define COMMAND_8_BIT_MODE      0x38   //8비트, 2라인, 5x8폰트
#define COMMAND_4_BIT_MODE      0x28   //4비트, 2라인, 5x8폰트

#define COMMAND_DISPLAY_ON_OFF_BIT   2
#define COMMAND_CURSOR_ON_OFF_BIT   1
#define COMMAND_BLINK_ON_OFF_BIT   0

void LCD_pulse_enable(void); //E : HIGH -> LOW
void LCD_write_data(uint8_t data); //문자 출력
void LCD_write_command(uint8_t command); //명령어 실행
void LCD_clear(void);
void LCD_init(void); //8비트 모드로 텍스트 LCD 초기화
void LCD_write_string(char *string); //문자열 출력, 임의의 위치에 문자 출력
void LCD_goto_XY(uint8_t row, uint8_t col);

#endif /* LCD_H_ */