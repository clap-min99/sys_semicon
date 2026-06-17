/*
 * led.c
 *
 * Created: 2026-06-10 오후 3:10:22
 *  Author: user
 */ 

#include "led.h"
void init_led(void);
void led_all_on(void);
void led_all_off(void);
void led_shift_left_on(void);
void led_shift_right_on(void);
void led_shift_left_keepon(void);
void led_shift_right_keepon(void);
void led_flower_on(void);
void led_flower_off(void);

int led_main(void);


int led_main(void)
{
	led_all_off();
	
	while(1)
	{
		led_flower_on();
		led_flower_off();
		//led_shift_left_keepon();
		//led_all_off();
		//led_shift_right_keepon();
		//led_all_off();
	}	
	
	return 0;
}

void init_led(void)
{
	DDRA=0xff;  // PORTA 를 출력 모드로 설정
	PORTA=0x00;  // PORTA에 물려있는 led를 all off 	
}

void led_all_on(void)
{
	PORTA=0xff;
}

void led_all_off(void)
{
	PORTA=0x00;
}

void led_shift_left_on()
{
	#if 1
	static int i = 0;
	*(unsigned char *) 0x3B = 1 << i;
	_delay_ms(30);
	
	i = (i + 1) % 8; // 다음 index 값
	
	#else // original
	
	for (int i=0; i<8; i++)
	{
		//PORTA = 1 << i;	// PORTA: 0x3B
		*(unsigned char *) 0x3B = 1 << i; 
		_delay_ms(30);
	}
	#endif
}

void led_shift_right_on()
{
	//for (int i=0; i<8; i++)
	//{
		//PORTA = 0x80 >> i;	
		//_delay_ms(300);
	//}
	#if 1
	static int i = 0;
	*(unsigned char *) 0x3B = 0x80 >> i;
	_delay_ms(30);
	
	i = (i + 1) % 8;
	
	#else
	for (int i=7; i>=0; i--)
	{
		// PORTA = 1 << i;	
		*(unsigned char *) 0x3B = 1 << i;
		_delay_ms(30);
	}
	#endif
}

void led_shift_left_keepon()
{
	for (int i=0; i<8; i++)
	{
		// PORTA |= 1 << i;	
		*(unsigned char *) 0x3B |= 1 << i;
		_delay_ms(300);
	}
}

void led_shift_right_keepon()
{
	for (int i=7; i>=0; i--)
	{
		PORTA |= 1 << i;
		_delay_ms(300);
	}
}

void led_flower_on()
{
	for (int i=0; i<4; i++)
	{
		PORTA |= (1 << (4 + i)) | (1 << (3 - i));
		_delay_ms(300);
	}
}

void led_flower_off()
{
	for (int i=0; i<4; i++)
	{
		PORTA &= ~((1 << (7 - i)) | (1 << i));
		_delay_ms(300);
	}
}