// 1번 문제
#if 0
#include <iostream>
using namespace std;

class figure
{
private:
	int color_index;

public:
	void set_color(int ci)
	{
		color_index = ci;
	}
	
	int get_color()
	{
		return color_index;
	}
};

class circle : public figure
{
    private:
        int radius;

    public:
        circle(int r, int ci)
        {
            radius = r;
            set_color(ci);
        }

        void info()
        {
            cout << get_color() << endl;
            cout << radius << endl;
        }

};


class box :public figure
{
    private:
        int width;
        int height;
    
    public:
        box(int w, int h, int ci)
        {
            width = w;
            height = h;
            set_color(ci);
        }

        void info()
        {
            cout << get_color() << endl;
            cout << width << endl;
            cout << height << endl;
        }

};

int main()
{
circle c(5, 1);
box b(10, 20, 2);

c.info();
b.info();

return 0;
}

#endif

// 2번 문제
#if 0
#include <iostream>
using namespace std;

class A
{
public:
	int x = 10;
};

class B : public A
{
public:
	int y = 20;
};

class C : public B
{
public:
	int z = 30;
};

int main()
{
	C c;

	cout << c.x << endl;
	cout << c.y << endl;
	cout << c.z << endl;

	return 0;
}
#endif

// 3번 문제
#if 0
#include <iostream>
using namespace std;

class A
{
public:
	int x = 10;
};

class B : private A
{
public:
	int y = 20;
	
friend class C;
friend class D;


};

class C : protected B
{
public:
	int z = 30;
	
friend class B;
friend void f();
};

class D
{
	B b;
public:
	void prt()
	{
		cout << b.x << endl;
	}
	
};

void f()
{
	C c;
	cout << c.y << endl;


}

int main()
{
	D d;
	
	d.prt();
	f();

	return 0;
}
#endif

// 4번 문제
#if 0
#include <iostream>
using namespace std;

class figure
{
private:
	int color_index;

public:
	figure(int ci) : color_index(ci) {}

	int get_color()
	{
		return color_index;
	}
};

class circle : public figure
{
private:
	int radius;
public:

	// 생성자 설계
	circle (int r, int ci) : figure(ci)
    {
        radius = r;
        
    }

	void info()
	{
		cout << get_color() << endl;
		cout << radius << endl;
	}
};

int main()
{
	circle c(5, 1);
	c.info();
	return 0;
}
#endif

// 5번 문제
#if 0
#include <iostream>
using namespace std;

class figure
{
private:
	const char *color;

public:
	figure(const char *c) : color(c) {}

	const char * get_color()
	{
		return color;
	}
};

class circle : public figure
{
private:
	const int radius;
public:

	// 생성자 설계
    // const 멤버, 레퍼런스(&) 멤버, base class 생성자 호출은 반드시 여기서
    circle(const char *c, int r): figure(c), radius(r)
    {
              
    }

	void info()
	{
		cout << get_color() << endl;
		cout << radius << endl;
	}
};

int main()
{
	circle c("White", 1);
	c.info();
	return 0;
}
#endif

// 6번 문제
#if 0
#include <iostream>
using namespace std;

class figure
{
public:
	int color_index;

	figure(int c) : color_index(c) {};
};

class circle : public figure
{
public:
	int radius;

	circle(int c, int r) : figure(c), radius(r) {};
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

// 함수 설계
void prt_info(figure *p)
{
    cout << p -> color_index << endl;
}

int main()
{
	circle c(0, 5);
	square s(1, 10);
	rectagle r(2, 20, 30);

	prt_info(&c);
	prt_info(&s);
	prt_info(&r);

	return 0;
}
#endif

// 7번 문제
#if 0
/*
주어진 코드에서 prt_height 함수를 설계하라.
전달받은 class 포인터를 이용하여 rectagle class의 멤버 데이터인 height 값을 인쇄해야 한다.
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

void prt_height(figure * p)
{
	// 전달받은 r 주소를 이용하여 r의 height 인쇄
    cout << ((rectagle *)p) -> height << endl; 

}

int main()
{
	rectagle r(2, 20, 30);
	prt_height(&r);
	return 0;
}
#endif

// 8번 문제
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

void prt_height(const figure &x)
{
	// 전달받은 r의 reference를 이용하여 r의 height 인쇄
    cout <<  << endl;
}

int main()
{
	rectagle r(2, 20, 30);

	prt_height(r);

	return 0;
}
#endif