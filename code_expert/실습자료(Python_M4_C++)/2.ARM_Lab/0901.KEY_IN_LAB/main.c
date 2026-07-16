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

#if 0
void Main(void)
{
	int k;
	Sys_Init(115200);
	printf("KEY Input Toggling #1\n");

	Macro_Set_Bit(RCC->AHB1ENR, 2); 
	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0, 26);

	for(;;)
	{
		// KEY(PC13)이 눌릴때마다 LED(PA5)가 Toggling하도록 코드 작성		
		// 로컬변수는 쓰고 싶은만큼 써도 된다 -> 컴파일러가 최적화 잘해준다
		// 코드 라인 수는 최적화랑 무관하다.
		k = Macro_Extract_Area(~GPIOC->IDR, 0x1, 13);
		Macro_Write_Block(GPIOA->ODR, 0x1, k, 5);
		
	}
}

#endif


#endif

/* Key에 의한 LED Toggling */

#if 0

void Main(void)
{
	
	Sys_Init(115200);
	printf("KEY Input Toggling #1\n");

	Macro_Set_Bit(RCC->AHB1ENR, 2); 
	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0, 26);

	int flag = 0;
	for(;;)
	{
		if (!flag && Macro_Check_Bit_Clear(GPIOC->IDR, 13)){		// 스위치가 눌림
			Macro_Invert_Bit(GPIOA->ODR, 5);
			flag = 1;
		}
		else if (flag && Macro_Check_Bit_Set(GPIOC->IDR, 13)) flag=0; // 스위치가 떼짐
		

	}
}

#endif

// 과제
#if 1
void Main(void)
{
	Sys_Init(115200);
	Macro_Set_Bit(RCC->AHB1ENR, 2); 
	
	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0, 14);
	Macro_Write_Block(GPIOC->PUPDR, 0x3, 0x1, 14);
	
	for(;;)
	{
		if (Macro_Check_Bit_Clear(GPIOC->IDR, 7)) {
		Macro_Clear_Bit(GPIOA->ODR, 5);
	}
	else
		(Macro_Set_Bit(GPIOA->ODR, 5));
	}
	
}
#endif