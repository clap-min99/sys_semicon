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

volatile int Key_Pressed = 0;
volatile int Uart_Data_In = 0;
volatile unsigned char Uart_Data = 0;
volatile int TIM4_Expired = 0;

void Main(void)
{
	Sys_Init(115200);
	Macro_Set_Bit(RCC->AHB1ENR, 0); 
	Macro_Set_Bit(RCC->AHB1ENR, 1); 
	Macro_Clear_Area(GPIOB->MODER, 0x3, 16);
	Macro_Write_Block(GPIOB->PUPDR, 0x3, 0x2, 16);

	Macro_Clear_Bit(GPIOA->ODR, 5);

	int flag = 1;

	for(;;)
	{
		if (!flag && Macro_Check_Bit_Set(GPIOB->IDR, 8))
		{
			Macro_Invert_Bit(GPIOA->ODR, 5);
			flag = 1;
		}
		else if (flag && Macro_Check_Bit_Clear(GPIOB->IDR, 8)){
			flag = 0;

		}
	}

}

