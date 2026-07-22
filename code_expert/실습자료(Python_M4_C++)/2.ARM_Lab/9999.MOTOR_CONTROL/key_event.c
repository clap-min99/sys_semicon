#include "device_driver.h"

void Get_Pressed_Check(void) 
{
    if (!key_pressed_flag)
    {
        if (Key_Get_Pressed())
        // 3초 세기
        {
            TIM2_SW_Start(3000);
            TIM4_SW_Stop();
            key_pressed_flag = 1;
        }
    }

    else 
    {
        if (!Key_Get_Pressed())
        {
            TIM2_SW_Stop();
            TIM4_SW_Start(500);
            key_pressed_flag = 0;
            TIM4_SW_T_CHK(500);
        }
    }

}
