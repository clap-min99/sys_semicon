// 문제 1
#if 0
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int i = 0;
    cin >> i;
    cout << showbase << uppercase << hex << i << endl; 
}
#endif

// 문제 2
#if 0
#include <iostream>

using namespace std;


int main()
{
    int x, y;

    cin >> x >> hex >> y;
    
    cout << dec << x+y << endl;
    
}
#endif

// 문제 3
#if 0
/*
첫번째 줄에 정수(n) 하나를 입력 받는다.
두번째 줄에 공백(공백은 하나만 존재)으로 분리된 두개의 단어가 입력된다.
이때 두번째 단어를 n줄에 걸쳐서 인쇄하는 코드를 구현하라.
*/

#include <iostream>
using namespace std;

int main()
{
    int x;
    cin >> x;

    char c1[20], c2[20];
    cin >> c1 >> c2;

    for (int i = 0; i < x; i++)
    {
        cout << c2 << endl;
    }

}
#endif

// 문제 4
#if 0
#include <iostream>
using namespace std;

// 함수 설계
int compute_price(int x, double y = 0.1)
{
    int price = 0;
    price = x - x * y;
    return price;
}


int main()
{
	cout << compute_price(12000, 0.25) << endl;
	cout << compute_price(12000) << endl;
	cout << compute_price(32000, 0.1) << endl;

	return 0;
}
#endif

//문제 5
#if 0
/*
전달된 값이 정수일 경우 제곱한 결과를 반환하고
전달된 값이 실수일 경우는 정수화(반올림)한 결과를 반환하고
전달된 값이 정수 1개와 실수 1개일 경우는 두 수의 합을 실수 타입으로 반환하는 함수 func를 구현하라
템플릿 코드를 사용하라.
*/

#include <iostream>
using namespace std;

//  함수 설계
int func(int x)
{
    return x*x;
}

int func(double a)
{
    return (a+0.5);
}

double func(int x, double y)
{
    return x+y;
}

int main()
{
	cout << func(3) << endl;
	cout << func(3.49) << endl;
	cout << func(3.51) << endl;
	cout << func(10, 3.14) << endl;

	return 0;
}

#endif

// 문제 6
#if 0
/*
첫 줄에 정수 n이 입력되고 다음줄부터 n줄에 걸쳐서 정수가 입력된다.
n개의 정수를 저장할 공간을 heap에 생성하고 n개의 정수를 입력받아서 최대값을 구해 반환하는 코드를 구현하라.
단, 반드시 모든 n개의 정수를 다 입력받은 후 에 최대값을 구해야하며 반드시 생성한 heap 공간은 반환하도록 해야 한다.
*/
#include <iostream>
using namespace std;

int main()
{
    int i, n;
    cin >> n;

    int container[10];

    for (i=0; i<n; i++)
    {
        int a;
        cin >> a;
        container[i] = a;
    }

    double max= -10e9;
    int j = 0;
    for (;;)
    {
        if (j >= n) break;
        
        if (max < container[j])
        {
            max = container[j];
            j++;
        }
        else j++;

    }

    cout << max << endl;
    
}

#endif

// 문제 7
#if 0
#include <iostream>
using namespace std;

// 함수 설계
char func(char &r, char name)
{
	r = name;
}

int main()
{
	struct _st
	{
		int a;
		char b;
	};
	
	_st s{100, 'A'};
	char n;

	cin >> n;
	func(s.b, n);

	cout << s.b << endl;

	return 0;
}

#endif

// 문제 8
#if 1
/*
다음과 같이 배열 a와 b를 전달하면 그 내용을 한줄에 하나씩 인쇄하는 함수 func를 설계하라.
단, ranged for를 이용하여 구현해야한다.
템플릿 코드를 이용하여 구현하라.
*/
#include <iostream>
using namespace std;

// 함수 설계
template<typename T, int N>
void func(T (&arr)[N])
{
    for (const auto& e : arr)   // 배열의 주소를 넘겨줘야한다
        cout << e << " "<<endl;
}

/*
void func(int *p)
{
    for(int i=0;i<3;i++)
    {
        cout << p[i];
    }
}

void func(const char **p)
{
    for (int i=0; i<2; i++)
    {
        cout << p[i] << endl;
    }
}

*/

int main()
{
	int a[3] = { 10,20,30 };
	const char * b[2] = { "Kim", "Lee" };

	func(a);
	func(b);

	return 0;
}
#endif