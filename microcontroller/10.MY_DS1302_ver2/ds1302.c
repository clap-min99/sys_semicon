/*
 * ds1301.c
 *
 * Created: 2026-06-26 오후 2:42:13
 *  Author: kccistc
 */ 


#include "ds1302.h"
#include <avr/interrupt.h> 

void init_ds1302(t_ds1302 *p);
void init_date_time(t_ds1302 *p);
void init_ddr_ds1302(void);
void init_gpio_ds1302(void);

void ds1302_main(void);
void clock_ds1302(void);
void read_time_ds1302(t_ds1302 *p);
void read_date_ds1302(t_ds1302 *p);
void tx_ds1302(uint8_t data);
void rx_1302(uint8_t *pdata8bits);
void write_ds1302(uint8_t addr, uint8_t data);
void rx_burst_1302(uint8_t *pdata8bits);
void read_burst_ds1302(t_ds1302 *p);

uint8_t read_ds1302(uint8_t addr);
uint8_t dec2bcd(uint8_t data);
uint8_t bcd2dec(uint8_t data);

extern void pc_command_processing(t_ds1302 *p); 

void ds1302_main(void)
{
	t_ds1302 rtc;
	
	init_date_time(&rtc);
	init_ddr_ds1302();
	init_gpio_ds1302();		// all LOW로 설정
	init_ds1302(&rtc);
	sei();   // UART 인터럽트 활성화
	
	while (1)
	{
		pc_command_processing(&rtc);
		
		read_burst_ds1302(&rtc);
		
		//// 1. read time
		//read_time_ds1302(&rtc);
		//
		//// 2. read date
		//read_date_ds1302(&rtc);
		
		// 3. printf date & time
		printf("DATE: %d-%d-%d ", rtc.year, rtc.month, rtc.date);
		printf("TIME: %d:%d:%d\n", rtc.hour, rtc.minutes, rtc.seconds);
		
		// 4. delay_ms(1000);
		_delay_ms(1000);
	}

};

void read_time_ds1302(t_ds1302 *p)
{
	p->seconds = read_ds1302(ADDR_SECONDS);
	p->minutes = read_ds1302(ADDR_MINUTES);
	p->hour    = read_ds1302(ADDR_HOUR);
}

void read_date_ds1302(t_ds1302 *p)
{
	p->date  = read_ds1302(ADDR_DATE);
	p->month = read_ds1302(ADDR_MONTH);
	p->year  = read_ds1302(ADDR_YEAR);
}


uint8_t read_ds1302(uint8_t addr)
{
	uint8_t data8bits = 0;	// 1bit씩 읽어서 담을 변수
	
	// 4. CE low
	// 5. return(bcd to dec)
	
	// 1. CE low --> High
	DS1302_RST_PORT |= 1 << DS1302_RST;
	
	// 2. ADDR 전송
	tx_ds1302(addr+1);	// read addr
	
	// 3. DATA 읽어들임
	rx_1302(&data8bits);
	
	// 4. CE HIGH ---> LOW
	DS1302_RST_PORT &= ~(1 << DS1302_RST);
	
	return bcd2dec(data8bits);
	
}

void rx_1302(uint8_t *pdata8bits)
{
	uint8_t temp=0;
	
	// 1. 입력 모드로 설정
	DS1302_DAT_DDR &= ~(1 << DS1302_DAT);		// write mode
	_delay_us(2);           
	
	// LSB로부터 차례로 
	for (int i=0; i<8; i++)
	{
		if (DS1302_DAT_PIN & (1 << DS1302_DAT))
		{
			temp |= 1 << i;		// 1의 조건만 set
		}
		
		// 3. CLK을 high -> low
		if (i != 7)				// 마지막 비트를 읽을 때는 clk을 보내주지 않는다. 
			clock_ds1302();
	}
	*pdata8bits = temp;
};

void init_ds1302(t_ds1302 *p)
{
	write_ds1302(ADDR_WRITEPROTECTED, 0x00);

	write_ds1302(ADDR_SECONDS,   p->seconds);
	write_ds1302(ADDR_MINUTES,   p->minutes);
	write_ds1302(ADDR_HOUR,      p->hour);
	write_ds1302(ADDR_DATE,      p->date);
	write_ds1302(ADDR_MONTH,     p->month);
	write_ds1302(ADDR_DAYOFWEEK, p->dayofweek);
	write_ds1302(ADDR_YEAR,      p->year);
}



// decimal --> bcd
// ex) 25
//	  dec				bcd 
//	00011001		 0010 0101	

