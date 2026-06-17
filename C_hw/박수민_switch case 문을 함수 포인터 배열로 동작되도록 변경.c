

// switch ~ case 문을 함수 포인터 배열로 동작되도록 변경
#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //malloc, atoi ...
#define NAME_LEN 20
#define NUMBER 10

// 정적메모리를 동적 메모리로 변경
// t_account acc_arr[100] // account 저장을 위한 배열
// 을 동적메모리로 할당
typedef struct
{
	int acc_id;
	int balance;
	char cus_name[NAME_LEN];
} t_account;

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT = 9 };

void show_menu(void);
void make_account(t_account* pa, int* pn);
void deposit_money(t_account* pa, int* pn);
void with_draw_money(t_account* pa, int* pn);
void show_all_acc_info(t_account* pa, int* pn);



void (*fp[])(t_account*, int*) =
{
	NULL,
	make_account,	
	deposit_money,
	with_draw_money,
	show_all_acc_info
};



int main()
{
	int choice;
	//t_account* acc_arr[100];
	t_account* acc_arr;
	int acc_num = 0;


	acc_arr = (t_account*)malloc(sizeof(t_account) * NUMBER);
	if (acc_arr == 0) {
		fprintf(stderr, "malloc failed!!\n");
		return -1; // return 0인 경우 error 없이 정상적으로 종료됨을 의미. return -1은 에러가 발생했다는 의미
	}

	while (1)
	{
		show_menu();
		printf("선택: ");
		scanf("%d", &choice);
		printf("\n");


		if (choice == 9) {          // 9번: 종료
			printf("프로그램을 종료합니다.");
			free(acc_arr);
			return 0;
		}
		if (fp[choice] == NULL) {
			printf("유효하지 않은 선택입니다.\n\n");
			continue;
		}
		fp[choice](acc_arr, &acc_num);
	

	}
	return 0;
}

void show_menu(void)
{
	char* menu[] =
	{
		"-----Menu------\n",
		"1. 계좌개설\n",
		"2. 입    금\n",
		"3. 출    금\n",
		"4. 계좌정보 전체 출력\n",
		"9. 종    료\n"
	};

	for (int i = 0; i < 6; i++)
		printf("%s", *(menu + i));
}

void make_account(t_account* pa, int* pn)
{
	int id;
	char name[NAME_LEN];
	int balance;

	printf("[계좌개설]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("이  름: ");
	scanf(" %s", name);
	printf("입금액: ");
	scanf(" %d", &balance);
	printf("\n");

	// pa + *pn 으로 n번째 계좌 포인터 접근
	t_account* pt = pa + *pn;
	pt->acc_id = id;
	pt->balance = balance;
	strcpy(pt->cus_name, name);

	(*pn)++;
}

void deposit_money(t_account* pa, int* pn)
{
	int money, id;
	t_account* pt = pa;   // 포인터 복사

	printf("[입    금]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("입금액: ");
	scanf("%d", &money);

	for (int i = 0; i < *pn; i++)
	{
		if (pt->acc_id == id)   // pt->  로 접근
		{
			pt->balance += money;
			printf("입금완료\n\n");
			return;
		}
		pt++;   // 다음 계좌로 이동
	}
	printf("유효하지 않은 ID 입니다.\n\n");
}

void with_draw_money(t_account* pa, int* pn)
{
	int money, id;
	t_account* pt = pa;   // 포인터 복사

	printf("[출    금]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("출금액: ");
	scanf("%d", &money);

	for (int i = 0; i < *pn; i++)
	{
		if (pt->acc_id == id)   // pt->  로 접근
		{
			if (pt->balance < money)
			{
				printf("잔액부족\n\n");
				return;
			}
			pt->balance -= money;
			printf("출금완료\n\n");
			return;
		}
		pt++;   // 다음 계좌로 이동
	}
	printf("유효하지 않은 ID 입니다.\n\n");
}

void show_all_acc_info(t_account* pa, int* pn)
{
	t_account* pt = pa;   // 포인터 복사

	printf("ID   잔액     이름\n");
	printf("==== ======== ====================\n");

	for (int i = 0; i < *pn; i++)
	{
		printf("%-4d %-8d %s\n", pt->acc_id, pt->balance, pt->cus_name);
		pt++;   // 다음 계좌로 이동
	}

	printf("==== ======== ====================\n");
}
#endif