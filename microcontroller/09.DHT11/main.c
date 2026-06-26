/*
 * 09.DHT11.c
 *
 * Created: 2026-06-26 오전 9:25:42
 * Author : kccistc
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>   // sei, ISR 등
#include <stdio.h>
#include <util/delay.h>

extern void init_uart0();
extern void UART0_transmit(uint8_t data);
extern void dht11_main();

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	init_uart0();
	stdout = &OUTPUT;		// printf가 동작할 수 있도록 stdout을 설정
	
	while (1)
	{
		dht11_main();
		_delay_ms(1500);	// DHT11 안정화 시간
	}
}
