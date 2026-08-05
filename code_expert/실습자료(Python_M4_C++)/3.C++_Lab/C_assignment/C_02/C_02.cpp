// 문제 1
#if 0
#include <iostream>
using namespace std;

class mart_calc
{
private:
	double tax = 0.01;

public:
	double total = 0;
	void buy(int price);
	void change_tax(double tax);
};

void mart_calc::buy(int price)
{
	total += price * (1 + tax);
}

void mart_calc::change_tax(double tax)
{
	// class의 private 변수 tax를 전달 받은 값으로 변경
	mart_calc::tax = tax;
	// this -> tax = tax;
}

int main(void)
{
	mart_calc calc1;
	mart_calc calc2;

	calc1.change_tax(0.02);

	calc1.buy(10);
	calc1.buy(20);
	cout << calc1.total << endl;

	calc2.buy(200);
	cout << calc2.total << endl;

	calc1.buy(50);
	cout << calc1.total << endl;

	return 0;
}
#endif

// 문제 2
#if 0
#include <iostream>
using namespace std;

class mart_calc
{
public:
	double total = 0;
	void buy(int price, double tax = 0.01);
};

// member function buy 설계
void mart_calc::buy(int price, double tax)
{
	total += price * (1 + tax);
}

int main(void)
{
	mart_calc calc1;
	mart_calc calc2;

	calc1.buy(10);
	calc1.buy(20, 0.1);
	cout << calc1.total << endl;

	calc2.buy(200, 0.1);
	cout << calc2.total << endl;

	calc1.buy(50);
	cout << calc1.total << endl;

	return 0;
}
#endif

// 문제 3
#if 0
#include <iostream>
using namespace std;

class test
{
public:
	int a = 10;

	test(int b)
	{
		a += b;
	}
};

int main(void)
{
	test x(20);

	// &x로 초기화를 하는 포인터 p 선언
	test *p = &x;
	// test *p(&x);

	cout << x.a << endl;

	// 포인터 p를 이용하여 instance x의 a값 인쇄
	cout << (*p).a << endl;
	// cout << p->a << endl;
	return 0;
}
#endif

// 문제 4
#if 0
#include <iostream>
using namespace std;

class test
{
public:
	int a = 10;

	test(int b)
	{
		a += b;
	}
};

int main(void)
{
	// test class의 instance 2개를 갖는 배열 y를 선언하고 
	// 두 instance의 초기화 값으로 10, 20이 전달 되도록 하라.
	test y[2] {test(10), test(20)}; 
	// test y[2] {10, 20};
	

	// 배열 y의 요소 instance 들의 멤버 데이터 a를 인쇄하는 코드를 작성하라.
	cout << y[0].a << endl;
	cout << y[1].a << endl;

	return 0;
}
#endif

// 문제 5
#if 0
#include <iostream>
using namespace std;

class test
{
public:
	int a = 10;

	test(int b)
	{
		a += b;
	}
};

struct st
{
	int m1;
	test m2;
};

int main(void)
{
	// st 구조체 template의 변수 z 선언
	// 구조체 z의 멤버 m1은 정수 10으로 초기화
	// 구조체 z의 멤버 m2 instance의 초기값으로 20 전달
	st z = {10, test(20)};
	

	
	// 구조체 z의 멤버 m1과 m2의 a 값 인쇄
	cout << z.m1 << endl;
	cout << z.m2.a << endl;
	
	return 0;
}
#endif

// 문제 6
#if 0
#include <iostream>
using namespace std;

// 코드 설계
class SALES
{
private:
    static int total_cnt;
    static int total_money;

    int sales_cnt;
    int sales_money;

public:
    SALES(int c, int m)
    {
        sales_cnt = c; 
        sales_money = m;
        total_cnt += c;
        total_money += m;

    }
    void sales_report(int c, int m)
    {
        sales_cnt += c;
        sales_money += m;
        total_cnt += c;
        total_money += m;
    }

    void print_report()
    {
        cout << total_cnt << endl;
        cout << total_money << endl;
        cout << sales_cnt << endl;
        cout << sales_money << endl;
    }

};

int SALES::total_cnt = 0;
int SALES::total_money = 0;

int main()
{
	SALES a(5, 200);
	SALES b(2, 30);

	a.sales_report(7, 500);
	b.sales_report(9, 600);

	a.print_report();
	b.print_report();

	return 0;
}

#endif

#if 0
#include <iostream>
using namespace std;

// 코드 설계
class SALES
{
private:
    static int total_cnt;
    static int total_money;

    int sales_cnt;
    int sales_money;

public:
    SALES(int c, int m)
    {
        sales_cnt = c; 
        sales_money = m;
        total_cnt += c;
        total_money += m;

    }
    void sales_report(int c, int m)
    {
        sales_cnt += c;
        sales_money += m;
        total_cnt += c;
        total_money += m;
    }

    static void total_report()
    {
        cout << total_cnt << endl;
        cout << total_money <<endl;
    }

    void my_report()
    {
        cout << sales_cnt << endl;
        cout << sales_money << endl;
    }



};

int SALES::total_cnt = 0;
int SALES::total_money = 0;

int main()
{
	SALES a(5, 200);
	SALES b(2, 30);

	a.sales_report(7, 500);
	b.sales_report(9, 600);

	a.my_report();
	b.my_report();
	SALES::total_report();

	return 0;
}

#endif

#if 0
#include <iostream>
using namespace std;

class student
{
public:
	int age;

	student(int a) : age(a) {}

	int func() const
	{
		cout << age << endl;
		return age;
	}
};

int main(void)
{
	const student x(10);

	int r = x.func();

	cout << r << endl;

	return 0;
}
#endif