uint8_t dec2bcd(uint8_t data)
{
	uint8_t high, low;
	
	high = (data/10) << 4;	// high nibble에 위치
	low = data % 10;
	
	return (high+low);
}

// bcd --> decimal
// 1. 입력 bcd 
// ex. 26년의 bcd
// 7654 3210
// 0010 0110
//	2	  6
// x10	 x1
// ==========
// 26

uint8_t bcd2dec(uint8_t data)
{
	uint8_t high, low;
	
	low = data & 0x0f;
	high = (data >> 4) * 10;	
	
	return (high + low);
}

void write_ds1302(uint8_t addr, uint8_t data)
{
	// 1. CE low --> High
	DS1302_RST_PORT |= 1 << DS1302_RST;
	
	// 2. ADDR 전송
	tx_ds1302(addr);
	
	// 3. DATA 전송
	tx_ds1302(dec2bcd(data));
	
	// 4. CE HIGH ---> LOW
	DS1302_RST_PORT &= ~(1 << DS1302_RST);
	
}

void tx_ds1302(uint8_t data)
{
	// 1. 출력 모드로 설정
	 DS1302_DAT_DDR |= 1 << DS1302_DAT;		// write mode
	 // ex) 0x80
	 //		M	   L
	 //		1000 000
	 for (int i=0; i<8; i++)
	 {
		 // 2. 1 bit를 전송
		 if (data & (1 << i))
			DS1302_DAT_PORT |= 1 << DS1302_DAT;			// 1
		else DS1302_DAT_PORT &= ~(1 << DS1302_DAT);		// 0
		
		// 3. CLK을 high -> low
		clock_ds1302();
	 }
}

void clock_ds1302(void)
{ 
	// LOW ----> HIGH ----> LOW
	DS1302_CLK_PORT &= ~(1<<DS1302_CLK);
	 _delay_us(1);
	DS1302_CLK_PORT |= 1<<DS1302_CLK;
	 _delay_us(1);
	DS1302_CLK_PORT &= ~(1<<DS1302_CLK);
	 _delay_us(1);
}


void init_ddr_ds1302(void)
{
	DDRF &=  ~(1 << DS1302_CLK | 1 << DS1302_DAT | 1 << DS1302_RST);
	DDRF |=  1 << DS1302_CLK | 1 << DS1302_DAT | 1 << DS1302_RST;	// 출력 모드로 설정
	
}

void init_gpio_ds1302(void)
{
	DS1302_CLK_PORT &= ~( 1 << DS1302_CLK | 1 << DS1302_DAT | 1 << DS1302_RST);
	_delay_ms(2);
}



void init_date_time(t_ds1302 *p)
{
	p->year      = 26;
	p->month     = 06;
	p->date      = 29;
	p->dayofweek = 6;
	p->hour      = 10;
	p->minutes   = 02;
	p->seconds   = 00;
}

void rx_burst_1302(uint8_t *pdata8bits)
{
	uint8_t temp = 0;

	DS1302_DAT_DDR &= ~(1 << DS1302_DAT);
	_delay_us(2);

	for (int i = 0; i < 8; i++)
	{
		if (DS1302_DAT_PIN & (1 << DS1302_DAT))
		temp |= 1 << i;

		clock_ds1302();   // ← 마지막 비트도 CLK 보냄 (다음 바이트 준비)
	}
	*pdata8bits = temp;
}

void read_burst_ds1302(t_ds1302 *p)   // 포인터 받기
{
	uint8_t data[7];

	DS1302_RST_PORT |= 1 << DS1302_RST;
	_delay_us(5);

	tx_ds1302(0xBF);

	rx_burst_1302(&data[0]);
	rx_burst_1302(&data[1]);
	rx_burst_1302(&data[2]);
	rx_burst_1302(&data[3]);
	rx_burst_1302(&data[4]);
	rx_burst_1302(&data[5]);
	rx_1302(&data[6]);              // 마지막은 기존 함수

	DS1302_RST_PORT &= ~(1 << DS1302_RST);

	p->seconds   = bcd2dec(data[0] & 0x7F);   // p-> 로 변경
	p->minutes   = bcd2dec(data[1] & 0x7F);
	p->hour      = bcd2dec(data[2] & 0x3F);
	p->date      = bcd2dec(data[3] & 0x3F);
	p->month     = bcd2dec(data[4] & 0x1F);
	p->dayofweek = bcd2dec(data[5] & 0x07);
	p->year      = bcd2dec(data[6]);
}