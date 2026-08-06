# C++ 시험 정리 

---

## 0. 문제 유형 → 바로 찾아가기

| 문제에 이런 말이 나오면 | 핵심 도구 | 섹션 |
|---|---|---|
| "16진수로 출력", "0x 붙여서" | `hex` `showbase` `uppercase` | 1 |
| "16진수로 입력받아" | `cin >> hex >> x` | 1 |
| "인자를 생략해도 동작" | 디폴트 인자 | 2 |
| "타입에 따라 다르게 동작하는 함수" | 오버로딩 / 템플릿 | 2 |
| "배열을 넘겨서 ranged for로" | `T (&arr)[N]` 템플릿 | 2 |
| "heap에 생성하고 반드시 반환" | `new[]` / `delete[]` | 3 |
| "전달된 인자의 원본이 바뀌어야" | 참조 `&` | 3 |
| "private 멤버를 바꾸는 함수" | `this->` 또는 `클래스::` | 4 |
| "const 멤버 / 참조 멤버 초기화" | 초기화 리스트 `: a(x)` | 4 |
| "모든 instance가 공유하는 값" | `static` 멤버 | 5 |
| "instance 없이 호출" | `static` 멤버 함수 | 5 |
| "const 객체가 호출" | `const` 멤버 함수 | 5 |
| "base 생성자에 값 전달" | `: Base(c)` 초기화 리스트 | 6 |
| "상속했는데 접근이 안 됨" | 접근지정자 표 / `friend` | 6 |
| "타입에 맞는 함수가 호출되도록" | `virtual` (다형성) | 7 |
| "함수 내부는 수정하지 말고" | `virtual` 붙이기 | 7 |
| "base 포인터로 derived 멤버 접근" | 다운캐스팅 | 7 |
| "반드시 자식이 구현하도록" | 순수 가상 함수 `= 0` | 7 |
| "여러 종류를 배열 하나로 관리" | `Base *a[2]{&x,&y};` | 7 |
| "a + b 가 되도록", "*x 가 되도록" | 연산자 오버로딩 | 8 |
| "a << 10 << 20 처럼 연속으로" | **참조 반환** `T&` | 8 |

---

## 1. 입출력 & 조작자 (iostream / iomanip)

### 1-1. 출력 조작자

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int i = 255;
cout << showbase << uppercase << hex << i << endl;   // 0XFF
```

| 조작자 | 효과 | 헤더 |
|---|---|---|
| `dec` `hex` `oct` | 진법 변경 (한 번 걸면 계속 유지) | iostream |
| `showbase` | 접두사 표시 (`0x`, `0`) | iostream |
| `uppercase` | 영문자 대문자로 (`0XFF`) | iostream |
| `endl` | 개행 + flush | iostream |
| `setw(n)` | **다음 1개**만 폭 n | iomanip |
| `setfill('*')` | 빈칸 채울 문자 | iomanip |
| `setprecision(n)` | 유효자리 n | iomanip |
| `fixed` | 소수점 이하 고정 | iostream |

> **팁**: `setw`만 "1회용", 나머지는 "한 번 걸면 계속". 시험에서 두 줄 출력이 이상하면 이거부터 의심.

### 1-2. 입력 조작자

```cpp
int x, y;
cin >> x >> hex >> y;      // x는 10진수, y는 16진수로 해석
cout << dec << x + y << endl;   // 출력할 땐 dec로 되돌려야 함!
```

> **팁**: `cin`에도 `hex`가 먹는다. 그리고 **출력 전에 `dec` 복구**를 잊지 말 것.

### 1-3. 문자열 입력

```cpp
int n;  cin >> n;
char c1[20], c2[20];
cin >> c1 >> c2;                  // 공백 기준으로 두 단어 분리
for (int i = 0; i < n; i++)
    cout << c2 << endl;           // 두 번째 단어를 n줄 출력
