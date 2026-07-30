#include "device_driver.h"
#include <stdio.h>

#define GAMMA(v)   (((v) * (v)) >> 8)


volatile unsigned char Uart_Data=0;
volatile int Uart_Data_In=0;

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Clock_Init();
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
	LED_Init();
}

static unsigned char frame[12];
static unsigned char hue = 0;

void Animation_Step(void)
{
    int i;
    unsigned char r, g, b;

    for(i = 0; i < 4; i++)
    {
        Hue_To_RGB(hue + i * 64, &r, &g, &b);   // 픽셀마다 색상 오프셋
        frame[i*3 + 0] = GAMMA(g) >> 2;         // GRB, 밝기 1/4
        frame[i*3 + 1] = GAMMA(r) >> 2;
        frame[i*3 + 2] = GAMMA(b) >> 2;
    }
    hue += 2;                                    // 다음 프레임
}

void Hue_To_RGB(unsigned char h, unsigned char *r, unsigned char *g, unsigned char *b)
{
    unsigned char reg = h / 43;
    unsigned char rem = (h % 43) * 6;

    switch(reg)
    {
        case 0: *r = 255;       *g = rem;       *b = 0;         break;
        case 1: *r = 255 - rem; *g = 255;       *b = 0;         break;
        case 2: *r = 0;         *g = 255;       *b = rem;       break;
        case 3: *r = 0;         *g = 255 - rem; *b = 255;       break;
        case 4: *r = rem;       *g = 0;         *b = 255;       break;
        default:*r = 255;       *g = 0;         *b = 255 - rem; break;
    }
}

 

void Main(void)
{
	Sys_Init(115200);
	printf("WS2812B Pulse Test\n");

	SPI1_SC16IS752_Init(32); 			
	SPI1_SC16IS752_Config_GPIO(0xFF);
	SPI1_SC16IS752_Write_GPIO(0xFF);
	// Uart2_RX_Interrupt_Enable(1);
	//NVIC_SetPriority(38, 2); 

 	/* GRB × 4 픽셀 */
    // unsigned char led[12] = {
    //     0x00, 0x20, 0x00,   // 1번: Red
    //     0x20, 0x00, 0x00,   // 2번: Green
    //     0x00, 0x00, 0x20,   // 3번: Blue
    //     0x20, 0x20, 0x20    // 4번: White
    // };

    TIM3_Out_Init();
    TIM4_Repeat(20);     
	
	for(;;)
	{

		if(TIM4_Check_Timeout())       // 논블로킹 체크
		{
			Animation_Step();          // 프레임 갱신
			if(!WS2812_Is_Busy())
			{
				WS2812_Encode(frame, 12);
				WS2812_Send();
			}
		}
	}
}
