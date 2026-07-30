#include <stdio.h>
#include "device_driver.h"


#define WS_ARR_BIT   (120 - 1)
#define WS_T0H       38
#define WS_T1H       82
#define WS_RESET_N   48          // 48 x 1.25us = 60us

#define WS_MAX_LED   4           // 픽셀 수에 맞춰 조정
#define WS_MAX_BIT   (WS_MAX_LED * 24)


static unsigned short ws_buf[WS_MAX_BIT];
static volatile int ws_idx, ws_total, ws_rst;
static volatile int ws_busy;
static volatile int ws_pre;


int WS2812_Encode(unsigned char *grb, int nbyte)
{
    int i, b, k = 0;
    if(ws_busy) return -1; 

    for(i = 0; i < nbyte; i++)
        for(b = 7; b >= 0; b--)
            ws_buf[k++] = (grb[i] & (1 << b)) ? WS_T1H : WS_T0H;
    ws_total = k;

    return 0;
}

int WS2812_Send(void)
{
    if(ws_busy) return -1;

    ws_idx = 0;
    ws_rst = 0;
    ws_pre = WS_RESET_N;
    ws_busy = 1;

    TIM3->PSC = 0;                      // 0: 1분주
    TIM3->ARR = WS_ARR_BIT;             // 주기 ARR: 119(120)

    TIM3->CCR3 = 0;                     // 첫 주기는 Low (더미)
    Macro_Set_Bit(TIM3->EGR, 0);        // UG → shadow=0 → 출력 확실히 Low
    TIM3->CCR3 = 0;                     // preload도 0

    Macro_Clear_Bit(TIM3->SR, 0);
    NVIC_ClearPendingIRQ(29);
    NVIC_SetPriority(29, 0);
    Macro_Set_Bit(TIM3->DIER, 0);
    NVIC_EnableIRQ(29);

    TIM3->CR1 = (1<<7)|(0<<4)|(0<<3)|(1<<0);

    return 0;
}

int WS2812_Is_Busy(void) { return ws_busy; }


void WS2812_Debug_Print(void)
{
    int i;
    printf("ws_buf: ");
    for(i = 0; i < 24; i++)
        printf("%d ", ws_buf[i]);
    printf("\n");
}



void TIM3_IRQHandler(void)
{
    Macro_Clear_Bit(TIM3->SR, 0);

    if(ws_pre > 0)                  // 분기 하나 추가
    {
        TIM3->CCR3 = 0;
        ws_pre--;
    }
    else if(ws_idx < ws_total)
    {
        TIM3->CCR3 = ws_buf[ws_idx++];
    }
    else if(ws_rst < WS_RESET_N)
    {
        TIM3->CCR3 = 0;
        ws_rst++;
    }
    else
    {
        Macro_Clear_Bit(TIM3->CR1, 0);
        Macro_Clear_Bit(TIM3->DIER, 0);
        NVIC_DisableIRQ(29);
        ws_busy = 0;
    }
}