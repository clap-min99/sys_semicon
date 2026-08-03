#include "device_driver.h"
#include <stdio.h>

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Clock_Init();
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
	LED_Init();
}

static volatile unsigned short Arr_CCR[24 * 4 + 1];
static volatile unsigned int bit_count = 0;
static volatile unsigned int display_finish = 0;

/* TIM3 ISR */

void TIM3_IRQHandler(void)
{
	if(bit_count > (24 * 4))
	{
		Macro_Clear_Bit(TIM3->CR1, 0);
		display_finish = 1;
		Macro_Clear_Bit(TIM3->DIER, 0);
		NVIC_DisableIRQ(29);
	}

	TIM3->CCR3 = Arr_CCR[bit_count++];
	Macro_Clear_Bit(TIM3->SR, 0);
	NVIC_ClearPendingIRQ(29);
}

#define ARR_R	6000
#define CCR_R	ARR_R
#define ARR_D	120
#define CCR_1	38	// Active Low
#define CCR_0	82	// Active Low

static void Color_LED_Init(void) // TIM3_CH3(PB0)
{
	Macro_Set_Bit(RCC->AHB1ENR, 1);
	Macro_Set_Bit(RCC->APB1ENR, 1);

	Macro_Clear_Bit(GPIOB->ODR, 0);
	Macro_Clear_Bit(GPIOB->OTYPER, 0);
	Macro_Write_Block(GPIOB->MODER, 0x3, 0x1, 0);  	// PB0 => GPIO OUT
	Macro_Write_Block(GPIOB->AFR[0], 0xf, 0x2, 0); 	// PB0 => AF02	

	TIM3->PSC = 0;
	TIM3->CR1 = (1<<4)|(0<<3)|(0<<0);
	TIM3->CCER = (1<<9)|(1<<8);
	Macro_Write_Block(TIM3->CCMR2, 0xff, 0x68, 0);
	Macro_Write_Block(GPIOB->MODER, 0x3, 0x2, 0);  	// PB0 => ALT		
}

static void Color_LED_Draw(void) // TIM3_CH3(PB0)
{
	bit_count = 1;
	display_finish = 0;
	TIM3->ARR = ARR_R;
	TIM3->CCR3 = CCR_R;
	TIM3->EGR |= 1<<0;

	Macro_Clear_Bit(TIM3->SR, 0);
	NVIC_ClearPendingIRQ(29);
	Macro_Set_Bit(TIM3->DIER, 0);
	NVIC_EnableIRQ(29);

	Macro_Set_Bit(TIM3->CR1, 0);
	TIM3->ARR = ARR_D;
	TIM3->CCR3 = Arr_CCR[0];

	while(!display_finish);
}

static void Make_Color_LED_Data(const unsigned int *d)
{
	int i, digit;

	for(digit = 0; digit < 4; digit++)
	{
		for(i = 0; i < 24; i++)
		{
			Arr_CCR[digit * 24 + i] = ((d[digit] >> (23 - i)) & 1) ? CCR_1 : CCR_0;
		}
	}

	Arr_CCR[24 * 4] = ARR_D;
}

static char _Uart2_Get_Char(void)
{
	while(!Macro_Check_Bit_Set(USART2->SR, 5));
	return (char)USART2->DR;
}

const unsigned int d[3][4] = {{0xFF0000u, 0x00FF00u, 0x0000FFu, 0xFFFFFFu}, // GRB
							  {0x555555u, 0xFF00FFu, 0xFFFF00u, 0x00FFFFu}, 
							  {0x00FF00u, 0xFF0000u, 0x0000FFu, 0xFFFF00u}}; 

const unsigned int black[4] = {0x000000u, 0x000000u, 0x000000u, 0x000000u};
							
void Main(void)
{
	Sys_Init(115200);
	printf("\nFull Color LED Test\n");

	Color_LED_Init();
	Make_Color_LED_Data(black);
	Color_LED_Draw();

	for(;;)
	{
		printf("Color Table? ");
		int x = _Uart2_Get_Char() - '0';
		printf("%c\n", x + '0');

		if(x >= 0 && x <= 2)
		{
			Make_Color_LED_Data(d[x]);
		}
		
		Color_LED_Draw();
	}
}

