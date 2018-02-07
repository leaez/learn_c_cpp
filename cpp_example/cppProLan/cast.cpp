#include <iostream>
using namespace std;
struct V {
    virtual void f() {};  // must be polymorphic to use runtime-checked dynamic_cast
};
struct A : virtual V {};
struct B : virtual V {
  B(V* v, A* a) {
    // casts during construction (see the call in the constructor of D below)
    dynamic_cast<B*>(v); // well-defined: v of type V*, V base of B, results in B*
    dynamic_cast<B*>(a); // undefined behavior: a has type A*, A not a base of B
  }
};
struct D : A, B {
    D() : B((A*)this, this) { }
};

struct Base {
    static int a;
    virtual void name() {cout << "base name;" <<endl;}
    virtual ~Base() {}
};

struct Derived: Base {
    void name() {cout << "derived name;" <<endl;}
};
 
int Base::a = 10;

cast_test(){
    int i1 = 10;int i2 = 4;
    float f = (float)i1 / i2;/** C-style casts */ 
    float f = float(i1) / i2;

    int i = 48; char ch = static_cast<char>(i);
}

int main()
{
    D d; // the most derived object
    A& a = d; // upcast, dynamic_cast may be used, but unnecessary
    D& new_d = dynamic_cast<D&>(a); // downcast
    B& new_b = dynamic_cast<B&>(a); // sidecast
 
 
    Base* b1 = new Base;
    Derived* dd = static_cast<Derived*>(b1);
    dd->name(); // base的
    //Derived* dd = dynamic_cast<Derived*>(b1);
    //dd->name(); //这样直接调用，会运行错误的

    if(Derived* d = dynamic_cast<Derived*>(b1)) // d变成 空， 失败了
    {
        std::cout << "downcast from b1 to d successful\n";
        d->name(); // safe to call 调用的是deriver的
    }
 
    Base* b2 = new Derived;
    if(Derived* d = dynamic_cast<Derived*>(b2))  /** 只有base指针直到 derived 才是安全了 */ 
    {
        std::cout << "downcast from b2 to d successful\n";
        d->name(); // safe to call
        d->a = 11;
        std::cout <<  d->a << "\n";
    }
 
    delete b1;
    delete b2;
}
