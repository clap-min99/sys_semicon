/*
 * button.c
 *
 * Created: 2026-06-12 오후 1:22:26
 *  Author: kccistc
 */ 

#include "button.h"		// "xx.h" -> 같은 directory에 있는 파일을 가져오겠다

void init_button(void);
int get_button(int button_num, int button_pin);

// 버튼 초기화 방향설정
void init_button(void)
{
	BUTTON_DDR &= ~(1 << BUTTON0PIN | 1 << BUTTON1PIN | 1 << BUTTON2PIN | 1 << BUTTON3PIN);
}

// ex) BUTTON0PIN 3
// button 을 눌렀다 떼면	: 1 리턴
// button 이 idle 상태	: 0 리턴

int get_button(int button_num, int button_pin)
{
	// static 지역변수에 static 을 선언하면 함수를 빠져나와 다시 들어가도 이전값을 유지한다.
	static unsigned char button_status[BUTTON_NUMBER] =
	{
		BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE , BUTTON_RELEASE
	};
	
	int current_state;
	
	// 1. 버튼을 읽는다.
	current_state = BUTTON_PIN & (1 << button_pin);
	
	//2. 버튼 상태 check
	if (current_state && button_status[button_num] == BUTTON_RELEASE) // 버튼이 처음 눌려진 상태
	{
		//_delay_ms(20);	// noise 가 지나가기를 기다림
		button_status[button_num] =  BUTTON_PRESS;
		return 0;		// 아직은 완전히 눌렀다 뗀 상태가 아님
	}
	
	
	
	else if (button_status[button_num] == BUTTON_PRESS && current_state == BUTTON_RELEASE)
	{
		// 버튼이 이전에 눌려진 상태 + 지금은 떼어진 상태
		// 다음 버튼을 체크하기 위해 초기화
		button_status[button_num] = BUTTON_RELEASE;
		//_delay_ms(20);
		return 1;		// 완전히 1번 눌렀다 뗀 상태로 인정한다.
	};
	
	return 0;			// 버튼이 open 상태
	
}