```

> `cin >>`는 공백에서 끊긴다. 한 줄 통째로 받으려면 `cin.getline(buf, 20)`.

---

## 2. 함수 (디폴트 인자 · 오버로딩 · 템플릿)

### 2-1. 디폴트 인자

```cpp
int compute_price(int x, double y = 0.1)
{
    return x - x * y;
}
compute_price(12000, 0.25);   // 9000
compute_price(12000);         // 10800
```

**규칙 (자주 나오는 함정)**
- 디폴트 인자는 **오른쪽부터** 채워야 한다. `f(int a = 1, int b)` ✗
- **선언과 정의를 분리하면 디폴트값은 선언(클래스 안)에만 쓴다.**

```cpp
class mart_calc {
public:
    double total = 0;
    void buy(int price, double tax = 0.01);   // 여기에만 =0.01
};
void mart_calc::buy(int price, double tax)    // 여기엔 쓰지 않음!
{ total += price * (1 + tax); }
```

### 2-2. 오버로딩

```cpp
int    func(int x)              { return x * x; }
int    func(double a)           { return (int)(a + 0.5); }   // 반올림
double func(int x, double y)    { return x + y; }
```

> **팁**: 리턴 타입만 다른 건 오버로딩이 **아니다**. 반드시 `매개변수 개수 or 타입`이 달라야 함.
> 반올림 관용구: `(int)(a + 0.5)`

### 2-3. 템플릿

```cpp
template <typename T>
T func(T a, T b) { return a + b; }

template <typename T>
void print_info(T *p) { p->prt(); }    // 서로 다른 클래스 포인터 하나로 처리
```

**템플릿 vs 일반 함수가 같이 있으면 → 딱 맞는 일반 함수가 이긴다.**

```cpp
template <typename T> void prt_info(T *p) { /* 일반 처리 */ }
void prt_info(rectagle *p)                { /* rectagle 전용이 우선 호출 */ }
```

### 2-4. 배열을 템플릿으로 받기 (⭐ ranged for 문제 단골)

```cpp
template <typename T, int N>
void func(T (&arr)[N])                 // 배열의 "참조" → 크기 N이 자동 추론
{
    for (const auto &e : arr)
        cout << e << endl;
}

int a[3] = {10,20,30};
const char *b[2] = {"Kim","Lee"};
func(a);   func(b);
```

> **팁**: `T *p`로 받으면 크기 정보가 사라져서 ranged for를 못 쓴다.
> 괄호 위치 암기: **`T (&arr)[N]`** — "참조를 괄호로 묶는다".

---

## 3. 참조 · 포인터 · heap

### 3-1. 참조로 원본 바꾸기

```cpp
void func(char &r, char name) { r = name; }   // 리턴 없으면 void!
_st s{100, 'A'};
func(s.b, 'Z');                // s.b가 실제로 바뀐다
```

> **팁**: "원본이 갱신되어야 한다" = `&`. 리턴 타입 `char`로 써놓고 return 안 하면 UB → **void로**.

### 3-2. heap 사용 정석 (문제: "heap에 생성하고 반드시 반환")

```cpp
int n;  cin >> n;
int *p = new int[n];           // 생성

for (int i = 0; i < n; i++) cin >> p[i];   // 다 받은 후에

int max = p[0];
for (int i = 1; i < n; i++)
    if (p[i] > max) max = p[i];

cout << max << endl;
delete[] p;                    // 반드시 반환
```

> **팁 3종**: `new int[n]` ↔ `delete[] p` 짝 / 초기 max는 **첫 원소**로 / 배열 `int a[10]`은 heap이 아니다(감점 포인트).

### 3-3. 포인터로 멤버 접근

```cpp
test x(20);
test *p = &x;        // 또는 test *p(&x);
cout << (*p).a;      // 두 표현 동일
cout << p->a;
```

---

## 4. 클래스 기본

### 4-1. 멤버 함수 외부 정의 + 이름 충돌

```cpp
class mart_calc {
private:
    double tax = 0.01;
public:
    void change_tax(double tax);
};

