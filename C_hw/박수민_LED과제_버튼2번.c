// LED 과제 source code

//main.c
#define F_CPU 16000000UL		// 16MHz
#include <avr/io.h>				// PORTA PORTD 등의 I/O register 들이 들어있음.
#include <util/delay.h>			// _delay_ms _delay_us 등의 함수가 들어있음. 

#include "button.h"

extern void init_led(void);		// init_led 함수는 다른 파일에 들어있다고 컴파일러에 알려줌
extern void init_button(void); 
extern int get_button(int button_num, int button_pin);
extern void led_all_on();
extern void led_all_off();
extern void led_right_on();
extern void led_left_on();
extern void led_odd_on();
extern void led_even_on();

// polling 방식 -> 소프트웨어가 주기적으로 상태를 체크하는 방식
// interrupt 방식 -> 하드웨어가 상황 변화를 소프트웨어에 알려주는 방식

#if 1
int main(void)
{
	int button0_state = 0;	// 초기상태를 LED all off 로 설정
	int button1_state = 0;
	
	init_button();
	init_led();
	
	while (1) 
    {
		
		// 0번 버튼: toggle off <--> on
		// led 전부 끈 상태 -> 전부 켜기 -> led right 4개 -> led left 4개 
		if (get_button(BUTTON0, BUTTON0PIN))
		{
			// button0_state = !button0_state;		// 반전 0 <--> 1 	
			button0_state = (button0_state+1) % 4;
			
			switch (button0_state)
			{ 
				case 0: led_all_off();	break;  // 전체 OFF
				case 1: led_all_on();   break;  // 전체 ON
				case 2: led_right_on(); break;  // 오른쪽
				case 3: led_left_on();  break;  // 왼쪽
				
			}
		}
		
		// 1번 버튼: 홀수 짝수
		if (get_button(BUTTON1, BUTTON1PIN))
		{
			button1_state = !button1_state;
			if (button1_state) 
			{
				led_odd_on();
			}
			else
			{
				led_even_on();
			}
		}
		// 2번버튼 : 전체 상태 리셋
		if (get_button(BUTTON2, BUTTON2PIN))
		{
			button0_state = 0;   // 상태 0으로 초기화
			led_all_off();       // LED 전체 끄기
		}
    }
	
}

#endif



//led.c


#include "led.h"

void init_led(void);
void led_all_on(void);
void led_all_off(void);
void led_right_on(void);
void led_left_on(void);
void led_odd_on(void);
void led_even_on(void);

void init_led(void) 
{
	DDRA = 0xff;	// PORTA 를 출력 모드로 설정
	PORTA = 0x00;	// PORTA에 물려있는 LED를 모두 off
	
}

void led_all_on(void) 
{
	PORTA = 0xff;	// 모두 on
}

void led_all_off(void)
{
	PORTA = 0x00;	// 모두 off
}

void led_right_on(void)
{
	PORTA = 0b00001111;
}

void led_left_on(void)
{
	PORTA = 0b11110000;
}

void led_odd_on(void)
{
	PORTA = (1<<1) | (1<<3) | (1<<5) | (1<<7); // PORTA = 0b10101010;
}

void led_even_on(void)
{
	PORTA = (1<<0) | (1<<2) | (1<<4) | (1<<6); // PORTA = 0b01010101;
}