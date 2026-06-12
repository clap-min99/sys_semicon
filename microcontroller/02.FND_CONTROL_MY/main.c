/*
 * 02.FND_CONTROL_MY.c
 *
 * Created: 2026-06-12 오후 1:20:39
 * Author : kccistc
 */ 

#define F_CPU 16000000UL		// 16MHz
#include <avr/io.h>				// PORTA PORTD 등의 I/O register 들이 들어있음.
#include <util/delay.h>

#include "button.h"

extern void init_button(void);
extern int get_button(int button_num, int button_pin);

extern int fnd_main();
extern int init_fnd();


#define MODE_CLOCK   0   /* 분:초 시계   */
#define MODE_CHRONO  1   /* 초시계       */
#define MODE_SW      2   /* 스탑워치     */



int main(void)
{
   
	init_fnd();
	init_button();
	
    while (1) 
    {
		fnd_main();          
	}
	

}

