/*
 * i2c.h
 *
 * Created: 2026-07-01 오후 5:36:28
 *  Author: kccistc
 */ 


#ifndef I2C_H_
#define I2C_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h> //sei 등의 함수
#include <stdio.h>

//I2C 설정
#define	I2C_FREQUENCY 100000UL	// 100KHz

// TWBR : I2C 통신 bit rate 설정 (Two Wire Bit Rate)
// TWBR = (F_CPU / I2C_FREQUENCY - 16) / 2 (분주비 = 1)
#define TWBR_VALUE (F_CPU / I2C_FREQUENCY - 16)	// TWBR(TWI bit rate register)
//------------TWI 상태코드 ------------------
// TWSR(TWI Status Register) : 7번 ~ 3번 bit(5bit를 참조) - I2C 통신의 전송 상태나 오류를 나타낸다
#define TWSR_START 0x08			// START 조건 전송 완료
#define TWSR_REP_START 0x10   // TWSR_REP_START (0x10) - Repeated START
#define TWSR_MT_SLA_ACK 0x18	// MT: master transmitter Master가 slave addr + w 전송 후 ack 수신
#define TWSR_MT_DATA_ACK 0x28	// Master가 SLAVE DATA 전송 후 ACK 수신
#define TWSR_MR_SLA_ACK 0x40	// Master가 SLAVE ADDR + R 전송 후 ACK 수신
#define TWSR_MR_DATA_ACK 0x50	// Master가 DATA 수신 뒤 + ACK 전송
#define TWSR_MR_DATA_NACK 0x58  // Master가 DATA 수신 뒤 + NACK 전송


#endif /* I2C_H_ */