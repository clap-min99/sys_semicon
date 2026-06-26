/*
 * pwm.c
 *
 * Created: 2026-06-18 오후 2:22:50
 *  Author: kccistc
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>   
#include <stdio.h>
#include "pwm.h"
//extern void init_button(void);
//extern int get_button(int button_num, int button_pin);

void init_timer1_pwm(void);
int servo_motor_main(void);
void init_timer1_pwm(void) 
{
	
	
	TCCR1A |= 1 << WGM11;	// TOP --> ICR1으로 설정
	TCCR1B |= 1 << WGM13 | 1 << WGM12;
	TCCR1A |= 1 << COM1A1;
	
	// === 분주비 설정 ===
	// 분주비 8 -> 16MHz로 50Hz 주파수를 바로 만들 수 없으므로
	// T= 1/f = 1/16000000Hz ---> 0.0000000625 * 8 ---> 0.000005sec (0.5us)
	// T = 1/f = 1/200000 Hz ---> 0.000005sec (0.5sec)
	// 16bit까지 count 할 수 있는 최대 0xffff(65535)
	// 250000Hz에서 256개 펄스 count하면 소요시간: 1.02ms
	//				127							: 0.5ms
	// 0.000005sec * 65535 = 0.0327675sec(32.7675ms) 32.7675ms  마다 timer INT
	// 20ms 길이(듀티)를 갖는것을 만든다고 하면
	// 0.000005sec * 40000개 ---> 0.02sec(20ms)
	// TCNT3: 0~255(0x00ff)까지 count한 후 0으로 다시 돌아간다.
	TCCR1B &= ~(1 << CS12 | 1 << CS11 | 1 << CS10);	// reset
	TCCR1B |= 1 << CS11;	// 분주비 8
	//ICR1 = 0x3ff;	// 1023 * 4µs ==> 4ms TOP 값
	ICR1 = 40000 - 1; // 0.000005sec * 40000개 ---> 0.02sec(20ms) TOP값
}


int servo_motor_main(void)
{
	// servo motor가 PB5를 출력으로 설정 
	DDRB |= 1 << 5;
	init_timer1_pwm();
	
	// 0(1ms) --> 90(1.5ms) --> 180(2ms)
	while(1) 
	{
		// 1ms : 2000개 count 
		// 40000(20ms) / 20 --> 1ms(2000)
		OCR1A = 1400;
		_delay_ms(1000);
		
		// 1.5ms : 3000개 count
		OCR1A = 3100;
		_delay_ms(1000);
		
		// 2ms : 4000개 count
		OCR1A = 4900;
		_delay_ms(1000);
		
	}
	return 0;
}