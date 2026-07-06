/*
 * i2c_m_loopback.c
 *
 * Created: 2026-06-30 오전 10:52:20
 *  Author: kccistc */

/*
	"ABC" 문자열을 slave로 전송하고 slave가 돌려보낸 문자열을 수신하여 
	UART로 출력하는 loop-back test program을 작성
	
	Atmega128A 2개를 연결한다.
	1개는 master, 1개는 slave로 동작하도록 한다	
	
	H/W 조건
	============
	1. I2C연결
	PD0 (SCL) -- 10K(pullup 저항) --- VCC (pull up 저항은 master에만 연결)
	PD1 (SDA) -- 10K(pullup 저항) --- VCC 
	두 atmega의 GND라인은 공통으로 연결. VCC끼리는 연결안해도 됨	
	
	I2C ADDR: 0x60
	
	2. 속도
	F_CPU: 16MHz I2C 속도: 100KHz UART: 9600bps
	
	3. Handshking
	ACK/ NACK 의미
	
	신호		SDA(데이터라인)		Slave 입장에서의 의미
	================================================
	ACK		LOW					다음 바이트도 계속 보냄. 정상적으로 수신
	NACK	HIGH				이제 그만 보내도 됨. 전송 끝남
		
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>   // sei, ISR 등
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

//I2C 설정
#define SLAVE_ADDR 0x50		// 7bit slave 주소
#define	I2C_FREQUENCY 100000UL	// 100KHz

// TWBR : I2C 통신 bit rate 설정 (Two Wire Bit Rate)
// TWBR = (F_CPU / I2C_FREQUENCY - 16) / 2 (분주비 = 1)
#define TWBR_VALUE ((F_CPU / I2C_FREQUENCY - 16) / 2)	// TWBR(TWI bit rate register)


//------------TWI 상태코드 ------------------
// TWSR(TWI Status Register) : 7번 ~ 3번 bit(5bit를 참조) - I2C 통신의 전송 상태나 오류를 나타낸다
#define TWSR_START 0x08			// START 조건 전송 완료 
#define TWSR_REP_START 0x10   // TWSR_REP_START (0x10) - Repeated START
#define TWSR_MT_SLA_ACK 0x18	// MT: master transmitter Master가 slave addr + w 전송 후 ack 수신
#define TWSR_MT_DATA_ACK 0x28	// Master가 SLAVE DATA 전송 후 ACK 수신
#define TWSR_MR_SLA_ACK 0x40	// Master가 SLAVE ADDR + R 전송 후 ACK 수신 
#define TWSR_MR_DATA_ACK 0x50	// Master가 DATA 수신 뒤 + ACK 전송
#define TWSR_MR_DATA_NACK 0x58  // Master가 DATA 수신 뒤 + NACK 전송

/*
Atmega128A TWI(I2C) 관련  register
TWCR: TWI Control Register
	- 각 bit의 역할 -
	TWINT: 인터럽트 플래그 (1이면 clear: 일반 flag와 다름) I2C 작업이 끝나면 set
	TWEA: ACK enable (1: 자동으로 ACK 가 전송 , 0: NACK 전송)
	TWSTA: START 신호 발생 (MASTER 전용, slave는 사용 안함)
	TWSTO: STOP 신호 발생 (MASTER 전용, slave는 사용 안함)
	TWEN: TWT(I2C) Enable (I2C 하드웨어를 활성화)
	TWIE: Interrupt Enable (IWI(I2C) interrupt를 활성화)
TWSR: TWI Status Register (상위 5bit == 상태코드, 하위 2bit: Prescaler)
TWBR: TWI BIT Rate Register
TWDR: TWI Data Register
TWAR: TWI Address Register (Slave 모드에서 사용: 나의 address를 설정)

*/


int i2c_main(void);
void init_i2c(void);
void loopback_test(void);
uint8_t i2c_data_read_acksend(void);
uint8_t i2c_data_read_nacksend(void);

void i2c_stop(void);
uint8_t i2c_start(void);
uint8_t i2c_slave_addr_send(uint8_t addr_rw);
uint8_t i2c_data_write(uint8_t data);

// TWI(I2C) driver
void init_i2c(void)
{
	DDRD |= 1 << 0 | 1 << 1;
	
	TWSR = 0x00;
	TWBR = TWBR_VALUE;	// SCL 주파수 결정 register 100KHz
}

uint8_t i2c_start(void)
{
	uint8_t st;
	
	TWCR =  1 << TWINT | 1 << TWSTA | 1 << TWEN; 
	// TWINT			TWSTA: START 요청 , TWEN: I2C HW 활성화
	// I2C HW가 동작이 완료될때까지 기다린다. 동작이 완료되면 TWINT flag를 1로 세트
	while (!(TWCR & (1<< TWINT)));
	
	st = TWSR & 0xf8;		// 7~3 bit 까지 값을 취함
	return (st == TWSR_START || st == TWSR_REP_START ) ? 0 : st;		// 성공이면 0, 아니면 error 상태 코드 반환
		
	
}

