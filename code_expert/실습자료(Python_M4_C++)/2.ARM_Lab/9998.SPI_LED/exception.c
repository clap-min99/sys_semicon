#include "device_driver.h"
#include <stdio.h>

void _Invalid_ISR(void)
{
	unsigned int r = Macro_Extract_Area(SCB->ICSR, 0x1ff, 0);
	printf("\nInvalid_Exception: %d!\n", r);
	printf("Invalid_ISR: %d!\n", r - 16);
	for(;;);
}

// void USART2_IRQHandler(void)
// {
// 	Uart_Data = (unsigned char)USART2->DR;
// 	Uart2_Send_Byte(Uart_Data);
// 	Uart_Data_In = 1;
// 	NVIC_ClearPendingIRQ(38);
// }

#define RX_SIZE  64
static volatile char rx_buf[RX_SIZE];
static volatile int rx_head, rx_tail;

void USART2_IRQHandler(void)
{
    if(Macro_Check_Bit_Set(USART2->SR, 5))       // RXNE
    {
        char c = (char)USART2->DR;               // 읽으면 RXNE 자동 클리어
        int next = (rx_head + 1) % RX_SIZE;
        if(next != rx_tail)
        {
            rx_buf[rx_head] = c;
            rx_head = next;
        }
    }
}

int Uart2_Get_Byte(char *pc)                     // 0 = 없음, 1 = 받음
{
    if(rx_head == rx_tail) return 0;
    *pc = rx_buf[rx_tail];
    rx_tail = (rx_tail + 1) % RX_SIZE;
    return 1;
}