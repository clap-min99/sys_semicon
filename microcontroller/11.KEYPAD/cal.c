/*
 * cal.c
 *
 * Created: 2026-06-29 오후 4:08:20
 *  Author: kccistc
 */ 
#include "cal.h"
#include "keypad.h"

void cal_main(void);
void cal_input(t_cal *c, uint8_t key);
void cal_reset(t_cal *c);
int32_t cal_evaluate(char *expr);   // Shunting-yard 계산

extern void init_keypad();
extern uint8_t keypad_scan(void);

static uint8_t precedence(char op)
{
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}

// 계산 수행
static int32_t apply_op(int32_t a, int32_t b, char op)
{
	switch (op)
	{
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/':
		if (b == 0) { printf("ERR: div by zero\n"); return 0; }
		return a / b;
	}
	return 0;
}


int32_t cal_evaluate(char *expr)
{
	int32_t num_stack[STACK_SIZE];   // 숫자 스택
	char    op_stack[STACK_SIZE];    // 연산자 스택
	int8_t  num_top = -1;
	int8_t  op_top  = -1;

	int8_t i = 0;

	while (expr[i] != '\0')
	{
		// 1. 숫자면 파싱해서 num_stack에 push
		if (expr[i] >= '0' && expr[i] <= '9')
		{
			int32_t num = 0;
			while (expr[i] >= '0' && expr[i] <= '9')
			{
				num = num * 10 + (expr[i] - '0');
				i++;
			}
			num_stack[++num_top] = num;
			continue;
		}

		// 2. '(' 이면 op_stack에 push
		if (expr[i] == '(')
		{
			op_stack[++op_top] = expr[i];
			i++;
			continue;
		}

		// 3. ')' 이면 '(' 나올 때까지 계산
		if (expr[i] == ')')
		{
			while (op_top >= 0 && op_stack[op_top] != '(')
			{
				int32_t b = num_stack[num_top--];
				int32_t a = num_stack[num_top--];
				char    op = op_stack[op_top--];
				num_stack[++num_top] = apply_op(a, b, op);
			}
			op_top--;   // '(' 제거
			i++;
			continue;
		}

		// 4. 연산자면 우선순위 비교 후 처리
		if (expr[i]=='+' || expr[i]=='-' || expr[i]=='*' || expr[i]=='/')
		{
			while (op_top >= 0 && op_stack[op_top] != '(' &&
			precedence(op_stack[op_top]) >= precedence(expr[i]))
			{
				int32_t b  = num_stack[num_top--];
				int32_t a  = num_stack[num_top--];
				char    op = op_stack[op_top--];
				num_stack[++num_top] = apply_op(a, b, op);
			}
			op_stack[++op_top] = expr[i];
			i++;
			continue;
		}

		i++;   // 모르는 문자 스킵
	}

	// 5. 남은 연산자 전부 처리
	while (op_top >= 0)
	{
		int32_t b  = num_stack[num_top--];
		int32_t a  = num_stack[num_top--];
		char    op = op_stack[op_top--];
		num_stack[++num_top] = apply_op(a, b, op);
	}

	return num_stack[num_top];
}

void cal_reset(t_cal *c)
{
	memset(c->buf, 0, BUF_SIZE);
	c->idx = 0;
	printf("CLEAR\n");
}

void cal_input(t_cal *c, uint8_t key)
{
	// Clear
	if (key == 'C')
	{
		cal_reset(c);
		return;
	}

	// '=' 누르면 계산
	if (key == '=')
	{
		if (c->idx == 0)
		{
			printf("error: empty\n");
			return;
		}
		printf("%s=", c->buf);
		int32_t result = cal_evaluate(c->buf);
		printf("%ld\n", result);
		cal_reset(c);
		return;
	}

	// 버퍼에 추가
	if (c->idx < BUF_SIZE - 1)
	{
		c->buf[c->idx++] = key;
		c->buf[c->idx]   = '\0';
		printf("%s\n", c->buf);   // 현재 입력 상태 출력
	}
	else
	{
		printf("error: buf full\n");
	}
}