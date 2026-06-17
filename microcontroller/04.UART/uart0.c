/*
 * uart0.c
 *
 * Created: 2026-06-16 오전 9:57:55
 *  Author: kccistc
 */ 

#include "uart0.h"

void init_uart0();
void UART0_transmit(uint8_t data);

/*
1. 전송속도 : 9600bps
2. start/stop 설정
3. RX(수신): interrupt 로 설정

*/
void init_uart0(void){
	UBRR0H = 0x00;
	UBRR0L = 207;			// 9600bps, 표 8-9
	UCSR0A |= 1 << U2X0;	// 2배속 설정
	// UART0 송신, 수신이 모두 가능하도록 RX Interrupt가 가능하도록 설정.	
	UCSR0B |= 1 << RXEN0 | 1 << TXEN0 | 1 << RXCIE0; // RXCIE: RX complete interrupt enable 
}

// UART0로 1byte 전송하는 함수
void UART0_transmit(uint8_t data)
{
	while( !(UCSR0A & (1 << UDRE0))); // no operation -> data가 송신중이면 송신이 끝날 때까지 기다림

	UDR0 = data;			// HW 전송 register에 data를 송신한다.
	
}