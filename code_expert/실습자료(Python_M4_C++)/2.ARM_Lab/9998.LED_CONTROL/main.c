#include "device_driver.h"
#include <stdio.h>

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
	Clock_Init();
	LED_Init();
	
}

void Main(void)
{
	Sys_Init(115200);
	printf("led test");

	int led = 0;

	for(;;)
	{
		(led ^= 1) ? LED_Off() : LED_On();
		TIM2_Delay(500);
		
	}

}
