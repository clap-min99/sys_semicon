#include "device_driver.h"

void SysTick_Run(unsigned int msec)
{
	// Timer 설정 : 인터럽트 발생 안함, clock source는 HCLK/8, Timer 정지
	// 아래 처럼 해도 되는데, 초기값 설정이니까 대입해서 초기화하는게 일반적
	// Macro_Write_Block(SysTick->CTRL, 0x7, 0x0, 0);
	// Macro_Clear_Bit(SysTick->CTRL, 16);
	SysTick->CTRL = (0x0<<2) | (0x0<<1) | (0x0<<0);

	// 주어진 msec 값 만큼의 msec를 count하는 초기값 설정 (LOAD)
	// SysTick -> VAL , LOAD, CTRL
	SysTick->LOAD = (unsigned int)((HCLK/(8.*1000.))*msec+0.5);
	// VAL 레지스터 값 초기화(0)(아무거나 넣으면 초기화됨) 및 COUNTFLAG Clear
	SysTick->VAL = 0;
	// Timer Start (시작이 되면 자동으로 LOAD의 값을 VAL로 가져간다) 
	Macro_Set_Bit(SysTick->CTRL, 0);
}

int SysTick_Check_Timeout(void)
{
	// Timer의 Timeout이 발생하면 참(1)리턴, 아니면 거짓(0) 리턴
	if (Macro_Check_Bit_Set(SysTick->CTRL, 16)) 
	{
		return 1;
	}
	else return 0;
}

unsigned int SysTick_Get_Time(void)
{
	// Timer의 현재 count 값 리턴(VAL)
	return SysTick->VAL;
}

unsigned int SysTick_Get_Load_Time(void)
{
	// Timer에 설정된 초기값을 리턴(LOAD)
	return SysTick->LOAD;

}

void SysTick_Stop(void)
{
	// Timer Stop
	Macro_Clear_Bit(SysTick->CTRL, 0);
}
