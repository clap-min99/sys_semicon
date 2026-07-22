#include "device_driver.h"

void Motor_CW(void)
{
    Motor_Stop();
    TIM5_CW();
    Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 2);
    Macro_Clear_Bit(GPIOA->ODR, 1);
    TIM5_Out_PWM(10000, pwm_default);

}

void Motor_CCW(void)
{
    TIM5_CCW();
    Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 0);
    Macro_Clear_Bit(GPIOA->ODR, 0);
    TIM5_Out_PWM(10000, pwm_default);
}

void Motor_Stop(void)
{
    Macro_Write_Block(GPIOA->MODER, 0xf, 0x5, 0);
    Macro_Clear_Bit(GPIOA->ODR, 0);
    Macro_Clear_Bit(GPIOA->ODR, 1);
}