/*
 * 03.TIMER_FND_BTN_CONTROL.c
 *
 * Created: 2026-06-15 오후 3:44:54
 * Author : kccistc
 */ 

/*
 * main.c
 *
 * Timer2 (8bit) Overflow Interrupt 를 이용해 FND 구동
 * 분주비: 256분주
 */

#define F_CPU 16000000UL
#include <avr/io.h>
// #include <avr/interrupt.h>   // sei, ISR 등

#include "button.h"
extern void init_button(void);
extern int get_button(int button_num, int button_pin);

extern int fnd_main();
extern int init_fnd();
extern void init_timer2(void);   

#define MODE_CLOCK   0   /* 분:초 시계   */
#define MODE_CHRONO  1   /* 초시계       */
#define MODE_SW      2   /* 스탑워치     */


int main(void)
{
	init_fnd();
	init_button();
	init_timer2();       
	
	fnd_main();
	
	while (1)
	{
		
	}
}

