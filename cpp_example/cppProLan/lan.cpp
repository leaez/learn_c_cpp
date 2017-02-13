#include <iostream>
#include <string>
#include <array>
#include <map>
#include <tuple>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <initializer_list>

//#include <stdio>
using std::cout;
using namespace std;

struct X {
    //implicit conversion
    operator int() const { return 7; }
 
    // explicit conversion
    explicit operator int*() const { return nullptr; }
 
    // Error: array operator not allowed in conversion-type-id
    // operator int(*)[3]() const { return nullptr; }
    using arr_t = int[3];
    operator arr_t*() const { return nullptr; } // OK if done through typedef
    //operator arr_t () const; // Error: conversion to array not allowed in any case
};

void test1()
{
    X x;
 
    int n = static_cast<int>(x);   // OK: sets n to 7
    int m = x;                     // OK: sets m to 7

    cout << n << "   " << m << "\n";
}

#include <iostream>
#include <typeinfo>
struct Base1 {/** polymorphic type: declares a virtual member */ 
    virtual ~Base1() {}
};
struct Derived1 : Base1 {/** polymorphic type: inherits a virtual member */ 
};
 
struct Base2 {/** non-polymorphic type*/ 
};
struct Derived2 : Base2 {/** non-polymorphic type */ 
};
 
void test2()
{
    Derived1 obj1; // object1 created with type Derived1
    Derived2 obj2; // object2 created with type Derived2
 
    Base1& b1 = obj1; // b1 refers to the object obj1
    Base2& b2 = obj2; // b2 refers to the object obj2
 
    std::cout << "Expression type of b1: " << typeid(decltype(b1)).name() << ' '
              << "Expression type of b2: " << typeid(decltype(b2)).name() << '\n'
              << "Object type of b1: " << typeid(b1).name() << ' '  /** virtual; derived */ 
              << "Object type of b2: " << typeid(b2).name() << '\n' /** no virtual: base */ 
              << "size of b1: " << sizeof b1 << ' '
              << "size of b2: " << sizeof b2 << '\n';
}

struct S1 {
    static int x ; // static data member 只是申明
    // a definition outside of class is required if it is odr-used
};
int S1::x = 23;  //定义

struct S2 { S2(std::string) {} }; // implicitly convertible from std::string


int f1(int a)
{cout <<"f1 called :" << a <<"\n";} 

/**  */ 
class X1 {
    public:
    static int a; 
    int mem1(int i = a){cout << i <<"\n";}; 
    using fp1 = int(*)(int);
    operator fp1() { return f1; }
};
int X1::a = 10;

/** inner class  */ 
class enclose { // enclosing class
    int x; // note: private members
    static int s;
 public:
    struct inner { // nested class
        void f(int i) {
            s = i; 
            // x =i ;erorr canot to non-static 不能访问非 静态
        }
        void g(enclose* p, int i) {
            p->x = i; // OK: assign to enclose::x 可以通过间接 指针访问
        }
    };
};

struct AA{
    int x;
    AA(int x = 1): x(x) {cout <<"aa called :" << x <<"\n";} // user-defined default constructor
};

struct EE: AA
{
    EE(int y): AA(y) {}
    EE() = default; // explicitly defaulted, calls A::A()
};

/** template */ 
int ai[2]= {1, 2};
int abc = 123;
const int *cp= const_cast<int *>(&abc);
const int b[3] = {1,2,3}; 
template<int (&pa)[3]> struct W {};
template<const int* pci> struct X2 {};
template<int (*pf)(int)> struct X3 {X3(){pf(99);}};  //类似回调

template<class T> class X4{}; // declaration, not definition
template<typename T>void f(T s){
    std::cout << s << '\n';
}

/** 多个参数 */ 
template<class... Types> void f2(Types... values){
    //for(auto v: values){
    //    cout << v ; 
   // }   cout << "\n"; 
}
template<typename T, typename... Tail> void ff(T head, Tail... tail){ //...indicate the rest
    g(head); /*  do something to head */ 
    f(tail...); }// try again with tail

template<int I, int J, class T> struct X5 { 
    T i = 55;
    void f(T i){
    cout << I << J  << i << "\n";}}; 

//constexpr int *cp= &abc;  
/********************* 
 *
 * */ 
int main()
{
    /**  */ 
    test1();

    /** 多态  */ 
    test2();

    /** static */
    S1::x = 55;
    cout << S1::x << "\n";

    /** initalize */ 
    S2 s1("abc"); // OK: conversion from const char[4] to std::string
    //S2 s2 = "abc"; // Error: no conversion from const char[4] to S
    // S2 s = "abc"s; // error: conversion from std::string to S
    int n = 1;
    double&& copy_ref = n; // bind to an rvalue temporary with value 1.0
    
    /** constructor */  
    X1 x1;
    x1.mem1();
    X1::a = 100;
    x1.mem1();

    EE e;
    
    /** template */ 
    //W<b> w; // eror: no conversion
    //int * pai = const_cast<int * >(ai);
    X2<ai> xi;  // ok: array to pointer conversion and cv-qualification conversion
    X3<&f1> x3;
    X4<char> ch;  
    f<string>("ffsdfsd");
    f<>('a');
    f(12);
    void (*ptr)(std::string) = f;
    ptr("------sfdfs");
    X5<2,3,int> x5;
    x5.f(852);

    /** const pioint */ 
    int i2;
    const int *cp = &i2; // 指针指向 常量
    //*cp = 23; //error readonly
    int *p = const_cast<int *>(cp);
    *p = 10;
    int * const cp2 = p; // here the static_cast is optional
    //cp2 = &i2;  //error readonly
    cout << i2 << "\n";

    
}
