///*
//* ds1307.c
//*
//* Created: 2026-07-01 오전 10:29:16
//*  Author: kccistc
//*/
//
//#include "ds1307.h"
//#include "i2c.h"
//
//////초기화 함수
////void clock_ds1307(void);
////void init_ddr_ds1307(void);
////void init_gpio_ds1307(void);
//
////날짜 초기화 함수
//void reset_date_time(t_ds1307 *ds1307);
//void reset_ds1307(t_ds1307* ds1307);
//
////i2c함수
//extern void i2c_init(void);
//extern uint8_t i2c_start(void);
//extern uint8_t i2c_stop(void);
//extern uint8_t i2c_slave_addr_send(uint8_t addr_rw);
//extern uint8_t i2c_data_write(uint8_t data);
//extern uint8_t i2c_data_read_acksend(void);
//extern uint8_t i2c_data_read_nacksend(void);
//
////기능 함수
///*
//*	dec --> bcd
//*	예) 25
//*	00011001(10)	0010 0101(16)
//*/
//uint8_t dec2bcd(uint8_t data);
//uint8_t bcd2dec(uint8_t data);
//uint8_t write_ds1307(uint8_t addr, uint8_t data);
//uint8_t read_ds1307(uint8_t addr, uint8_t* rx_buff);
//void tx_ds1307(uint8_t data);
//void read_time_ds1307(t_ds1307* ds1307);
//void read_date_ds1307(t_ds1307* ds1307);
//void rx_ds1307(uint8_t* pdata8bits);
//
//
//
//int ds1307_main(void)
//{
	//
	//t_ds1307	ds1307;
	//
	//i2c_init();
	//reset_date_time(&ds1307);	//all low로 설정
	//reset_ds1307(&ds1307);
	//
	//while(1)
	//{
		////1. read time
		//read_time_ds1307(&ds1307);
		////2. read date
		//read_date_ds1307(&ds1307);
		////3. printf date & time
		//printf("y-m-d: %d-%d-%d\n", ds1307.year, ds1307.month, ds1307.date);
		//printf("time: %d-%d-%d\n", ds1307.hours, ds1307.minutes, ds1307.seconds);
		////4. delay_ms(1000);
		//_delay_ms(1000);
	//}
//}
//
//////초기화 함수
////void clock_ds1307(void)
////{
//////LOW --> HIGH --> LOW
////DS1307_CLK_PORT &= ~(1<<DS1307_CLK);
////DS1307_CLK_PORT |= 1<<DS1307_CLK;
////DS1307_CLK_PORT &= ~(1<<DS1307_CLK);
////}
////
////void init_ddr_ds1307(void)
////{
////DS1307_DDR &= ~(1 << DS1307_CLK | 1 << DS1307_DAT | 1 << DS1307_RST);
////DS1307_DDR |= 1 << DS1307_CLK | 1 << DS1307_DAT | 1 << DS1307_RST;	//출력모드로 설정
////}
////
////void init_gpio_ds1307(void)
////{
////DS1307_CLK_PORT &= ~(1 << DS1307_CLK | 1 << DS1307_DAT | 1 << DS1307_RST);
////_delay_ms(2);
////}
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
	//write_ds1307(DS1307_HOUR,ds1307->hours);
	//write_ds1307(DS1307_DAY,ds1307->dayofweek);
	//write_ds1307(DS1307_DATE,ds1307->date);
	//write_ds1307(DS1307_MONTH,ds1307->month);
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
//uint8_t write_ds1307(uint8_t addr, uint8_t data)
//{
	//uint8_t status;
	//
	//// -----------------------------------
	//// PHASE 1: Master --> Slave 전송
	////------------------------------------
	//// 1. start 전송
	//
	//status = i2c_start();
	//if (status)
	//{
		//printf("ERR: START FAILED !\n");
		//return status;
	//}
	//// 2. SLAVE_ADDR + W 전송
	//status = i2c_slave_addr_send((DS1307_ADDR << 1) | 0); //SLAVE_ADDR + W
	//if (status != TWSR_MT_SLA_ACK) {
		//printf("ERR: SLAVE_ADDR !\n");
		//i2c_stop();
		//return status;
	//}
	//
	//// 3. timer reg addr write
	//status = i2c_data_write((uint8_t)addr);
	//if (status != TWSR_MT_DATA_ACK)
	//{
		//printf("ERR: DATA WRITE + NACK \n");
		//i2c_stop();
		//return status;
	//}
	//
	//// 4. timer reg data write
	//status = i2c_data_write((uint8_t)data);
	//if (status != TWSR_MT_DATA_ACK)
	//{
		//printf("ERR: DATA WRITE + NACK \n");
		//i2c_stop();
		//return status;
	//}
	//
	//// 4. STOP signal
	//i2c_stop();
	//
	//return status;
//}
//
//
//void read_time_ds1307(t_ds1307* ds1307)
//{
	//read_ds1307(DS1307_SEC, &ds1307->seconds);
	//read_ds1307(DS1307_MIN, &ds1307->minutes);
	//read_ds1307(DS1307_HOUR, &ds1307->hours);
//}
//
//void read_date_ds1307(t_ds1307* ds1307)
//{
	//read_ds1307(DS1307_DAY, &ds1307->dayofweek);
	//read_ds1307(DS1307_DATE, &ds1307->date);
	//read_ds1307(DS1307_MONTH, &ds1307->month);
	//read_ds1307(DS1307_YEAR, &ds1307->year);
//}
//
//uint8_t read_ds1307(uint8_t addr, uint8_t* rx_buff)
//{
	//uint8_t status;
	//// 1. start
	//status = i2c_start();
	//if (status)
	//{
		//printf("ERR: START(read) FAILED");
		//i2c_stop();
		//
		//return status;;
	//}
	//
	//// 2. SLAVE_ADDR + W 전송
	//status = i2c_slave_addr_send(DS1307_ADDR << 1 | 0);	// SLAVE_ADDR + W
	//if (status != TWSR_MT_SLA_ACK)
	//{
		//printf("ERR: slave_addr(read) + nack !!! \n");
		//printf("TWSR = 0x%02X\n", TWSR & 0xF8);
		//printf("status = 0x%02X\n", status);
		//i2c_stop();
		//
		//return status;
	//}
	//
	//// 3. timer reg addr read point
	//status = i2c_data_write((uint8_t)addr);
	//if (status != TWSR_MT_DATA_ACK)
	//{
		//printf("ERR: DATA WRITE + NACK \n");
		//i2c_stop();
		//return status;
	//}
	//
	////4.repeated start
	//status = i2c_start();
	//if (status)
	//{
		//printf("ERR: Repeated FAILED");
		//i2c_stop();
		//
		//return status;
	//}
	//
	////5.SLAVE_ADDR + R 전송
	//status = i2c_slave_addr_send(DS1307_ADDR << 1 | 1);	// 0xC1: SLAVE_ADDR + R
	//if (status != TWSR_MR_SLA_ACK)
	//{
		//printf("ERR: slave_addr(read) + nack !!! \n");
		//i2c_stop();
		//
		//return status;
	//}
	//
	//// 6. 3byte 수신 A, B, C
	//*rx_buff = i2c_data_read_nacksend();	// 'C' 수신 + NACK 전송(이제 그만 보내라)
	//
	//// 7. i2c stop
	//i2c_stop();
	//
	//return status;
//}
//