void mart_calc::change_tax(double tax)
{
    this->tax = tax;          // 방법 1 (제일 무난)
    // mart_calc::tax = tax;  // 방법 2
}
```

> **팁**: 매개변수 이름이 멤버와 같으면 **매개변수가 이긴다** → `this->` 필수.

### 4-2. 생성자 & 초기화 리스트

```cpp
class circle : public figure {
    const int radius;          // const 멤버
public:
    circle(const char *c, int r) : figure(c), radius(r) { }
};
```

**초기화 리스트에서만 가능한 3가지 (⭐ 시험 포인트)**
1. `const` 멤버
2. 참조(`&`) 멤버
3. base class 생성자 호출

> 몸통 `{ }` 안은 "대입"이라 위 3개는 불가능.

### 4-3. 객체 배열 / 구조체 멤버 초기화

```cpp
test y[2] {test(10), test(20)};   // 또는  test y[2] {10, 20};
cout << y[0].a;

struct st { int m1; test m2; };
st z = { 10, test(20) };
cout << z.m2.a;
```

---

## 5. static 멤버 · const 멤버 함수

### 5-1. static 데이터/함수

```cpp
class SALES {
private:
    static int total_cnt;      // 선언
    int sales_cnt;
public:
    SALES(int c) : sales_cnt(c) { total_cnt += c; }

    static void total_report()          // instance 없이 호출 가능
    { cout << total_cnt << endl; }      // static 멤버만 접근 가능!

    void my_report() { cout << sales_cnt << endl; }
};

int SALES::total_cnt = 0;      // ⭐ 클래스 밖에서 반드시 정의(초기화)

SALES::total_report();         // 호출 형식
```

**암기 3줄**
- static 데이터는 **모든 instance가 공유**, 클래스 밖에서 `타입 클래스명::이름 = 0;` 필수.
- static 함수 안에는 `this`가 없다 → **일반 멤버 접근 불가**.
- "전체 합계 vs 개별 합계"가 같이 나오면 → static + 일반 멤버 조합 문제.

### 5-2. const 멤버 함수

```cpp
class student {
public:
    int age;
    student(int a) : age(a) {}
    int func() const              // 멤버를 수정하지 않겠다는 약속
    { cout << age << endl; return age; }
};

const student x(10);
x.func();        // const 객체는 const 멤버 함수만 호출 가능
```

> **팁**: `const` 객체가 나오면 호출하는 함수 뒤에 `const`가 붙어있는지 확인. 없으면 컴파일 에러.

---

## 6. 상속

### 6-1. 접근 지정자 표 (⭐ 통째로 암기)

| base 멤버 \ 상속 방식 | `public` 상속 | `protected` 상속 | `private` 상속 |
|---|---|---|---|
| public | public | protected | private |
| protected | protected | protected | private |
| private | **접근 불가** | 접근 불가 | 접근 불가 |

- base의 `private`은 상속 방식과 무관하게 **자식이 직접 못 쓴다** → public getter/setter 경유.
- 상속 방식 생략 시 `class`는 `private`, `struct`는 `public`.

```cpp
class figure {
    int color_index;                      // private
public:
    void set_color(int ci) { color_index = ci; }
    int  get_color()       { return color_index; }
};

