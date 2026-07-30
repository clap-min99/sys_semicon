#include "device_driver.h"

#define TIM3_FREQ 	  			(8000000) 	      	// Hz
#define TIM3_TICK	  			(1000000/TIM3_FREQ)	// usec
#define TIME3_PLS_OF_1ms  		(1000/TIM3_TICK)

#define TIM4_TICK	  		(20) 				// usec
#define TIM4_FREQ 	  		(1000000/TIM4_TICK) // Hz
#define TIME4_PLS_OF_1ms  	(1000/TIM4_TICK)
#define TIM4_MAX	  		(0xffffu)


void TIM4_Repeat(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 2);

	TIM4->CR1 = (1<<4)|(0<<3);
	TIM4->PSC = (unsigned int)(TIMXCLK/TIM4_FREQ + 0.5)-1;
	TIM4->ARR = TIME4_PLS_OF_1ms * time - 1;

	Macro_Set_Bit(TIM4->EGR,0);
	Macro_Clear_Bit(TIM4->SR, 0);
	Macro_Set_Bit(TIM4->CR1, 0);
}

int TIM4_Check_Timeout(void)
{
	if(Macro_Check_Bit_Set(TIM4->SR, 0))
	{
		Macro_Clear_Bit(TIM4->SR, 0);
		return 1;
	}
	else
	{
		return 0;
	}
}

void TIM3_Out_Init(void)
{
	Macro_Set_Bit(RCC->AHB1ENR, 1);
	Macro_Set_Bit(RCC->APB1ENR, 1);
	
	Macro_Write_Block(GPIOB->MODER, 0x3, 0x1, 0);
	Macro_Clear_Bit(GPIOB->OTYPER, 0);              // Push-Pull
	Macro_Clear_Bit(GPIOB->ODR, 0);                 // Low 확정

	
	Macro_Write_Block(GPIOB->MODER, 0x3, 0x2, 0);  	// PB0 => ALT
	Macro_Write_Block(GPIOB->AFR[0], 0xf, 0x2, 0); 	// PB0 => AF02
    Macro_Write_Block(GPIOB->OSPEEDR, 0x3, 0x2, 0); // Fast


	Macro_Write_Block(TIM3->CCMR2,0xff, 0x68, 0);	// capture & compare
	// TIM3->CCMR2 3번: OC3PE- CCR값을 비교 값으로 preload 시키는 것을 enable(repeat모드: 1)
	// TIM3->CCMR
	TIM3->CCER = (0<<9)|(1<<8);
}

void TIM3_Out_Fixed_Test(unsigned short ccr)
{
    TIM3->PSC  = 0;
    TIM3->ARR  = 120 - 1;
    TIM3->CCR3 = ccr;

    Macro_Set_Bit(TIM3->EGR, 0);
    Macro_Clear_Bit(TIM3->SR, 0);
    TIM3->CR1 = (1<<7)|(0<<4)|(0<<3)|(1<<0);
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


