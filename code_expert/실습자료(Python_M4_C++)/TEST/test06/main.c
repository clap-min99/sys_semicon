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
	printf("\nTimer 4 Interrupt Test\n");

	Key_ISR_Enable(1);
	Uart2_RX_Interrupt_Enable(1);
	// TIM4_Repeat_Interrupt_Enable(1, 200);

	// int d = 0;

	for(;;)
	{
		if (Key_Pressed)
		{
			TIM3_Stopwatch_Start();
			
			if (!Key_Pressed)
			{
				unsigned int r = TIM3_Stopwatch_Stop();
				printf("%d", r);
			}
			

		}
		

	}
}
