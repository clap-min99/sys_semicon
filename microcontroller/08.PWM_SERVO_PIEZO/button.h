/*
 * button.h
 *
 * created: 2026-06-12 오후 1:23:02
 *  author: kccistc
 */ 

// #ifndef button_h_		// button_h_라는 이름이 정의가 되어있지 않다면, 정의를 해라
// #define button_h_		// 그래서 정의한 것
// #endif /* button_h_ */

#define f_cpu 16000000ul	// 16mhz
#include <avr/io.h>			// porta, portb 등 i/o 관련 reg
#include <util/delay.h>		

// 아래는 pull down 저항(버튼) 기준으로 작성

#define BUTTON_DDR DDRD	
#define BUTTON_PIN PIND		// portd를 읽는 register 5v:1 0v:0

#define BUTTON0PIN 3		// portd.3 
#define BUTTON1PIN 4		// portd.4
#define BUTTON2PIN 5		// portd.5
#define BUTTON3PIN 6		// portd.6

#define BUTTON0 0			// portd.3의 가상 index (software number)
#define BUTTON1 1			// portd.4의 가상 index (software number)
#define BUTTON2 2			// portd.5의 가상 index (software number)
#define BUTTON3 3			// portd.6의 가상 index (software number)

#define BUTTON_NUMBER 4		// 버튼의 갯수

#define BUTTON_PRESS 1		// 버튼을 누르면 high(active-high)
#define BUTTON_RELEASE 0	// 버튼을 땐 상태(low)

// power on & reset , 초기화(버튼 초기화 led 초기화 ddr 초기화)
// finite state machine(fsm, 유한한 상태 내에서 작동) ≒ state transition diagram(상태전이도)
// fsm을 잘 그리는게 중요하다 1. 회로도 작성 2. 펌웨어 작성(입.출력 정의) 3. 기본설계.상세설계  4. 코딩  5. 검증
