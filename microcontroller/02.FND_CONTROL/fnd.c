/*
 * fnd.c
 *
 * Created: 2026-06-12 오전 10:52:35
 *  Author: kccistc
 */ 

#include "fnd.h"

uint32_t ms_count = 0;	// ms를 재는 count uint32_t: unsigned_int
uint32_t sec_count = 0; // sec를 재는 count
uint8_t dot_display = 0;

int fnd_main();
void init_fnd();
void fnd_display();


int fnd_main(void)
{
	
	init_fnd();
	
	while(1)
	{
		fnd_display();
		_delay_ms(1);
		ms_count++;
		if (ms_count >= 1000)	// 1000ms ---> 1sec
		{
			ms_count = 0;
			sec_count++;
			dot_display = !dot_display;
		}
	}
	return 0;
}


void init_fnd(void)
{
	FND_DATA_DDR = 0xff; // 출력모드로 설정한다.
	FND_DIGIT_DDR |= 1 << FND_DIGIT_D1 | 1 << FND_DIGIT_D2 | 1 << FND_DIGIT_D3 | 1 << FND_DIGIT_D4;
	
// FND를 전체 off 하는 적업
#if 1		// common anode 방식
	
	FND_DATA_PORT = 0xff; 

#else		// common cathode 방식
	
	FND_DATA_PORT ~= 0xff;
		
#endif
}

void fnd_display(void)
{	
	#if 1
	// 0 1 2 3 4 5 6 7 8 9 .
	uint8_t fnd_font[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98, 0x7f}; // common anode
	
	#else
	// 0 1 2 3 4 5 6 7 8 9 .
	uint8_t fnd_font[] = {~0xc0, ~0xf9, ~0xa4, ~0xb0, ~0x99, ~0x92, ~0x82, ~0xd8, ~0x80, ~0x98, ~0x7f}; // common cathode
	
	#endif
	
	static int digit_select = 0;					// 자릿수 선택
	
	switch(digit_select)
	{
		case(0):									// 1단위
		#if 1
			FND_DIGIT_PORT = 0x80;					// anode
		#else		
			FND_DIGIT_PORT = ~0x80;					// cathode
		#endif
			FND_DATA_PORT = fnd_font[sec_count%10]; // 0~9
		break;
		
		case(1):									// 10단위
		#if 1
			FND_DIGIT_PORT = 0x40;
		#else
			FND_DIGIT_PORT = ~0x40;
		#endif
			FND_DATA_PORT = fnd_font[sec_count/10%6]; // 0~59
		break;
		
		case(2):									// 100단위
		#if 1
			FND_DIGIT_PORT = 0x20;
		#else
			FND_DIGIT_PORT = ~0x20;
		#endif
			FND_DATA_PORT = fnd_font[sec_count/60%10]; 
		break;
		
		case(3):									// 1000단위
		#if 1
			FND_DIGIT_PORT = 0x10;
		#else
			FND_DIGIT_PORT = ~0x10;
		#endif
			FND_DATA_PORT = fnd_font[sec_count/600%6]; // 0~59
		break;
	}
	digit_select = (digit_select + 1) % 4;			// 다음 표시할 자리수 
}

