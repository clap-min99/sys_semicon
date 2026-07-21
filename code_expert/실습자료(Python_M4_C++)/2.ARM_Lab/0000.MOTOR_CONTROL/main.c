#include "device_driver.h"
#include <stdio.h>

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Clock_Init();
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
	LED_Init();
	Key_Poll_Init();
	
}

/* Key 인식 */

#if 0

void Main(void)
{
	Sys_Init(115200);
	printf("KEY Input Test #1\n");

	/* 아래 코드 수정 금지 : Port-C Clock Enable */
	Macro_Set_Bit(RCC->AHB1ENR, 2); 

	// KEY(PC13)을 GPIO 입력으로 선언
	Macro_Clear_Area(GPIOC->MODER, 0x3, 26);

	for(;;)
	{
		// KEY가 눌렸으면 LED(PA5) ON, 안 눌렸으면 OFF
		if(Macro_Check_Bit_Set(GPIOC->IDR, 13)){
			(Macro_Clear_Bit(GPIOA->ODR, 5));
			}
		else
		(Macro_Set_Bit(GPIOA->ODR, 5));
	}
}

#endif

// 1. 정방향
#if 0
void Main(void)
{
	Sys_Init(115200);
	Macro_Set_Bit(RCC->AHB1ENR, 0); // GPIOA 클럭 Enable

	Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 0); 
	Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 2);

	Macro_Set_Bit(GPIOA->ODR, 0);   
	Macro_Clear_Bit(GPIOA->ODR, 1); 

	for(;;)
	{
		// 계속 정방향 유지
	}
}
#endif


// 2. 역방향
#if 0
void Main(void)
{
	Sys_Init(115200);
	Macro_Set_Bit(RCC->AHB1ENR, 0); // GPIOA 클럭 Enable

	Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 0); 
	Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 2);

	Macro_Set_Bit(GPIOA->ODR, 1);   
	Macro_Clear_Bit(GPIOA->ODR, 0); 

	for(;;)
	{
		// 계속 정방향 유지
	}
}

#endif


// 3. 스위치 방향제어
#if 1
void Main(void)
{
	Sys_Init(115200);
	Macro_Set_Bit(RCC->AHB1ENR, 0);
	Macro_Set_Bit(RCC->AHB1ENR, 2); 
	
	// 스위치
	// Macro_Write_Block(GPIOC->MODER, 0x3, 0x0, 14);
	// Macro_Write_Block(GPIOC->PUPDR, 0x3, 0x1, 14);

	// 모터
	Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 0);
	Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 2);

	int flag = 0;

	for(;;)
			{
				if(Key_Get_Pressed())
				{
					TIM4_Repeat(1000);
					int cnt = 0;

					while (Key_Get_Pressed()) 
					{
						if (TIM4_Check_Timeout()) 
						{
							cnt++;
						}
						if (cnt>=3) break;
					}
					TIM4_Stop();

					Key_Wait_Key_Released();
					
					Macro_Clear_Bit(GPIOA->ODR, 0);   
					Macro_Clear_Bit(GPIOA->ODR, 1); 
					
					if (cnt>=3)
					{
						Key_Wait_Key_Released();
					}

					else 
					{
						// for(int i=0; i<40000; i++) {};
						TIM2_Delay(500);

						if (flag == 0) 
						{
							Macro_Set_Bit(GPIOA->ODR, 0);   
							Macro_Clear_Bit(GPIOA->ODR, 1); 
							flag = 1;
						}
						
						else 
						{
							Macro_Set_Bit(GPIOA->ODR, 1);   
							Macro_Clear_Bit(GPIOA->ODR, 0); 
							flag = 0;
						}
					}
					
				}
				
			}

}
#endif