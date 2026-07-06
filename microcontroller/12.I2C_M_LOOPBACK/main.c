/*
 * 12.I2C_M_LOOPBACK.c
 *
 * Created: 2026-06-30 오전 10:45:47
 * Author : kccistc
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>   // sei, ISR 등
#include <stdio.h>
#include <util/delay.h>

void init_timer0();
extern void init_uart0();
extern void UART0_transmit(uint8_t data);
extern int i2c_main(void);
volatile int ms_counter = 0;

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

ISR(TIMER0_OVF_vect)
{

	TCNT0 = 6;		// TCNT0 6~256: 250 펄스 count 하기 위해
	ms_counter++;

}
int main(void)
{
	init_timer0();
	init_uart0();
	
	stdout = &OUTPUT;		// printf가 동작할 수 있도록 stdout을 설정
	sei();
	
	i2c_main();
	
	while (1)
	{
		
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
