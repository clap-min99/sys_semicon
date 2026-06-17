/*
 * led.c
 *
 * Created: 2026-06-15 오후 1:17:24
 *  Author: kccistc
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

extern volatile uint32_t msec_count;
#define FUNC_SU 6

int led_main(void);

int func_state = 0;
void (*fp[]) () =
{
	led_shift_left_on,		// func_state = 0
	led_shift_right_on,		
	led_shift_left_keepon,
	led_shift_right_keepon,
	led_flower_on,
	led_flower_off			// func_state = 5
};


int led_main(void)
{
	// uint8_t led_toggle=0;
	init_led();
	led_all_off();
	
	while(1)
	{
		#if 1
		fp[func_state] ();	
		
		#else
		//if (msec_count >= 500) // 500ms if (msec_count == 500)
		//{
			//msec_count = 0;
			//led_toggle = !led_toggle;
			//if (led_toggle) {
				//led_all_on();
			//}
			//else led_all_off();
		//}
		#endif
		// led_flower_on();
		// led_flower_off();
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
	if (msec_count >= 100) 
	{
		msec_count = 0;
		*(unsigned char *) 0x3B = 1 << i;
		if ((i = (i + 1) % 8) == 0) // 다음 index 값 계산
		{
			func_state = (func_state + 1) % FUNC_SU; // 다음 실행할 func 으로 jump
		}
	}
	
#endif
	
#if 0 // original
	
	static int i = 0;
	*(unsigned char *) 0x3B = 1 << i;
	_delay_ms(30);
	
	i = (i + 1) % 8; // 다음 index 값
	
#endif
}

void led_shift_right_on()
{
	#if 1
	static int i = 0;
	if (msec_count >= 100)
	{
		msec_count = 0;
		*(unsigned char *) 0x3B = 0x80 >> i;
		if ((i = (i + 1) % 8) == 0) // 다음 index 값 계산
		{
			func_state = (func_state + 1) % FUNC_SU; // 다음 실행할 func 으로 jump
		}
	}
	
	#else
	for (int i=7; i>=0; i--)
	{
		// PORTA = 1 << i;	
		*(unsigned char *) 0x3B = 1 << i;
	}
	#endif
}

void led_shift_left_keepon()
{
#if 1 
	static int i = 0;
	if (msec_count >= 100)
	{
		msec_count = 0;
		*(unsigned char *) 0x3B |= 1 << i;
		
		if ((i = (i + 1) % 8) == 0) // 다음 index 값 계산
		{
			led_all_off();
			func_state = (func_state + 1) % FUNC_SU; // 다음 실행할 func 으로 jump
		}
		
	}

#else
	for (int i=0; i<8; i++)
	{
		// PORTA |= 1 << i;	
		*(unsigned char *) 0x3B |= 1 << i;
		
	}
#endif
}

void led_shift_right_keepon()
{
#if 1
	static int i = 0;
	if (msec_count >= 100)
	{
		msec_count = 0;
		*(unsigned char *) 0x3B |= 0x80 >> i;
		if ((i = (i + 1) % 8) == 0) // 다음 index 값 계산
		{
			led_all_off();
			func_state = (func_state + 1) % FUNC_SU; // 다음 실행할 func 으로 jump
		}
	}

#else	
	for (int i=7; i>=0; i--)
	{
		PORTA |= 1 << i;
	}
#endif
}

void led_flower_on()
{
	static int i = 0;
	if (msec_count >= 100)
	{
		msec_count = 0;
		*(unsigned char *) 0x3B |= (1 << (4 + i)) | (1 << (3 - i));
		if ((i = (i + 1) % 8) == 0) // 다음 index 값 계산
		{
			func_state = (func_state + 1) % FUNC_SU; // 다음 실행할 func 으로 jump
		}
	}
	
}

void led_flower_off()
{
	static int i = 0;
	if (msec_count >= 100)
	{
		msec_count = 0;
		*(unsigned char *) 0x3B &= ~((1 << (7 - i)) | (1 << i));
		if ((i = (i + 1) % 8) == 0) // 다음 index 값 계산
		{
			func_state = (func_state + 1) % FUNC_SU; // 다음 실행할 func 으로 jump
		}
	}

}