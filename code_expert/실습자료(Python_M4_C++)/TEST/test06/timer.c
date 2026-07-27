#include "device_driver.h"

#define TIM2_TICK         	(20) 				// usec
#define TIM2_FREQ 	  		(1000000/TIM2_TICK)	// Hz
#define TIME2_PLS_OF_1ms  	(1000/TIM2_TICK)
#define TIM2_MAX	  		(0xffffu)

#define TIM4_TICK	  		(20) 				// usec
#define TIM4_FREQ 	  		(1000000/TIM4_TICK) // Hz
#define TIME4_PLS_OF_1ms  	(1000/TIM4_TICK)
#define TIM4_MAX	  		(0xffffu)

void TIM3_Stopwatch_Start(void)
{
	Macro_Set_Bit(RCC->APB1ENR, 1);

	// TIM3 CR1 설정: down count, one pulse
	TIM3->CR1 = 0x1U<<4U | 0x01<<3U;
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	TIM3->PSC =  (HCLK / 50000.) - 1U;
	//TIM3->PSC = (HCLK * TIM3_TICK) / 1000000U - 1U;
	// ARR 초기값 설정 => 최대값 0xFFFF 설정
	TIM3->ARR = 0xffffU;
	// UG 이벤트 발생
	TIM3->EGR = 1U<<0;
	// TIM3 start
	TIM3->CR1 |= 0x1U<<0;
}

int TIM3_Check_Timeout(void)
{
	if(Macro_Check_Bit_Set(TIM3->SR, 0))	// 업데이트 발생시
	{
		Macro_Clear_Bit(TIM3->SR, 0);		// 클리어후 // TIM4->SR, 0 은 UIF(Update Interrupt Flag)
		return 1;							// 1 return
	}
	else
	{
		return 0;
	}
}


unsigned int TIM3_Stopwatch_Stop(void)
{
	unsigned int time;
	
	// TIM3 stop
	//TIM3->CR1 &= ~(0x1U<<0);
	// CNT 초기 설정값 (0xffff)와 현재 CNT의 펄스수 차이를 구하고
	time = TIM3->ARR - TIM3->CNT; 
	// 그 펄스수 하나가 20usec이므로 20을 곱한값을 time에 저장
	time *= 20;
	// 계산된 time 값을 리턴(단위는 usec)
	return time;
}

void TIM3_Delay(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 1);

	// TIM3 CR1 설정: down count, one pulse
	Macro_Set_Area(TIM3->CR1, 0x3, 3);
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	//TIM3->PSC = (HCLK * TIM3_TICK) / 1000000U - 1U;
	TIM3->PSC=1920;
	// ARR 초기값 설정 => 요청한 time msec에 해당하는 초기값 설정
	TIM3->ARR = time*50;
	// UG 이벤트 발생
	Macro_Set_Bit(TIM3->EGR,0);
	// UIF(Update Interrupt Pending) Clear
	Macro_Clear_Bit(TIM3->SR,0);
	// TIM3 start
	Macro_Set_Bit(TIM3->CR1, 0);
	// Wait timeout
	while(!(Macro_Check_Bit_Set(TIM3->SR, 0)));
	// TIM3 Stop
	Macro_Clear_Bit(TIM3->CR1, 0);
}

void TIM2_Stopwatch_Start(void)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	TIM2->CR1 = (1<<4)|(1<<3);									// 
	TIM2->PSC = (unsigned int)(TIMXCLK/50000.0 + 0.5)-1;		// 분주 0->1/1->2/..../65536분주
	TIM2->ARR = TIM2_MAX;

	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Set_Bit(TIM2->CR1, 0);
}

unsigned int TIM2_Stopwatch_Stop(void)
{
	unsigned int time;

	Macro_Clear_Bit(TIM2->CR1, 0);					// TIM2->CR1 : CEN, counter enable
	time = (TIM2_MAX - TIM2->CNT) * TIM2_TICK;		// 현재 시간(?) = (최대 시간 - 현재 counter(흐른시간))
	return time;
}


/* Delay Time Max = 65536 * 20use = 1.3sec */

#if 0

void TIM2_Delay(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	TIM2->CR1 = (1<<4)|(1<<3);
	TIM2->PSC = (unsigned int)(TIMXCLK/(double)TIM2_FREQ + 0.5)-1;
	TIM2->ARR = TIME2_PLS_OF_1ms * time;

	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Clear_Bit(TIM2->SR, 0);
	Macro_Set_Bit(TIM2->CR1, 0);

	while(Macro_Check_Bit_Clear(TIM2->SR, 0));

	Macro_Clear_Bit(TIM2->CR1, 0);
}

#else

/* Delay Time Extended */

void TIM2_Delay(int time)
{
	int i;
	unsigned int t = TIME2_PLS_OF_1ms * time;

	Macro_Set_Bit(RCC->APB1ENR, 0);

	TIM2->PSC = (unsigned int)(TIMXCLK/(double)TIM2_FREQ + 0.5)-1;
	TIM2->CR1 = (1<<4)|(1<<3);
	TIM2->ARR = 0xffff;
	Macro_Set_Bit(TIM2->EGR,0);

	for(i=0; i<(t/0xffffu); i++)
	{
		Macro_Set_Bit(TIM2->EGR,0);
		Macro_Clear_Bit(TIM2->SR, 0);
		Macro_Set_Bit(TIM2->CR1, 0);
		while(Macro_Check_Bit_Clear(TIM2->SR, 0));
	}

	TIM2->ARR = t % 0xffffu;
	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Clear_Bit(TIM2->SR, 0);
	Macro_Set_Bit(TIM2->CR1, 0);
	while (Macro_Check_Bit_Clear(TIM2->SR, 0));

	Macro_Clear_Bit(TIM2->CR1, 0);
}

