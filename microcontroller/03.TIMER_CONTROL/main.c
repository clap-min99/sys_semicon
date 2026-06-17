/*
 * 03.TIMER_CONTROL.c
 *
 * Created: 2026-06-15 오전 11:36:49
 * Author : kccistc
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> // sei 등 함수 

extern int led_main(void);

void init_timer0();

volatile uint32_t msec_count = 0; // volatile의 최적화 방지
/*
ISR(Interrupt Service Routine): 인터럽트 처리 함수 ISR로 시작
TIMER_0VF_vect: Timer 0 Overflow INT가 발생이 되면 이곳으로 진입
250개의 펄스를 count(1ms)
ISR은 가능한 짧게 작성
*/
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;		// TCNT0 6~256: 250 펄스 count 하기 위해 
	msec_count++;	
}



int main(void)
{
    init_timer0();
	led_main();
	
    while (1) 
    {
		
    }
}

/*
1. timer 0 을 초기화 한다. 
	AVR에서 8bit timer 0/2 중에서 0번을 초기화 한다.
	임베디드에서 가장 신경을 써야할 부분 -> 초기화 하는 것
	초기화가 잘못되면 이후가 다 꼬인다.
2. 8bit로 1ms를 측정하는 timer/counter를 만들고자 한다.
	2.1 분주비 설정(64분주)
		16,000,000Hz/64 ==> 250,000Hz
	2.2 한 주기가 잡아먹는(?) 시간을 계산
		T = 1/f = 1/250,000 = 0.0000004 = 4µs
	2.3 8비트 까지 count 하는 시간을 계산(8bit timer OV(overflow))
		0.004ms X 256개 ==> 1.024ms ≓ 1ms = 0.001s
		0.004ms X 250개 ==> 1ms = 0.001s
*/

void init_timer0()
{
	// TCNT0 = TimerCount0
	// TCNT0 6 ~ 256 : 250개 펄스를 count 하기 위해 6부터 시작
	TCNT0 = 6;
	
	TCCR0 &= ~( 1<< CS02 | 1 << CS01 | 1 << CS00);	// 0분주 reset 먼저
	TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00;		// 64분주		
	TIMSK |= 1 << TOIE0;	// TIMER0 Overflow INT
	sei();					// 전역(대문) interrupt 허용
	
}
