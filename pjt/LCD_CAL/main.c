/*
 * LCD_CAL.c
 *
 * Created: 2026-07-01 오전 9:47:11
 * Author : kccistc
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>   // sei, ISR 등
#include <stdio.h>
#include <util/delay.h>
#include "button.h"
#include "queue.h"
#include "cal.h"
#include "lcd.h"

void init_timer0();
extern void init_uart0();
extern void init_keypad();
extern void UART0_transmit(uint8_t data);
extern uint8_t keypad_scan(void);
extern void insert_queue(uint8_t value);
extern int queue_empty();
extern uint8_t read_queue();
extern void init_button();
extern int get_button(int button_num, int button_pin);
extern void LCD_init();
extern void lcd_goto_xy(uint8_t row, uint8_t col);
extern void lcd_write_command(uint8_t command);
extern void lcd_write_string(char *string);
extern void lcd_clear();

void cal_input(t_cal *c, uint8_t key);
void cal_reset(t_cal *c);


volatile uint32_t keypad_counter=0;
volatile uint32_t msec_count = 0;
volatile uint8_t  keypad_flag  = 0;


FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);


ISR(TIMER0_OVF_vect)
{
	volatile uint8_t keydata = 0;
	
	TCNT0 = 6;		// TCNT0 6~256: 250 펄스 count 하기 위해
	msec_count++;
	
	if (++keypad_counter >= 60)
	{
		keypad_counter = 0;
		if (keydata = keypad_scan())	//keypad를 체크해서 눌러진 것이 있어야 한다.
		{
			insert_queue(keydata);
			keypad_flag = 1;
		}
	};
	
	
}

int main(void)
{
	t_cal cal;
	
	init_timer0();
	init_uart0();
	init_keypad();
	init_button();
	LCD_init();
	
	cal_reset(&cal);
	
	stdout = &OUTPUT;		// printf가 동작할 수 있도록 stdout을 설정
	sei();

	// lcd_write_string("hello !");
	
	
	while (1)
	{if (keypad_flag)
		{
			keypad_flag = 0;
			
			uint8_t key = keypad_scan();      // 여기서 처리
			if (key) insert_queue(key);
		}
		
		
		if (get_button(BUTTON0, BUTTON0PIN)) insert_queue('H');   // 헥사 변환
		if (get_button(BUTTON1, BUTTON1PIN)) insert_queue('C');   // reset
		if (get_button(BUTTON2, BUTTON2PIN)) insert_queue('(');
		if (get_button(BUTTON3, BUTTON3PIN)) insert_queue(')');
		
		if (!queue_empty())
		{
			//key_value = read_queue();
			uint8_t key = read_queue();
			cal_input(&cal, key);
			//printf("key_value: %c\n", key_value);
		}
	}
}

void init_timer0()
{
	// TCNT0 = TimerCount0
	// TCNT0 6 ~ 256 : 250개 펄스를 count 하기 위해 6부터 시작
	TCNT0 = 6;
	
	TCCR0 &= ~( 1<< CS02 | 1 << CS01 | 1 << CS00);	// 0분주 reset 먼저
	TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00;		// 64분주
	TIMSK |= 1 << TOIE0;	// TIMER0 Overflow INT

}

