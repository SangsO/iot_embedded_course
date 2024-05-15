/*
 * LCD.c
 *
 * Created: 2022-07-28 오후 12:17:23
 *  Author: KCCI14
 */ 
#include "LCD.h"

void LCD_init(void) {
   _delay_ms(50);   //초기 구동 시간
   
   //연결 핀을 출력으로 설정
   DDR_DATA = 0xFF;                                   //DDRD 데이터 핀의 데이터 방향
   PORT_DATA = 0x00;                                   //PORTD 데이터 핀 연결
   DDR_CONTROL |= (1 << RS_PIN) | (1 << RW_PIN) | (1 << E_PIN);  //DDRC 제어 핀의 데이터 방향
   
   //R/W 핀으로 LOW를 출력하여 쓰기 전용으로 사용
   PORT_CONTROL &= ~(1 << RW_PIN);                          //PORTC 제어 핀 연결
   
   LCD_write_command(COMMAND_8_BIT_MODE);   //8비트 모드 0x38
   
   //display on/off control
   //화면 on, 커서 off, 커서 깜빡임 off
   uint8_t command = 0x08 | (1 << COMMAND_DISPLAY_ON_OFF_BIT);
   LCD_write_command(command);
   
   LCD_clear();   //화면 지움
   
   //Entry Mode Set
   //출력 후 커서를 오른쪽으로 옮김, 즉 DDRAM의 주소가 증가하여 화면 이동은 없음
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
   for(i = 0; string[i]; i++)      //종료 문자를 만날 때까지
   LCD_write_data(string[i]);   //문자 단위 출력
}

void LCD_goto_XY(uint8_t row, uint8_t col) {
   col %= 16;   //[0 15]
   row %= 2;   //[0 1]
   
   uint8_t address = 0;
   
   if(row == 0) address = 0x80;
   else if(row == 1) address = 0xC0;
   
   if(col < 16) address += col;
   
   LCD_write_command(address);   //커서 이동
}

void LCD_clear(void) {
   LCD_write_command(COMMAND_CLEAR_DISPLAY); //0x01
   _delay_ms(2);
}