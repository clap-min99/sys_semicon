# 혼자 공부하는 C언어

## C언어 시작하기

### 1. 프로그램과 C언어

- C언어 특징
    - 유닉스(리눅스) 개발하기 위해 만든 언어
        
        왜 리눅스 개발환경? → 오픈소스, 빠름 
        
        기본적으로 리눅스 사용
        
    - 시스템 프로그래밍 가능
    - 이식성(portability)을 갖춘 프로그램 개발 가능
        
        → porting(포팅) 코드 옮겨심는 작업
        
    - 함수 사용해서 개별 프로그래밍 가능

- 컴파일 과정
    
    소스파일 — 전처리(#include, #define) —> 전처리된 소스파일 — 컴파일 —> 개체 파일  — 링크( + startup code)  —> 실행파일


- C언어 기초

    ```C    
    #include <stdio.h>
    // printf scanf gets fgets 등의 함수가 포함됨
    // 표준 입력 stdin(0): keyboard
    // 표준 출력 stdout(1): 화면, normal stderr(2) : 화면에 에러를 출력하는 경우
    
    int main(void) // main: 프로그램의 시작을 의미
    
    {
        printf("Hello! World!\n"); // printf: 화면에 출력하는 함수, \n: 줄바꿈(newline)
    }
    ```

### 2. 변수와 데이터

- 변수
    ```C
    #if 1
    #include <stdio.h>
    int main(void)
    {
        // 변수(variable): data(자료)를 저장하는 메모리(ram) 공간
        // 상수: 자료값이 고정되어 있는것(ram, rom)
        char c; // c라는 이름으로 1byte(8bits)를 저장하는 메모리 공간
        // 상위 4bits(high nibble), 하위 4bits(low nibble)
        // -128 ~ 127

        unsigned char uc = 0xff; // unsigned: 부호 없는, 0~255까지 저장 가능, 0x: 16진수 표기법, 0xff: 16진수로 255를 의미
        unsigned char ub = 0b11111111; // 0b: 2진수 표기법, 0b11111111: 2진수로 255를 의미
        short s; // 2byte(16bits), -32768 ~ 32767
        unsigned short us; // 0 ~ 65535
        int i;
        long j;
        long long a;
        
        /* 암기!
        1byte: 256
        2byte: 65536
        
        */
        
        uc = 0xff; // 255
        printf("hex uc==> %d\n", uc); 
        uc = 0b11111111; 
        printf("bin uc==> %d\n", uc);
        uc = 255;
        printf("dec uc==> %d\n", uc);

        uc++; // uc = uc + 1; uc += 1; uc++: 후위 연산자, ++uc: 전위 연산자
        printf("uc++ ==> %d\n", uc); // 0이 됨, 오버플로우(overflow): 최대값을 초과하여 최소값으로 돌아감
        printf("uc++ ==> %0x\n", uc);
        printf("uc++ ==> %0o\n", uc);

        //printf("uc++ ==> %0b\n", uc);
        
        s = -1;
        printf("s ==> %d\n", s); // -1
        printf("s ==> %hu\n", s); // 65535 unsigned로 해석하면 65535가 됨
        printf("s ==> %u\n", s); // 65535가 될 것 같지만? 4294967295가 출력됨.
        //s는 short인데 %u는 unsigned int로 해석되어서 4294967295. 즉 정수 승격이 일어남 

        us = 0xffff; // 65535;
        printf("us ==> %d\n", us); // 65535
        printf("us ==> %0x\n", us); // 0xffff

        us++;
        printf("us++ ==> %d\n", us); // 0
        printf("us++ ==> %0x\n", us); // 0

        //sizeof 연산자: 자료형의 크기를 바이트 단위로 반환하는 연산자
        printf("char: %d\n", (int) sizeof(char)); // 1
        printf("unsigned char : %d\n", (int)sizeof(unsigned char)); // 1
        
        printf("short: %d\n", (int) sizeof(short)); // 2
        printf("unsigned short: %d\n", (int)sizeof(unsigned short)); // 2
        
        printf("int: %d\n", (int) sizeof(int)); // 4
        printf("unsigned int: %d\n", (int)sizeof(unsigned int)); // 4
        
        printf("a : %d\n", (int)sizeof(a)); // 8, sizeof는 자료형의 크기를 반환하기 때문에 변수 a의 자료형인 long long의 크기를 반환함

            
        printf("long: %d\n", (int) sizeof(long)); // 8

        return 0;
    }
    ```

- 배열 크기
    
    ```c
    #include <stdio.h>

    int main(void) {
        char c[10] = "abcd"; // 배열의 크기는 2의 배수로 하는 것이 좋음(컴파일러가 메모리를 효율적으로 관리할 수 있도록)
        unsigned char uc[20] = "abcde";
        
        short s[40]; // 80byte(80/8), 2byte(16bits) * 40 = 80byte
        unsigned short us[30]; // 60byte(60/8), 2byte(16bits) * 30 = 60byte

        int i[10]; // 40byte(40/8), 4byte(32bits) * 10 = 40byte
        int j[20]; // 80byte(80/8), 4byte(32bits) * 20 = 80byte

        printf("c ==> %d\n", (int)sizeof(c)); // 10, 배열의 크기를 반환
        printf("uc ==> %d\n", (int)sizeof(uc)); // 20, 배열의 크기를 반환
        
        printf("s ==> %d\n", (int)sizeof(s)); // 80, 배열의 크기를 반환
        printf("us ==> %d\n", (int)sizeof(us)); // 60, 배열의 크기를 반환
        
        printf("i ==> %d\n", (int)sizeof(i)); // 40, 배열의 크기를 반환
        printf("j ==> %d\n", (int)sizeof(j)); // 80, 배열의 크기를 반환

    }
    ```


- 진법

    ```c
    int main() {
	int i = 10;

	printf("i ==> %d\n", i); // 10을 십진수로 출력
	printf("%d\n", 10);

	//10을 octal로 출력
	printf("octal i : %o\n", i); // 12, octal로 출력
	printf("10 octal: %o\n", 10); // octa 체계 에서는 10이 12로 표현됨 

	//10을 hexadecimal로 출력
	printf("hex i: %0x\n", i); // a, hexadecimal로 출력
	printf("10 hex: %0x\n", 10); 

	printf("%lf\n", 3.4); // 소숫점 이하 6자리까지 출력, 3.400000
	printf("%.2lf\n", 3.452); // 소숫점 이하 2자리까지 출력, 3.45
	printf("%.10lf\n", 3.4); // 소숫점 이하 10자리까지 출력, 3.4000000000

	printf("%lf %.1lf %.10lf\n", 3.4, 3.452, 3.444);
	
	char c;
	c = 'A'; // 문자 A의 아스키 코드값은 65
	// c = "A"; null이 들어갈 공간 확보가 안되므로 오류 발생
	c = 0x41; // 16진수로 65를 표현한 것, c = 0b01000001; ascii 코드값 65를 2진수로 표현한 것
	printf("c ==> %c\n", c); // A, 문자로 출력
	printf("c ==> %d\n", c); // 65, 아스키 코드값으로 출력




	return 0;

    }
    ```