#endif

void TIM4_Repeat(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 2);

	TIM4->CR1 = (1<<4)|(0<<3);
	TIM4->PSC = (unsigned int)(TIMXCLK/(double)TIM4_FREQ + 0.5)-1;
	TIM4->ARR = TIME4_PLS_OF_1ms * time - 1;

	Macro_Set_Bit(TIM4->EGR,0);
	Macro_Clear_Bit(TIM4->SR, 0);
	Macro_Set_Bit(TIM4->CR1, 0);
}

int TIM4_Check_Timeout(void)
{
	if(Macro_Check_Bit_Set(TIM4->SR, 0))	// 업데이트 발생시
	{
		Macro_Clear_Bit(TIM4->SR, 0);		// 클리어후 // TIM4->SR, 0 은 UIF(Update Interrupt Flag)
		return 1;							// 1 return
	}
	else
	{
		return 0;
	}
}

void TIM4_Stop(void)
{
	Macro_Clear_Bit(TIM4->CR1, 0);
}

void TIM4_Change_Value(int time)
{
	TIM4->ARR = TIME4_PLS_OF_1ms * time;
}

void TIM4_Repeat_Interrupt_Enable(int en, int time)
{
	if(en)
	{
		// TIM4 Clock On
		Macro_Set_Bit(RCC->APB1ENR, 2);

		TIM4->CR1 = (1<<4)|(0<<3);
		TIM4->PSC = (unsigned int)(TIMXCLK/(double)TIM4_FREQ + 0.5)-1;
		TIM4->ARR = TIME4_PLS_OF_1ms * time;
		Macro_Set_Bit(TIM4->EGR,0);

		// TIM4 Pending Clear
		Macro_Clear_Bit(TIM4->SR, 0);  
		// NVIC Pending Clear
		NVIC_ClearPendingIRQ(30);
		// TIM4 Interrupt Enable
		Macro_Set_Bit(TIM4->DIER, 0);
		// NVIC Interrupt Enable
		NVIC_EnableIRQ(30);
		// TIM4 Start
		Macro_Set_Bit(TIM4->CR1, 0);
	}

	else
	{
		NVIC_DisableIRQ(30);
		Macro_Clear_Bit(TIM4->CR1, 0);
		Macro_Clear_Bit(TIM4->DIER, 0);
	}
}

#define TIM3_FREQ 	  			(8000000) 	      	// Hz
#define TIM3_TICK	  			(1000000/TIM3_FREQ)	// usec
#define TIME3_PLS_OF_1ms  		(1000/TIM3_TICK)

void TIM3_Out_Init(void)
{
	Macro_Set_Bit(RCC->AHB1ENR, 1);
	Macro_Set_Bit(RCC->APB1ENR, 1);

	Macro_Write_Block(GPIOB->MODER, 0x3, 0x2, 0);  	// PB0 => ALT
	Macro_Write_Block(GPIOB->AFR[0], 0xf, 0x2, 0); 	// PB0 => AF02

	Macro_Write_Block(TIM3->CCMR2,0xff, 0x60, 0);
	TIM3->CCER = (0<<9)|(1<<8);
}

void TIM3_Out_Freq_Generation(unsigned short freq)
{
	TIM3->PSC = (unsigned int)(TIMXCLK/(double)TIM3_FREQ + 0.5)-1;
	TIM3->ARR = (double)TIM3_FREQ/freq-1;
	TIM3->CCR3 = TIM3->ARR/2;

	Macro_Set_Bit(TIM3->EGR,0);
	TIM3->CR1 = (1<<4)|(0<<3)|(0<<1)|(1<<0);
}

void TIM3_Out_Stop(void)
{
	Macro_Clear_Bit(TIM3->CR1, 0);
}

void TIM3_Repeat_Interrupt_Enable(int en, int time)
{
	if(en)
	{
		// TIM3 Clock On
		Macro_Set_Bit(RCC->APB1ENR, 1);

		TIM3->CR1 = (1<<4)|(0<<3);
		TIM3->PSC = (unsigned int)(TIMXCLK/(double)TIM3_FREQ + 0.5)-1;
		TIM3->ARR = TIME3_PLS_OF_1ms * time;
		Macro_Set_Bit(TIM3->EGR,0);

		// TIM4 Pending Clear
		Macro_Clear_Bit(TIM3->SR, 0);  
		// NVIC Pending Clear
		NVIC_ClearPendingIRQ(29);
		// TIM4 Interrupt Enable
		Macro_Set_Bit(TIM3->DIER, 0);
		// NVIC Interrupt Enable
		NVIC_EnableIRQ(29);
		// TIM4 Start
		Macro_Set_Bit(TIM3->CR1, 0);
	}

	else
	{
		NVIC_DisableIRQ(30);
		Macro_Clear_Bit(TIM3->CR1, 0);
		Macro_Clear_Bit(TIM3->DIER, 0);
	}
}

