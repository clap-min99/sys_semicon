/*
 * 08.PWM_SERVO_PIEZO.c
 *
 * Created: 2026-06-25 오전 9:46:33
 * Author : kccistc
 */ 

#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "button.h"

#define F_SCALER   8UL
#define HZ_TO_OCR(hz)  (F_CPU / (2UL * F_SCALER * (hz)) - 1)

extern void init_button(void);
extern int get_button(int button_num, int button_pin);

/* ---- msec_count (Timer0 또는 Timer1 인터럽트로 1ms마다 증가) ---- */
volatile uint32_t msec_count = 0;
extern volatile uint8_t stop_music;
extern volatile int stop_btn;
extern volatile int stop_pin;
extern void delay_ms(int ms);

extern void Music_Player(int *tone, int *Beats);
extern void init_speaker(void);
extern void Beep(int repeat);
extern void Siren(int repeat);
extern void RRR(void);
extern const int Elise_Tune[];
extern const int Elise_Beats[];
extern int LG_Tune[];
extern const int LG_Beats[];
extern volatile uint8_t stop_music;


// PE3 (OC3A) PWM 출력 사용.
// 16bit Timer/Counter
// OCR3A값이 같아지면 Low 출력

void open_buzzer(void);
void power_on_melody(void);
void init_timer0();

/* ==================================================
 * power_on_melody() - 1회 실행분
 * ================================================== */
void power_on_melody(void)
{
	while(!stop_music)
	{
		OCR3A = HZ_TO_OCR(1000); delay_ms(70); if(stop_music) break;
		OCR3A = HZ_TO_OCR(2000); delay_ms(70); if(stop_music) break;
		OCR3A = HZ_TO_OCR(3000); delay_ms(70); if(stop_music) break;
		OCR3A = HZ_TO_OCR(4000); delay_ms(70);
	}
	OCR3A = 0;
}
/* ==================================================
 * open_buzzer() - 1회 실행분
 * ================================================== */
void open_buzzer(void)
{
	while(!stop_music)
	{
		OCR3A = HZ_TO_OCR(261); delay_ms(70); if(stop_music) break;
		OCR3A = HZ_TO_OCR(329); delay_ms(70); if(stop_music) break;
		OCR3A = HZ_TO_OCR(392); delay_ms(70); if(stop_music) break;
		OCR3A = HZ_TO_OCR(554); delay_ms(70);
	}
	OCR3A = 0;
}

/* ==================================================
 * Timer0 초기화 - 1ms 인터럽트용
 * ================================================== */

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;		// TCNT0 6~256: 250 펄스 count 하기 위해
	msec_count++;
	
}


int main(void)
{
	 init_timer0();    // msec_count용
	 init_button();    // 버튼 핀 입력 설정
	 init_speaker();   // Timer3 스피커 설정
	 sei();            // 전역 인터럽트 ON


	while(1)
	{
		if(get_button(BUTTON0, BUTTON0PIN))
		{
			stop_btn = BUTTON0; stop_pin = BUTTON0PIN; stop_music = 0;
			power_on_melody();
			OCR3A = 0;
		}
		if(get_button(BUTTON1, BUTTON1PIN))
		{
			stop_btn = BUTTON1; stop_pin = BUTTON1PIN; stop_music = 0;
			open_buzzer();
			OCR3A = 0;
		}
		if(get_button(BUTTON2, BUTTON2PIN))
		{
			stop_btn = BUTTON2; stop_pin = BUTTON2PIN; stop_music = 0;
			Music_Player(LG_Tune, (int*)LG_Beats);
			OCR3A = 0;
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

//
//#if 0
//#include <avr/io.h>
//extern int servo_motor_main(void);
//
//int main(void)
//{
    ///* Replace with your application code */
    //while (1) 
    //{
		//servo_motor_main();
    //}
//}
//#endif
