/*
 * i2c_s_loopback.c
 *
 * Created: 2026-06-30 오후 2:29:33
 *  Author: kccistc
 */ 

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
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>   // sei, ISR 등

//I2C 설정
#define SLAVE_ADDR 0x50		// 7bit slave 주소

//------------TWI 상태코드(SLAVE) ------------------
// TWSR(TWI Status Register) : 7번 ~ 3번 bit(5bit를 참조) - I2C 통신의 전송 상태나 오류를 나타낸다
// 아래의 코드를 수신하면 ISR(TWI_vect) 상태로 분기된다.
#define TWSR_SR_SLA_ACK 0x60	// Slave receive : slave address + W 수신, ACK 전송
#define TWSR_SR_DATA_ACK 0x80	// Slave receive : slave data 수신, ACK 전송
#define TWSR_SR_STOP 0xA0		// STOP 감지

#define TWSR_ST_SLA_ACK 0xA8	// Slave가 전송: slave address + R 수신, ACK 전송
#define TWSR_ST_DATA_ACK 0xB8	// 데이터 전송 + ACK 수신
#define TWSR_ST_DATA_NACK 0xC0	// 데이터 전송 + NACK 수신
#define TWSR_ST_LAST_DATA 0xC8	// 마지막 데이터 전송 + ACK 수신

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


int i2c_slave_main(void);
void init_slave_i2c(void);

#define RX_SIZE 8
volatile uint8_t i2c_rx_buff[8];	// volatile : compiler 최적화 방지
volatile int rx_len;			// 수신된 바이트 수 
volatile int tx_index;			// 송신 index
volatile uint8_t last_state = 0;   // 디버깅용: 마지막 상태코드 저장
volatile uint8_t isr_count = 0;    // 디버깅용: ISR 호출 횟수

//-----------------------------------
// TWI interrupt 서비스 루틴	
// ----------------------------------
ISR(TWI_vect)
{
	uint8_t st= TWSR & 0xf8;	// 7~3bit 값을 취한다
	last_state = st;     // 마지막 상태 기록
	isr_count++;         // 호출 횟수 증가
	
	switch(st)
	{
		// <------- slave 수신 단계 -------->
		case TWSR_SR_SLA_ACK:	// Slave receive : slave address + W 수신, ACK 전송
			rx_len = 0;
			TWCR = 1 << TWINT | 1<< TWEA | 1 << TWEN | 1 << TWIE;	// ACK 자동전송
			break;
		
		case TWSR_SR_DATA_ACK:
			if (rx_len < RX_SIZE)
			{
				i2c_rx_buff[rx_len++] = TWDR;
			}
			TWCR = 1 << TWINT | 1<< TWEA | 1 << TWEN | 1 << TWIE;	// ACK 자동전송
			break;
		
		case TWSR_SR_STOP:
			tx_index = 0;
			TWCR = 1 << TWINT | 1<< TWEA | 1 << TWEN | 1 << TWIE;	// 읽기 모드 대기
			break;
		
		// <--------- slave 전송 단계 --------?
		case TWSR_ST_SLA_ACK:
			tx_index = 0;			// 첫번째 byte 수신 준비
		
		case TWSR_ST_DATA_ACK:
			if (tx_index < rx_len)
			{
				TWDR = i2c_rx_buff[tx_index++];
			}
			else
			{
				TWDR = 0xff;		// 버퍼 이상 발생: dummy	
			}
			// 마지막 바이트이면 TWEA=0으로 NACK 준비 (더이상 보낼게 없다)
			if (tx_index >= rx_len)
			{
				TWCR = 1 << TWINT | 1 << TWEN | 1 << TWIE;				
				// 더 이상 보낼 데이터가 없음을 표시 (TWEA=0)
			}
			else
			{
				TWCR = 1 << TWINT | 1<< TWEA | 1 << TWEN | 1 << TWIE;	// ACK 준비
			}
			break;
		
		case TWSR_ST_DATA_NACK:		// NACK 받으면 송신 종료
		
		case TWSR_ST_LAST_DATA:		
			tx_index = 0;
			TWCR = 1 << TWINT | 1<< TWEA | 1 << TWEN | 1 << TWIE;
			break;
		
		default:	// error 복구 TWINT clear, ACK 재활성화
			TWCR = 1 << TWINT | 1<< TWEA | 1 << TWEN | 1 << TWIE;
			break;
	}
}

// TWI(I2C) driver
void init_slave_i2c(void)
{
	TWAR = SLAVE_ADDR << 1;
	TWCR = 1 << TWEA | 1 << TWEN | 1 << TWIE;	// ACK 활성화 , interrupt 활성화
}


int i2c_slave_main(void)
{
	init_slave_i2c();
	sei();
	
	while (1)
	{
		printf("isr_count=%u, last_state=0x%02X\n", isr_count, last_state);
		// _delay_ms(1000);
	}
}