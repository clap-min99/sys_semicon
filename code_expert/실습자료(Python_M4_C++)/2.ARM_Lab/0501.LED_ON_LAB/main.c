// 여기에 사용자 임의의 define을 작성하시오
#define GPIOA_MODER		(*(unsigned int *)0x40020000)	
#define GPIOA_OTYPER	(*(unsigned int *)0x40020004)	
#define GPIOA_ODR		(*(unsigned int *)0x40020014)	

void Main(void)
{
	// LED GPA[7]를 출력(General Push Pull) 모드로 설정하시오
	// 회로를 반드시 active low로 설계
	// 왜 open drain으로 설계해야하는가

	GPIOA_MODER = 0x00004000;
	GPIOA_OTYPER = 0x00000080;

	// GPA[7] LED를 ON 시키도록 설정하시오

	GPIOA_ODR = 0x00000000;
}




#if 0
#define GPIOA_MODER		(*(unsigned int *)0x40020000)	
#define GPIOA_OTYPER	(*(unsigned int *)0x40020004)	
#define GPIOA_ODR		(*(unsigned int *)0x40020014)	

void Main(void)
{
	// LED GPA[5]를 출력(General Push Pull) 모드로 설정하시오

	GPIOA_MODER = 0x00000400;
	GPIOA_OTYPER = 0x0;

	// GPA[5] LED를 ON 시키도록 설정하시오

	GPIOA_ODR = 0x00000020;
}
#endif