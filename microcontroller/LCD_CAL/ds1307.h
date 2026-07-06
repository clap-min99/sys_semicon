///*
 //* ds1307.h
 //*
 //* Created: 2026-07-01 오전 11:51:19
 //*  Author: kccistc
 //*/ 
//
//
//#ifndef DS1307_H_
//#define DS1307_H_
//
///*
	//----- HW -----
	//i2c통신 사용
	//
	//----- REGISTER -----
	//addr			bit7|	 6|	     5| 	 4|	   3|	 2|	    1|bit0
	//00H	seconds		ch	|      10 SECONDS     |			SECONDS
		//minutes		X	|      10 MINUTES     |			MINUTES
		//hour		X	|12/24|     AP|  10 HR|			HOURS
		//day			X	|	 X|	     X|	     X|	   X|		DAY	
		//date		X	|	 X|	    10 DATE   |			DATE
		//month		X	|	 X|	     X|10MONTH|			MONTH		
		//year					10YEAR		  |			YEAR
	//07H	control		OUT |	 X|		 X|SWWE	  |	   X|    X|  RS1|RS0
	//08H	RAM 56*8
	//
	//----- CONTROL REG -----
	//OUT : This bit controls the output level of the SQW/OUT pin when the square wave
	//output is disabled.  If SQWE=0, the logic level on the SQW/OUT pin is 1 if OUT=1 and is 0 if OUT=0.
	//
	//SQWE : (Square Wave Enable): This bit, when set to a logic 1, will enable the oscillator output.  The
	//frequency of the square wave output depends upon the value of the RS0 and RS1 bits
	//
	//RS : (Rate Select): These bits control the frequency of the square wave output when the square wave
	//output has been enabled.  Table 1 lists the square wave frequencies that can be selected with the RS bits.
	//
		//RS1|	RS2|	SQW OUTPUT FREQUENCY
		  //0|	  0|	1Hz
		  //0|	  1|	4.096kHz
		  //1|	  0|	8.192kHz
		  //1|	  1|	32768kHz
//*/
//
//
//#define F_CPU 16000000UL
//
//#include <avr/io.h>
//#include <avr/interrupt.h> //sei 등의 함수
//#include <stdio.h>
//#include <util/delay.h>
//#include <string.h>
//
//#define DS1307_ADDR        0x68
//
///* Register Address */
//#define DS1307_SEC     0x00
//#define DS1307_MIN     0x01
//#define DS1307_HOURS   0x02
//#define DS1307_DAY     0x03
//#define DS1307_DATE    0x04
//#define DS1307_MONTH   0x05
//#define DS1307_YEAR    0x06
//#define DS1307_CTRL    0x07
//
//#define DS1307_DDR		DDRF
//#define DS1307_CLK_PORT	PORTF
//
//#define DS1307_DAT_PORT	PORTF
//#define DS1307_DAT_PIN	PINF
//
//#define DS1307_RST_PORT	PORTF
//
//#define DS1307_CLK	0	//0	번핀
//#define DS1307_DAT	1
//#define DS1307_RST	2
//
//typedef struct _ds1307
//{
	//uint8_t seconds;
	//uint8_t minutes;
	//uint8_t hours;
	//uint8_t date;
	//uint8_t month;
	//uint8_t dayofweek;
	//uint8_t year;
	//uint8_t ampm;
	//uint8_t hourmode;
//} t_ds1307;
//
//
//
//#endif /* DS1307_H_ */