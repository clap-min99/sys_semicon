#include "stm32f4xx.h"
#include "option.h"
#include "macro.h"
#include "malloc.h"

extern volatile unsigned int key_pressed_flag;
extern unsigned int pwm_default;
extern volatile unsigned int motor_dir;

// key_event.c

extern void Get_Pressed_Check(void); 

// Uart.c

extern void Uart2_Init(int baud);
extern void Uart2_Send_Byte(char data);
extern char Uart2_Get_Char(void);
extern char Uart2_Get_Pressed(void);

// SysTick.c

extern void SysTick_Run(void);

// Led.c

extern void LED_Init(void);
extern void LED_On(void);
extern void LED_Off(void);

// Clock.c

extern void Clock_Init(void);

// key.c

extern void Key_Poll_Init(void);
extern int Key_Get_Pressed(void);

// motor.c
extern void Motor_CW(void);
extern void Motor_CCW(void);
extern void Motor_Stop(void);

// timer.c
extern void TIM2_Init(void);
extern void TIM2_Delay(int time);
extern void TIM2_SW_Start(int time);
extern unsigned int TIM2_SW_Stop(void);
extern int TIM2_SW_T_CHK(void);

extern void TIM4_SW_Start(int time);
extern int TIM4_SW_T_CHK(void);
extern void TIM4_SW_Stop(void);
extern void TIM4_Change_Value(int time);

extern void TIM5_Init(void);
extern void TIM5_CW(void);
extern void TIM5_CCW(void);
extern void TIM5_Out_PWM(unsigned short freq, int duty);
extern void TIM5_Out_Stop(void);