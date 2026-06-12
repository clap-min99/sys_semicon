# CH1. 마이크로컨트롤러

### 마이크로컨트롤러란?

1. 마이크로컨트롤러(MCU)

    
    - 개념

        All in one

        마이크로프로세서 + 메모리 + 입출력 인터페이스

        컴퓨터의 **메인보드와 하드디스크 기능을 하나의 IC칩으로 집적** 시켜 만든 반도체 소자

    - 구조
        
        CPU + RAM + ROM + I/O 가 하나의 chip에 총합
        8051, AVR(ATmega 128A), ARM(CORTEXM4)

    - 목적

        특정기능 제어
    
    - OS

        non-OS(OS 없이 동작), RTOS

    - power(전기) 소모

        초절전모드
    
    - cost size

        one-chip, cost 적고, 사이즈 작다.

    - 응용 예

        세탁기, 냉장고, 자동차


2. 마이크로프로세서(CPU)

    - 개념 
        
        CPU

    - 구조

        CPU 핵심기능(RAM, ROM, I/O 연결 경로)
        i7, i9

    - 목적

        대용량 데이터 고속 연산처리

    - OS
    
        linux, winAr?? 필수탑재

    - power(전기) 소모

        소모량 많음
    
    - cost size

        I/O 많음 -> 회로 복잡

    - 응용 예

        PC, 서버, AI,...

    
---

### 마이크로컨트롤러, 데톱 비교

1. 마이크로컨트롤러

    - CPU: ATmega128

    - bit: 8bit

        8bits -> 데이터버스의 폭 

        CPU와 I/O 메모리 사이에 데이터를 주고받는 선이 8개

        Address 버스: 데이터버스의 크기?

    - 메모리 128KB

        플래시 메모리를 의미

    - 클록 16MHz


2. 데스크탑 컴퓨터

    - CPU: intel Core i7

    - bit: 64bit

    - 메모리 8GB

    - 클록 3.4GHz(Quad Core)

---