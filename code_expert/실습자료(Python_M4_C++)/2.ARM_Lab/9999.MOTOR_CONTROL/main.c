#include "device_driver.h"
#include <stdio.h>

volatile unsigned int key_pressed_flag = 0;
unsigned int pwm_default = 65;
volatile unsigned int motor_dir= 0;

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Clock_Init();
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
	LED_Init();
	Key_Poll_Init();
	TIM5_Init();

}


// 3. 스위치 방향제어

void Main(void)
{
	Sys_Init(115200);
	Macro_Set_Bit(RCC->AHB1ENR, 0);
	Macro_Set_Bit(RCC->AHB1ENR, 2); 


	for(;;)
	{
		Get_Pressed_Check();
		
		if (key_pressed_flag) 
		{
			if (Macro_Check_Bit_Set(TIM2->SR, 0))
			{
				break;
			}
		}
		
	}

}
