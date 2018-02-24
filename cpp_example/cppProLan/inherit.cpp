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
    operator int() const { return 7; } //X is convertible to 7
 
    // explicit conversion
    explicit operator int*() const { return nullptr; }
 
    // Error: array operator not allowed in conversion-type-id
    // operator int(*)[3]() const { return nullptr; }
    using arr_t = int[3];
    operator arr_t*() const { return nullptr; } // OK if done through typedef
    //operator arr_t () const; // Error: conversion to array not allowed in any case
};

struct S2 { S2(std::string) {} }; // implicitly convertible from std::string

int print_a(int a){
    cout <<"print_a called :" << a <<"\n";
    return a;} 

/**  */ 
class X1 {
    public:
    static int a; 
    int mem1(int i = a){cout << i <<"\n";}; 
    using fp1 = int(*)(int);//type declare 
    operator fp1() { return print_a; } // conversion function to pointer to function
};
int X1::a = 10;

struct AA{
    int x;
    AA(int x = 1): x(x) {cout <<"aa called :" << x <<"\n";} // user-defined default constructor
};
struct EE: AA{
    EE(int y): AA(y) {}
    EE() = default; // explicitly defaulted, calls A::A()
};


void test_convert()
{
    cout << "----- test: over load convert " <<endl;
    X x; //can use as a integer 
    int n = static_cast<int>(x);   // OK: sets n to 7
    int m = x;                     // OK: sets m to 7
    cout << n << "   " << m << "\n";

    /** initalize */ 
    S2 s1("abc"); // OK: conversion from const char[4] to std::string
    //S2 s2 = "abc"; // Error: no conversion from const char[4] to S
    // S2 s = "abc"s; // error: conversion from std::string to S
    
    X1 x1;
    x1.mem1();
    X1::a = 100; //access static 
    x1.mem1();
    
    EE e;
}

/**************************
 *
 * */ 
#include <iostream>
#include <typeinfo>
struct Base {/** polymorphic type: declares a virtual member */ 
    virtual ~Base() {cout << "call ~Base() "<<endl;} //You should always make your destructors virtual if you’re dealing with inheritance
};
struct Derived : Base {/** polymorphic type: inherits a virtual member */ 
    virtual ~Derived() {cout <<"call ~Derived()" <<endl;}
};
 
struct Base2 {/** non-polymorphic type*/ 
};
struct Derived2 : Base2 {/** non-polymorphic type */ 
};

 
void test_derive()
{
    cout << "\n----- test_derive " <<endl;
    Derived *derived = new Derived();
    Base *base = derived ;
    delete base; //call~derived()&~base(); if destructor not virtual, ~deriver will not called

    Derived obj1; // object1 created with type Derived1
    Derived2 obj2; // object2 created with type Derived2

    Base& b1 = obj1; // b1 refers to the object obj1
    Base2& b2 = obj2; // b2 refers to the object obj2
 
    std::cout << "Expression type of b1: " << typeid(decltype(b1)).name() << ' '
              << "Expression type of b2: " << typeid(decltype(b2)).name() << '\n'
              << "Object type of b1: " << typeid(b1).name() << ' '  /** virtual; derived */ 
              << "Object type of b2: " << typeid(b2).name() << '\n' /** no virtual: base */ 
              << "size of b1: " << sizeof b1 << ' '
              << "size of b2: " << sizeof b2 << '\n';
}

/**************************
 *
 * */ 
class bas{
    public:
    int v;
    virtual const char* get_name(){return "basic"; }
    virtual const char* get_name2(){return "basic"; }
    virtual int get_value() = 0; // a pure virtual function
        //have one pure virtual func, it becomes an abstract base class, &can not be instantiated!!
};
class der final :public bas{ //cannot inherit from final class
    public: 
    const char* get_name(){return "derived"; } // override also virtual  
    const char* get_name2()override final {return "basic"; } //C++11 introduced the override; final :can over any more
    int get_value(){ return v; } // must impliment! 
};
//class derd : der{}; //compile error: cannot derive from ‘final’ class

/** interface */ 
class Interface{ //no member variables, and where all of the functions are pure virtual! 
    virtual int get_value() = 0;
};
/** virtual inherit */ 
class PoweredDevice{};
class Scanner: virtual public PoweredDevice{};
class Printer: virtual public PoweredDevice{}; //use  Virtual base classes 
class Copier: public Scanner, public Printer{};//inherit diamond problem

void test_polymorphy()
{
    cout << "\n----- test_polymorphy " <<endl;
    der d;
    bas &b = d; 
    cout <<"derive get:" << d.get_name() << ";  basic ref get:" << b.get_name() <<endl;
}


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


/********************* 
 *
 * */ 
int main()
{
    /**  */ 
    test_convert();

    /** derive  */ 
    test_derive();

    test_polymorphy();

    
}

