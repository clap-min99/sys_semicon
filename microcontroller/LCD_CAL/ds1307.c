///*
 //* ds1307.c
 //*
 //* Created: 2026-07-01 오전 11:51:10
 //*  Author: kccistc
 //*/ 
//
//#include "ds1307.h"
//
//int ds1307_main(void)
//{
	//
//}
//
////초기화 함수
//void clock_ds1307(void)
//{
	////LOW --> HIGH --> LOW
	//DS1307_CLK_PORT &= ~(1<<DS1307_CLK);
	//DS1307_CLK_PORT |= 1<<DS1307_CLK;
	//DS1307_CLK_PORT &= ~(1<<DS1307_CLK);
//}
//
//void init_ddr_ds1307(void)
//{
	//DS1307_DDR &= ~(1 << DS1307_CLK | 1 << DS1307_DAT | 1 << DS1307_RST);
	//DS1307_DDR |= 1 << DS1307_CLK | 1 << DS1307_DAT | 1 << DS1307_RST;	//출력모드로 설정
//}
//
//void init_gpio_ds1307(void)
//{
	//DS1307_CLK_PORT &= ~(1 << DS1307_CLK | 1 << DS1307_DAT | 1 << DS1307_RST);
	//_delay_ms(2);
//}
//
//
//
////날짜 초기화 함수
//void reset_date_time(t_ds1307 *ds1307)
//{
	//ds1307->year = 26;
	//ds1307->month = 6;
	//ds1307->date = 26;
	//ds1307->dayofweek = 6; //fri
	//ds1307->hours = 15;
	//ds1307->minutes = 19;
	//ds1307->seconds = 00;
//}
//
//
//void reset_ds1307(t_ds1307* ds1307)
//{
	//write_ds1307(DS1307_SEC,ds1307->seconds);
	//write_ds1307(DS1307_MIN,ds1307->minutes);
	//write_ds1307(DS1307_HOURS,ds1307->hours);
	//write_ds1307(DS1307_DATE,ds1307->date);
	//write_ds1307(DS1307_MONTH,ds1307->month);
	//write_ds1307(DS1307_DAYOFWEEK,ds1307->dayofweek);
	//write_ds1307(DS1307_YEAR,ds1307->year);
//}
//
//
////기능 함수
///*
//*	dec --> bcd
//*	예) 25
//*	00011001(10)	0010 0101(16)
//*/
//uint8_t dec2bcd(uint8_t data)
//{
	//uint8_t high, low;
	//
	//high = (data/10) << 4;
	//low = data % 10;
	//
	//return(high+low);
//}
//
//uint8_t bcd2dec(uint8_t data)
//{
	//uint8_t high, low;
	//
	//high = (data >> 4) * 10;
	//low = data & 0x0f;;
	//
	//return(high+low);
//}
//
//void write_ds1307(uint8_t addr, uint8_t data)
//{
	////1. CE low --> high
	//DS1307_RST_PORT |= 1 <<DS1307_RST;
	////2. ADDR 전송
	//tx_ds1307(addr);
	////3. DATA 전송
	//tx_ds1307(dec2bcd(data));
	////4. CE high --> low
	//DS1307_RST_PORT &= ~(1<<DS1307_RST);
//}
//
//void tx_ds1307(uint8_t data)
//{
	////1 출력 mode로 설정
	//DS1307_DDR |= 1 << DS1307_DAT;// write mode
	////EX) 0x80
	////1000 000
	//for(int i = 0; i<8; i++)
	//{
		//if(data& (1<<i))
		//DS1307_DAT_PORT |= 1<<DS1307_DAT;//1
		//else
		//DS1307_DAT_PORT &= ~(1<<DS1307_DAT);//0
		//
		//clock_ds1307();
	//}
//}
//
//void read_time_ds1307(t_ds1307* ds1307)
//{
	//ds1307->seconds = read_ds1307(ADDR_SECONDS);
	//ds1307->minutes = read_ds1307(ADDR_MINUTES);
	//ds1307->hours = read_ds1307(ADDR_HOURS);
//}
//
//void read_date_ds1307(t_ds1307* ds1307)
//{
	//ds1307->date = read_ds1307(ADDR_DATE);
	//ds1307->month = read_ds1307(ADDR_MONTH);
	//ds1307->dayofweek = read_ds1307(ADDR_DAYOFWEEK);
	//ds1307->year = read_ds1307(ADDR_YEAR);
//}
//
//uint8_t read_ds1307(uint8_t addr)
//{
	//uint8_t data8bits=0;//1b씩 읽을 변수
	////1.CE high
	//DS1307_RST_PORT |= 1 << DS1307_RST;
	////2 addr 전송
	//tx_ds1307(addr+1);
	////3.data 읽기
	//rx_ds1307(&data8bits);
	////4.CE low
	//DS1307_RST_PORT &= ~(1 << DS1307_RST);
	////5.return(bcd to dec)
	//return bcd2dec(data8bits);
//}
//
//
//void rx_ds1307(uint8_t* pdata8bits)
//{
	//uint8_t temp = 0;
	////1.input mode
	//DS1307_DDR &= ~(1<<DS1307_DAT);
	////LSB부터 차례로
	//for(int i=0; i<8; i++)
	//{
		//if(DS1307_DAT_PIN & (1<<DS1307_DAT))
		//{
			//temp |= 1 << i; //1의 조건만 set
		//}
		////3. CLK high-->low
		//if(i != 7)
		//clock_ds1307();
	//}
	//
	//*pdata8bits = temp;
//}