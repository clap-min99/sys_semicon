// 문제 1
#if 0
#include <iostream>
using namespace std;

class figure
{
public:
	int color_index;

	figure(int c) : color_index(c) {};
};

class square : public figure
{
public:
	int width;

	square(int c, int w) : figure(c), width(w) {};

	// prt_size 함수 설계
    void prt_size()
    {
        cout << width << endl;
    }

};

class rectagle : public square
{
public:
	int height;

	rectagle(int c, int w, int h) : square(c, w), height(h) {}

	// prt_size 함수 설계
    void prt_size()
    {
        cout << width << "*" << height << endl;
    }

};

int main()
{
	square s(1, 10);
	rectagle r(2, 20, 30);

	s.prt_size();
	r.prt_size();

	return 0;
}


#endif

// 문제 2
#if 0
/*
주어진 코드를 실행하면 전달되는 instance의 주소 타입이 figure *로 upcasting 되어 figure의 prt_info가 호출된다.
출력 예시와 같이 전달되는 instance 주소 타입에 따라서 각각 square와 rectagle의 prt_info가 호출되도록 코드를 수정하라.
단, 제시된 코드의 prt_info 내부 코드는 변경하지 않아야 한다.
*/
#include <iostream>
using namespace std;

class figure
{
public:
	int color_index;

	figure(int c) : color_index(c) {};

	virtual void prt_info()
	{
		cout << color_index << endl;
	}
};

class square : public figure
{
public:
	int width;

	square(int c, int w) : figure(c), width(w) {};

	virtual void prt_info()
	{
		cout << color_index << endl;
		cout << width << endl;
	}
};

class rectagle : public square
{
public:
	int height;

	rectagle(int c, int w, int h) : square(c, w), height(h) {}

	virtual void prt_info()
	{
		cout << color_index << endl;
		cout << width << "*" << height << endl;
	}
};

void prt_info(figure * p)
{
	p->prt_info();
}

int main()
{
	square s(1, 10);
	rectagle r(2, 20, 30);

	prt_info(&s);
	prt_info(&r);

	return 0;
}
#endif

// 문제 3
#if 0 
#include <iostream>
using namespace std;

class A
{
public:
	void prt()
	{
		cout << "A" << endl;
	}
};

class B : public A
{
public:
	void prt() 
	{
		cout << "B" << endl;
	}
};

class C : public A
{
public:
	void prt() 
	{
		cout << "C" << endl;
	}
};

// 아래 3개 함수를 하나의 generic 함수로 구현
template <typename T>
void print_info(T *p)
{
	p->prt();
}

int main(void)
{
	A x;
	B y;
	C z;

	print_info(&x);
	print_info(&y);
	print_info(&z);

	return 0;
}
#endif

// 문제 4
#if 0 
#include <iostream>
using namespace std;

class figure
{
public:
	int color_index;

	// Pure Virtual Function 설계
	virtual void set_color(int c) = 0;
	virtual void set_size(int w) = 0;
};

class square : public figure
{
public:
	int width;

	virtual void set_color(int c) override
	{
		color_index = c;
	}

	virtual void set_size(int w) override
	{
		width = w;
	}
};

class circle : public figure
{
public:
	int radius;

	virtual void set_color(int c) override
	{
		color_index = c;
	}

	virtual void set_size(int r) override
	{
		radius = r;
	}
};

int main()
{
	circle c;
	square s;

	c.set_color(0);
	c.set_size(10);

	s.set_color(1);
	s.set_size(20);

	cout << c.radius << endl;
	cout << s.width << endl;

	return 0;
}
#endif

// 문제 5
#if 0
#include <iostream>
using namespace std;

class figure
{
public:
	virtual void set_size(int) = 0;
	virtual int get_size() = 0;
};

class square : public figure
{
public:
	int width;

	virtual void set_size(int w) override
	{
		width = w;
	}

	virtual int get_size() override
	{
		return width;
	}
};

class circle : public figure
{
public:
	int radius;

	virtual void set_size(int r) override
	{
		radius = r;
	}

