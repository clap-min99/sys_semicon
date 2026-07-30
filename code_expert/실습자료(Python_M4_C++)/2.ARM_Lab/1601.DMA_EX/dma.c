#include "device_driver.h"
#include "stm32f411xe.h"

void DMA2_Stream0_M2M_Start(void * src_addr, void * dst_addr, int num)
{
	Macro_Set_Bit(RCC->AHB1ENR, 22);

    DMA2_Stream0->CR = (0x0 << 25)|(0x2 << 13)|(0x2 << 11)|(0x1 << 10)|(0x1 << 9)|(0x2 << 6)|(0x0 << 0);
	// 25(0x0): 채널 선택 / 13(0x2): MSIZE(memorysize) / 11(0x2): PSIZE(perisize)
	// 9(0x1): PINC peri 증가모드 / 10(0x1): MINC 증가 모드 
	// 0(0x0): enable 일단 꺼놓음 / 6(0x2): DIR MTM 
	DMA2_Stream0->FCR = (0x1 << 2)|(0x3 << 0);
	DMA2_Stream0->PAR  = (unsigned int)src_addr;
	DMA2_Stream0->M0AR = (unsigned int)dst_addr;
	DMA2_Stream0->NDTR = num;
	
	DMA2->LIFCR = 0x3F << 0;			// 111111 6자리 클리어
	Macro_Set_Bit(DMA2_Stream0->CR, 4);	
	NVIC_ClearPendingIRQ(56);
	NVIC_EnableIRQ(56);
		
	Macro_Set_Bit(DMA2_Stream0->CR, 0);	
}

void DMA1_Stream6_USART2_TX_Satrt(void * src_addr, int num)
{
	Macro_Set_Bit(RCC->AHB1ENR, 21);

    DMA1_Stream6->CR = (0x4 << 25)|(0x0 << 13)|(0x0 << 11)|(0x1 << 10)|(0x0 << 9)|(0x1 << 6)|(0x0 << 0);
	// 0(0x0): enable 꺼놓음 / 6(0x1): DIR MTP(MEM TO PERI)
	// 9(0X0): PINC peri 고정모드 / 10(0X1): MINC memory 증가모드

	DMA1_Stream6->FCR = 0;
	DMA1_Stream6->PAR  = (unsigned int)&USART2->DR;
	DMA1_Stream6->M0AR = (unsigned int)src_addr;
	DMA1_Stream6->NDTR = num;
	
	DMA1->HIFCR = 0x3F << 16;
	Macro_Set_Bit(DMA1_Stream6->CR, 4);
	NVIC_ClearPendingIRQ(17);
	NVIC_EnableIRQ(17);

	Macro_Set_Bit(DMA1_Stream6->CR, 0);	
}

#if 0
void DMA1_Stream6_USART2_TX_Satrt(void * src_addr, int num)
{
	Macro_Set_Bit(RCC->AHB1ENR, 21);

    DMA1_Stream6->CR = (0x4 << 25)|(0x0 << 13)|(0x0 << 11)|(0x1 << 10)|(0x0 << 9)|(0x1 << 6)|(0x0 << 0);
	// 0(0x0): enable 꺼놓음 / 6(0x1): DIR MTP(MEM TO PERI)
	// 9(0X0): PINC peri 고정모드 / 10(0X1): MINC memory 증가모드

	DMA1_Stream6->FCR = 0;
	DMA1_Stream6->PAR  = (unsigned int)&USART2->DR;
	DMA1_Stream6->M0AR = (unsigned int)src_addr;
	DMA1_Stream6->NDTR = num;
	
	DMA1->HIFCR = 0x3F << 0;
	Macro_Set_Bit(DMA1_Stream6->CR, 4);
	NVIC_ClearPendingIRQ(15);
	NVIC_EnableIRQ(15);

	Macro_Set_Bit(DMA1_Stream6->CR, 0);	
}
#endif
