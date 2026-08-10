// 문제 1
#if 0
#include <iostream>
using namespace std;

class acc_add
{
private: 
	int sum;

// 코드 구현
public:
    int total = 0;

    acc_add(int num): sum(0)
    {
        sum += num;
    }

    void add(int n)
    {
        sum +=n;
    }

    int result()
    {
        return sum;
    }
};

int main()
{
	acc_add a(10);

	a.add(20);
	a.add(30);

	cout << a.result() << endl;

	return 0;
}
#endif

// 문제 2
#if 0
#include <iostream>
using namespace std;

class school
{
   // 코드 설계
   public:
        static int cnt;
        const char *name;

        school(const char *n): name("")
        {
            cnt ++;
            name = n;
        }

        ~school()
        {
            cnt --;
        }

        void prt_name()
        {
            cout << name << endl;
        }

        static void prt_count()
        {
            cout << cnt << endl;
        }

   
};

int school::cnt = 0;

int main()
{
	school s1("Kim");
	{
		school s2("Lee");

		{
			school s3("Park");

			s1.prt_name();
			s2.prt_name();
			s3.prt_name();

			school::prt_count();
		}

		school::prt_count();
	}
	
	school::prt_count();

	return 0;
}
#endif

// 문제 3
#if 0
#include <iostream>
using namespace std;

class box
{
public:
	int color_index;

	box(int ci)
	{
		this->color_index = ci;
	}
};

class squre : public box
{
public:
	int widht;

	// 코드 구현
    squre(int ci, int w): box(ci)
    {
        widht = w;
    }

    void prt_info()
    {
        cout << color_index << endl;
        cout << widht << endl;
    }

};

class rectangle : public squre
{
public:

	int height;

	// 코드 구현
    rectangle(int ci, int w, int h): squre(ci, w)
    {
        height = h;
    }

    void prt_info()
    {
        cout << color_index << endl;
        cout << widht << endl;
        cout << height << endl;
    }


};

int main()
{
	int w, h;

	cin >> w >> h;

	squre a(1, w);
	rectangle b(2, w, h);

	a.prt_info();
	b.prt_info();

	return 0;
}
#endif

//문제 4
#if 1
#include <iostream>
using namespace std;

class x
{
public:
	int xx = 10;

	virtual int prt()
	{
		return this->xx;
	}
};

class y : public x
{
public:
	int xx = 20;

	virtual int prt() override
	{
		return xx;
	}
};

class z : public y
{
public:
	int xx = 30;

	virtual int prt() override
	{
		return xx;
	}
};

int prt(x * p)
{
	return p->prt();
}

int main()
{
	x a;
	y b;
	z c;

	cout << prt(&a) << endl;
	cout << prt(&b) << endl;
	cout << prt(&c) << endl;

	return 0;
}
#endif

#if 01
/*
다음 조건을 만족하는 연산자 overloading 함수를 설계하라.
단, 주어진 코드는 절대 수정하면 안된다.

1. names << n : << 연산을 수행하면 class arr의 a[n] 요소 이름을 리턴한다.
2. names(n) : n을 넣고 호출 연산자를 사용하면 class arr의 a[n] 요소의 글자수를 리턴한다.
3. << 연산자 overloading 함수는 class 외부에, () overloading 함수는 class 내부에 설계하라.
4. 단, 키보드로 입력되는 값은 0~3 사이의 정수 값이다.
*/
#include <iostream>
using namespace std;

#include <string.h>

class arr
{
private:
	const char * a[4] = { "kim","lee","park", "moon" };

	friend const char * operator<<(const arr& x, int n);
public:

	// 코드 구현
   
};

const char * operator<<(const arr& x, int n)
{
	// 코드 구현
    
    return ;
}

int main()
{
	int n;
	cin >> n;
	arr names;

	cout << (names << n) << endl;
	cout << names(n) << endl;

	return 0;
}
#endif