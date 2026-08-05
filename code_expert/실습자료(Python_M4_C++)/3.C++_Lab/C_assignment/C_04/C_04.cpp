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

// 문제 8
#if 0 
#endif

// 문제 9
#if 0 
#endif




