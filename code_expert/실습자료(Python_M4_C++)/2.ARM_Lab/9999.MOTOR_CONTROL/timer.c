#include "device_driver.h"

#define TIM2_TICK 		20 						// usec
#define TIM2_FREQ		(1000000./TIM2_TICK) 	// hz
#define TIM2_1ms_Pls	(TIM2_FREQ/1000.)		// 개
#define TIM2_MAX 		(0xFFFFU)

#define TIM4_TICK 		20 						// usec
#define TIM4_FREQ		(1000000./TIM4_TICK) 	// hz
#define TIM4_1ms_Pls	(TIM4_FREQ/1000.)		// 개
#define TIM4_MAX 		(0xFFFFU)
#define INIT_ARR 		(0xFFFFU)

#define TIM5_FREQ					(8000000)			// Hz
#define TIM5_TICK					(1000000/TIM5_FREQ)	// usec
#define TIME5_PLS_OF_1ms			(1000/TIM5_TICK)


void TIM2_SW_Start(int time)
{	
	Macro_Set_Bit(RCC->APB1ENR, 0);						// TIM2EN

	// TIM2 CR1 설정: down count, one pulse
	TIM2->CR1 = (0x1<<4) | (0x1<<3);		
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	TIM2->PSC = (unsigned int)(TIMXCLK/TIM2_FREQ+0.5)-1;	// 분주는 (n+1) 되므로 목표한 값에서 -1
	
	// ARR 초기값 설정 => 최대값 0xFFFF 설정
	TIM2->ARR = INIT_ARR; 
	
	Macro_Clear_Bit(TIM2->SR, 0);

	// UG 이벤트 발생
	Macro_Set_Bit(TIM2->EGR, 0);


	// TIM2 start
	Macro_Set_Bit(TIM2->CR1, 0);
}

unsigned int TIM2_SW_Stop(void)
{
	unsigned int time;

	// TIM2 stop
	Macro_Clear_Bit(TIM2->CR1, 0);
	// CNT 초기 설정값 (0xffffff)와 현재 CNT의 펄스수 차이를 구하고
	// 그 펄스수 하나가 20usec이므로 20을 곱한값을 time에 저장
	time = (INIT_ARR - (TIM2->CNT))*20;
	// 계산된 time 값을 리턴(단위는 usec)
	return time;
}

int TIM2_SW_T_CHK(void)
{
	// 타이머가 timeout 이면 1 리턴, 아니면 0 리턴
	if (Macro_Check_Bit_Set(TIM2->SR, 0)){
		Macro_Clear_Bit(TIM2->SR, 0);
		return 1;
	}
	else return 0;
}


void TIM4_SW_Start(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 2);

	// TIM4 CR1: ARPE=0, down counter, repeat mode
	TIM4->CR1 = (0x1<<4) | (0x1<<3);	

	// PSC(50KHz),  ARR(reload시 값) 설정
	TIM4->PSC = (unsigned int)(TIMXCLK/TIM4_FREQ+0.5)-1;

	// ARR은 1ms 필요 펄스 * time
	TIM4->ARR = TIM4_1ms_Pls * time;

	// UG 이벤트 발생
	Macro_Set_Bit(TIM4->EGR, 0);

	// Update Interrupt Pending Clear
	Macro_Clear_Bit(TIM4->SR, 0);
	
	// TIM4 start 
	Macro_Set_Bit(TIM4->CR1, 0);

}

int TIM4_SW_T_CHK(void)
{
	// 타이머가 timeout 이면 1 리턴, 아니면 0 리턴
	if (Macro_Check_Bit_Set(TIM4->SR, 0)){
		Macro_Clear_Bit(TIM4->SR, 0);
		return 1;
	}
	else return 0;
}

void TIM4_SW_Stop(void)
{
	Macro_Clear_Bit(TIM4->CR1, 0);
}

void TIM5_Init(void)
{
	Macro_Set_Bit(RCC->AHB1ENR, 0);		// portA
	Macro_Set_Bit(RCC->APB1ENR, 3);		// timer
}
void TIM5_CW(void)
{
    Macro_Write_Block(GPIOA->MODER, 0x3, 0x2, 0);      // PA0 => ALT(MODER -> 10: alternate function)
    Macro_Write_Block(GPIOA->AFR[0], 0xf, 0x2, 0);     // PA0 => AF02
    Macro_Write_Block(TIM5->CCMR1,0xff, 0x60, 0);
    TIM5->CCER = (0<<1)|(1<<0);
}

void TIM5_CCW(void)
{
    Macro_Write_Block(GPIOA->MODER, 0x3, 0x2, 2);       // PA1 => ALT(MODER -> 10: alternate function)
    Macro_Write_Block(GPIOA->AFR[0], 0xf, 0x2, 4);  // PA1 => AF02

    Macro_Write_Block(TIM5->CCMR1,0xff, 0x60, 8);
    TIM5->CCER = (0<<5)|(1<<4);
}

void TIM5_Out_PWM(unsigned short freq, int duty)
{
    TIM5->CR1 = (0x1<<4);
    // Timer 주파수가 TIM5_FREQ가 되도록 PSC 설정
    TIM5->PSC = (unsigned int)(TIMXCLK/TIM5_FREQ+0.5)-1;

    // 요청한 주파수가 되도록 ARR 설정
    // TIM5->ARR = TIM5_FREQ / freq;
    TIM5->ARR = (unsigned int)((double)TIM5_FREQ / freq + 0.5)-1;


     if (!motor_dir) {
        TIM5->CCR1 = (TIM5->ARR) * ((double)duty / 100.);
    } else {
        TIM5->CCR2 = (TIM5->ARR) * ((double)duty / 100.);
    }

    // Manual Update(UG 발생)
    Macro_Set_Bit(TIM5->EGR, 0);

    // Down Counter, Repeat Mode, Timer Start
    Macro_Set_Bit(TIM5->CR1, 0);
}

void TIM5_Out_Stop(void)
{
	Macro_Clear_Bit(TIM5->CR1, 0);
}