class circle : public figure {
    int radius;
public:
    circle(int r, int ci) { radius = r; set_color(ci); }   // getter/setter로 접근
    void info() { cout << get_color() << endl << radius << endl; }
};
```

### 6-2. base 생성자 호출

```cpp
class figure {
public:
    figure(int ci) : color_index(ci) {}
};
class circle : public figure {
    int radius;
public:
    circle(int r, int ci) : figure(ci) { radius = r; }   // base부터 초기화
};
```

**생성 순서**: base 생성자 → 멤버 초기화 → 자식 몸통. 소멸은 반대 순서.
base에 디폴트 생성자가 없으면 **초기화 리스트에서 반드시 호출**해야 함.

### 6-3. friend

```cpp
class B {
    friend class C;      // C는 B의 private에 접근 가능
    friend void f();     // 전역 함수 f도 가능
};
```

- friend는 **주는 쪽(B)이 선언**한다. 받는 쪽이 선언하는 게 아님.
- **단방향**이고 **상속되지 않으며 전이되지도 않는다** (A→B friend, B→C friend여도 A→C는 아님).

---

## 7. 다형성 (virtual / 캐스팅 / 순수 가상)

### 7-1. 함수 은닉 vs 가상 함수

```cpp
// virtual 없음 → 포인터 "타입" 기준으로 호출 (정적 바인딩)
figure *p = &r;   p->prt_info();       // figure의 것이 호출됨

// virtual 있음 → 실제 "객체" 기준으로 호출 (동적 바인딩)
class figure {
public:
    virtual void prt_info() { cout << color_index << endl; }
};
class square : public figure {
public:
    virtual void prt_info() { cout << color_index << endl << width << endl; }
};
```

> **⭐ 단골 문제**: "함수 내부는 수정하지 말고 타입에 맞는 함수가 호출되게 하라"
> → **답은 base의 함수에 `virtual` 한 단어 추가**. (자식 쪽은 `virtual`/`override` 생략 가능하지만 붙여주면 안전)

### 7-2. 업캐스팅 / 다운캐스팅

```cpp
void prt_height(figure *p)          // 포인터 버전
{ cout << ((rectagle *)p)->height << endl; }

void prt_height(const figure &x)    // 참조 버전
{ cout << ((rectagle &)x).height << endl; }
```

> **팁**: 포인터는 `((T*)p)->m`, 참조는 `((T&)x).m`. **괄호 위치가 채점 포인트**.
> 업캐스팅(자식→부모)은 자동, 다운캐스팅(부모→자식)은 **명시적 캐스팅 필요**.

### 7-3. 타입 구분해서 처리하기

가상 함수 없이 "circle이면 A, rectagle이면 B" 를 요구하면 → base에 타입 식별 멤버를 두거나 `dynamic_cast` 사용:

```cpp
void prt_info(figure *p)
{
    cout << p->color_index << endl;
    if (square *s = dynamic_cast<square *>(p)) {      // 실패하면 nullptr
        cout << s->width << endl;
        if (rectagle *r = dynamic_cast<rectagle *>(p))
            cout << r->height << endl;
    }
}
```
> `dynamic_cast`를 쓰려면 base에 **virtual 함수가 하나라도** 있어야 한다(보통 `virtual ~figure(){}`).
> 수업 범위대로면 **virtual 함수로 푸는 게 정답 루트**.

### 7-4. 순수 가상 함수 / 추상 클래스

```cpp
class figure {
public:
    virtual void set_size(int) = 0;      // 순수 가상
    virtual int  get_size()    = 0;
};

class square : public figure {
public:
    int width;
    virtual void set_size(int w) override { width = w; }
    virtual int  get_size()      override { return width; }
};
```

- 순수 가상 함수가 하나라도 있으면 **추상 클래스 → 객체 생성 불가**, 포인터/참조는 가능.
- 자식이 하나라도 구현 안 하면 자식도 추상 클래스.
- `override`는 오타 방지용. 붙여두면 시그니처 틀렸을 때 컴파일 에러로 잡아줌.

### 7-5. 서로 다른 자식을 배열 하나로

```cpp
circle c;  square s;
figure *a[2] { &c, &s };       // base 포인터 배열

a[0]->set_size(10);
a[1]->set_size(20);
cout << a[0]->get_size() << endl;
```

> **팁**: `figure a[2]`는 불가(추상 + 슬라이싱). 반드시 **포인터 배열**.

---

## 8. 연산자 오버로딩

### 8-1. 기본 형태 (이항, 멤버 함수)

```cpp
class box {
public:
    int width, height;
    box(int w, int h) : width(w), height(h) {}

