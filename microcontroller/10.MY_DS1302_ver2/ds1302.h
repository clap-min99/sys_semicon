/*
 * ds1302.h
 *
 * Created: 2026-06-26 오후 2:42:24
 *  Author: kccistc
 */ 


#ifndef DS1302_H_
#define DS1302_H_

#define F_CPU 16000000UL	
#include <avr/io.h>			
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
 
#define DS1302_CLK_DDR	DDRF
#define DS1302_CLK_PORT PORTF

#define DS1302_DAT_DDR	DDRF
#define DS1302_DAT_PORT PORTF
#define DS1302_DAT_PIN  PINF	// read

#define DS1302_RST_DDR  DDRF
#define DS1302_RST_PORT PORTF

#define DS1302_CLK	0	
#define DS1302_DAT	1
#define DS1302_RST	2

#define ADDR_SECONDS		0x80	// write만 define(read는 write+1 이므로)
#define ADDR_MINUTES		0x82
#define ADDR_HOUR			0x84
#define ADDR_DATE			0x86
#define ADDR_MONTH			0x88
#define ADDR_DAYOFWEEK		0x8a
#define ADDR_YEAR			0x8c
#define ADDR_WRITEPROTECTED 0x8e
#define ADDR_BURST_READ  0xBF

typedef struct _ds1302
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t date;
	uint8_t month;
	uint8_t dayofweek;	// 1.sun 2.mon
	uint8_t year;
	uint8_t ampm;		// 1.pm	 0.am
	uint8_t hourmode;	// 0: 24 1: 12
	
	} t_ds1302;
	
// t_ds1302 ds1302;


#endif /* DS1302_H_ */