	virtual int get_size() override
	{
		return radius;
	}
};

int main()
{
	circle c;
	square s;

    // 배열 a 선언 및 초기화
    figure *a[2] {&c, &s};



	a[0]->set_size(10);
	a[1]->set_size(20);

	cout << a[0]->get_size() << endl;
	cout << a[1]->get_size() << endl;

	return 0;
}
#endif

// 문제 6
#if 0
#include <iostream>
using namespace std;

class figure
{
public:
	int color_index;

	figure(int c) : color_index(c) {};
};

class square : public figure
{
public:
	int width;

	square(int c, int w) : figure(c), width(w) {};
};

class rectagle : public square
{
public:
	int height;

	rectagle(int c, int w, int h) : square(c, w), height(h) {}
};

template <typename T>
void prt_info(T * p)
{
    // 코드 설계
    cout << p->color_index << endl;
    cout << p->width << endl;
}

void prt_info(rectagle * p)
{
	cout << p->color_index << endl;
	cout << p->width << endl;
	cout << p->height << endl;
}
int main()
{
	square s(1, 10);
	rectagle r(2, 20, 30);

	prt_info(&s);
	prt_info(&r);

	return 0;
}
#endif

// 문제 7
#if 0
#include <iostream>
using namespace std;

class box
{
public:
	int width;
	int height;

	box(int w, int h) : width(w), height(h) {}

        // 코드 구현
        box operator+(const box &other)
        {
            return box(width + other.width, height + other.height);
        }

	void prt_info()
	{
		cout << width << endl;
		cout << height << endl;
	}
};

int main()
{
	box a(3,4);
	box b(10,20);

	box c = a + b;
	c.prt_info();

	return 0;
}
#endif

// 8번 문제
#if 0
/*
주어진 코드에서 +, * 연산자의 overloading 함수를 아래 요구사항에 맞게 설계하라.
'요구 사항'

box class 타입과 정수의 + 연산 : width, height를 각각 정수만큼씩 더한 결과로 만든 box class 반환
box class 타입끼리의 + 연산 : 두 instance의 width, height를 각각 더한 결과로 만든 box class 반환 즉, x의 width와 y의 width, x의 height와 y의 height를 더한 결과를 갖는 box class 반환
box class 타입의 * 연산(여기서 *은 곱하기가 아닌 단항 연산자 *임) : 전달 받은 box class 타입의 instance의 width와 height를 곱한 결과를 정수형으로 반환
*/
#include <iostream>
using namespace std;

class figure
{
public:
	int color_index;

	figure(int c) : color_index(c) {};
};

class square : public figure
{
public:
	int width;

	square(int c, int w) : figure(c), width(w) {};
};

class rectagle : public square
{
public:
	int height;
	
	rectagle(int c, int w, int h) : square(c, w), height(h) {}
};

void prt_height(const figure &x)
{
	// 전달받은 r의 reference를 이용하여 r의 height 인쇄
	// downcasting
	cout << ((rectagle &)x).height << endl;
}

int main()
{
	rectagle r(2, 20, 30);

	prt_height(r);

	return 0;
}
#endif


// 9번 문제
#if 1
/*
주어진 코드를 실행하면 두 줄의 인쇄 결과가 서로 다르게 나온다.
이것은 << 연산자 overloading 함수에서 myout 타입을 리턴하므로 발생하는 문제이다.
두 번째 인쇄에서도 첫 번째 인쇄 결과와 같은 결과가 나올 수 있도록 operator<< 함수를 수정하라.
참고로, << 연산의 결과로 전달된 원본 myout 타입의 n이 갱신되어야 한다.
*/
#include <iostream>
using namespace std;

class myout
{
public:
	int n;

	myout(int in = 0) : n(in) {}

	myout& operator<<(int m)
	{
		this->n += m;
		return *this;
	}
};

int main()
{
	myout x;
	
	cout << (x << 10 << 20 << 30).n << endl;
	cout << x.n << endl;

	return 0;
}
#endif