void i2c_stop(void)
{

	TWCR =  1 << TWINT | 1 << TWSTO | 1 << TWEN;
	// TWINT			TWSTA: STOP 요청 , TWEN: I2C HW 활성화
	// I2C HW가 동작이 완료될때까지 기다린다. 동작이 완료되면 TWINT flag를 1로 세트
	// STOP 후 TWINT clear 되기까지 대기
	_delay_us(10);
	
}

//SLAVE_ADDR+R SLAVE_ADDR+W
uint8_t i2c_slave_addr_send(uint8_t addr_rw)
{
	uint8_t st;
	
	TWDR = addr_rw;
	TWCR =  1 << TWINT | 1 << TWEN;
	// TWINT			 TWEN: I2C HW 활성화
	// I2C HW가 동작이 완료될때까지 기다린다. 동작이 완료되면 TWINT flag를 1로 세트
	while (!(TWCR & (1<< TWINT)));
	
	st = TWSR & 0xf8;		// 7~3 bit 까지 값을 취함
	
	return st;	
}

uint8_t i2c_data_write(uint8_t data)
{
	
	TWDR = data;	
	TWCR =  1 << TWINT | 1 << TWEN;
	// TWINT			 TWEN: I2C HW 활성화
	// I2C HW가 동작이 완료될때까지 기다린다. 동작이 완료되면 TWINT flag를 1로 세트
	while (!(TWCR & (1<< TWINT)));
	
	return (TWSR & 0xf8);		// 7~3 bit 까지 값을 취함
}

uint8_t i2c_data_read_acksend(void)
{
	
	TWCR = 1 << TWINT | 1 << TWEN | 1 << TWEA ;		// TWEA = 1: ACK 자동 전송
	// TWINT			 TWEN: I2C HW 활성화
	// I2C HW가 동작이 완료될때까지 기다린다. 동작이 완료되면 TWINT flag를 1로 세트
	while (!(TWCR & (1<< TWINT)));
	
	return TWDR;		// 7~3 bit 까지 값을 취함
}

uint8_t i2c_data_read_nacksend(void)
{
	
	TWCR = 1 << TWINT | 1 << TWEN ;		// TWEA = 0: NACK 자동 전송
	
	while (!(TWCR & (1<< TWINT)));
	
	return TWDR;		// 7~3 bit 까지 값을 취함
}

void loopback_test(void)
{
	char tx_msg[] = "ABC";
	char i2c_rx_buff[4] = {0};
	uint8_t status;		
	
	// -----------------------------------
	// PHASE 1: Master --> Slave 전송
	//------------------------------------
	// 1. start 전송
	
	status = i2c_start();
	if (status)
	{
		printf("ERR: START FAILED !\n");
		return;
	}
	
	// 2. SLAVE_ADDR + W 전송
	status = i2c_slave_addr_send((SLAVE_ADDR << 1) | 0); // 0xC0: SLAVE_ADDR + W
	if (status != TWSR_MT_SLA_ACK) {
		printf("ERR: SLAVE_ADDR !\n");
		i2c_stop();
		return;
	}
	
	// 3. DATA 3 byte write 
	for (int i = 0; tx_msg[i] != '\0'; i++)
	{
		status = i2c_data_write((uint8_t) tx_msg[i]);

		if (status != TWSR_MT_DATA_ACK)
		{
			printf("ERR: DATA WRITE + NACK \n");
			i2c_stop();
			return;
		}

	}
	
	// 4. STOP signal 
	i2c_stop();
	
	// START 0xc0 ACK 'A' ACK 'B' ACK 'C' ACK STOP
	
	// 5. 대기 _delay_ms(5)
	_delay_ms(5);
	
	
	// -----------------------------------
	// PHASE 2: Slave --> Master
	//------------------------------------
	
	// 1. start
	status = i2c_start();
	if (status) 
	{
		printf("ERR: START(read) FAILED");
		i2c_stop();
		return;
	}
	
	// 2. SLAVE_ADDR + R 전송
	status = i2c_slave_addr_send(SLAVE_ADDR << 1 | 1);	// 0xC1: SLAVE_ADDR + R
	if (status != TWSR_MT_SLA_ACK)
	{
		printf("ERR: slave_addr(read) + nack !!! \n");
		i2c_stop();
		return;
	}
	
	// 3. 3byte 수신 A, B, C
	i2c_rx_buff[0] = i2c_data_read_acksend();	// 'A' 수신 + ACK 전송('B'도 보내라)
	i2c_rx_buff[1] = i2c_data_read_acksend();	// 'B' 수신 + ACK 전송('C'도 보내라)
	i2c_rx_buff[2] = i2c_data_read_nacksend();	// 'C' 수신 + NACK 전송(이제 그만 보내라)
	
	// 4. i2c stop
	i2c_stop();
	
	// 결과 출력
	printf("TX: %s, RX: %s\n",tx_msg, i2c_rx_buff);
	if (strncmp(tx_msg, i2c_rx_buff, 3) == 0)
	{
		printf("loop back ok!\n");
	}
	else printf("loop back not ok\n");
}

// ------------------------------------
// loop back test: "ABC" 전송 --> 수신
// ------------------------------------

int i2c_main(void)
{
	init_i2c();
	printf("I2C loopback test start\n");
	
	while (1)
	{
		loopback_test();
		_delay_ms(1000);
		
	}
}