    box operator+(const box &other)          // a + b
    { return box(width + other.width, height + other.height); }

    void prt_info() { cout << width << endl << height << endl; }
};

box c = a + b;
```

> **핵심**: 멤버 함수로 만들면 **왼쪽 피연산자가 자기 자신(`this`)**, 오른쪽만 인자로 받는다.
> `a + b` → `a.operator+(b)`

### 8-2. 클래스 + 정수

```cpp
box operator+(int m)                       // a + 10
{ return box(width + m, height + m); }
```

`10 + a` 처럼 **정수가 왼쪽**이면 멤버 함수로 불가 → 전역(friend) 함수로:

```cpp
class box { ... friend box operator+(int m, const box &b); };

box operator+(int m, const box &b)
{ return box(m + b.width, m + b.height); }
```

### 8-3. 단항 연산자

```cpp
class box {
public:
    int operator*()                        // *a  (단항 *)
    { return width * height; }
};
cout << *a << endl;
```

> **팁**: **인자 개수로 단항/이항을 구분**한다.
> 멤버 함수 기준 — 인자 0개 = 단항, 인자 1개 = 이항.
> 전역 함수 기준 — 인자 1개 = 단항, 인자 2개 = 이항.

### 8-4. ⭐ 체이닝 문제 (값 반환 vs 참조 반환)

```cpp
class myout {
public:
    int n;
    myout(int in = 0) : n(in) {}

    myout& operator<<(int m)      // ← myout 이 아니라 myout&
    {
        this->n += m;
        return *this;             // 원본의 참조를 반환
    }
};

myout x;
cout << (x << 10 << 20 << 30).n << endl;   // 60
cout << x.n << endl;                       // 60 (참조 반환이라 원본도 갱신)
```

**왜?**
- `myout` (값) 반환 → 매번 **복사본**이 생겨 체이닝이 복사본 위에서 진행 → 원본 x는 10만 반영.
- `myout&` (참조) 반환 → 모든 `<<`가 **같은 객체**에서 일어남 → 원본도 60.

> **암기**: "연속으로 이어 쓰는 연산자(`<<`, `=`, `+=`)는 **참조 반환**".

### 8-5. cout으로 내 클래스 출력하기

```cpp
class box {
    friend ostream& operator<<(ostream &os, const box &b);
};

ostream& operator<<(ostream &os, const box &b)
{
    os << b.width << "*" << b.height;
    return os;                    // 반드시 os 참조 반환
}

cout << a << endl;
```

> **팁**: 왼쪽이 `cout`이라 **멤버 함수로는 불가** → 반드시 전역 friend 함수. 리턴은 `ostream&`.

### 8-6. 오버로딩 가능/불가

- 불가: `.` `.*` `::` `?:` `sizeof`
- `=`, `[]`, `()`, `->` 는 **반드시 멤버 함수**로만.

---

## 9. 확인하기

1. `int main()` 끝에 `return 0;` 넣었는가.
2. static 멤버 → **클래스 밖 정의** 썼는가. (`int SALES::total_cnt = 0;`)
3. const/참조 멤버 & base 생성자 → **초기화 리스트**에 있는가.
4. 디폴트 인자 → 선언부에만 썼는가.
5. "타입에 맞게 호출" → base에 **`virtual`** 붙였는가.
6. 다운캐스팅 괄호 → `((T*)p)->m` / `((T&)x).m`
7. `new[]` 썼으면 `delete[]` 짝이 있는가.
8. 체이닝 연산자 → **`T&` 반환 + `return *this;`**
9. 출력 진법 바꿨으면 `dec` 복구했는가.
10. 함수에 리턴 타입 있으면 `return` 문 있는가.
