#include <iostream>
using namespace std;

struct V {
    virtual void f() {};  // must be polymorphic to use runtime-checked dynamic_cast
};

struct BB : virtual V {};
struct B : virtual V {
  B(V* v, BB* bb) {
    // casts during construction (see the call in the constructor of D below)
    dynamic_cast<B*>(v); // well-defined: v of type V*, V base of B, results in B*
    dynamic_cast<B*>(bb); // undefined behavior: bb has type BB*, BB not a base of B
  }
};
struct D : BB, B {
    D() : B((BB*)this, this) { }
};

struct Base {
    static int a;
    virtual void name() {cout << "base name called;" <<endl;}
    virtual ~Base() {cout << "base destructor called;" <<endl;} //should always virtual if use inherit 
};
struct Derived: Base {
    void name() {cout << "derived name called;" <<endl;}
    virtual ~Derived() {cout << "Derived destructor called;" <<endl;}
};
int Base::a = 10;


class Base1{
public:
    virtual ~Base1(){};
};
class Derived1 : public Base1{
    char c;
public:
    virtual void get_name() {cout << "derived name;" <<endl;}
    virtual ~Derived1(){};
};
class Derived2 : public Base1{
    long l;
public:
    virtual ~Derived2(){};
};

void test_static_cast(){
    cout << "----- test_dynamic_cast " <<endl;

    int i1 = 10;int i2 = 4;
    float f = (float)i1 / i2;/** C-style casts */ 
    float f1 = float(i1) / i2;

    int i = 48; char ch = static_cast<char>(i);

    char c = 10;       // 1 byte
    int *p = (int*)&c; //ok, 4 bytes  ; ‘char*’ to type ‘int*’
//    int *q = static_cast<int*>(&c); // compile-time error, can't ‘char*’ to type ‘int*’

        /** cast  */ 
    char x = 'a';
    //int* p1 = &x; // error : no implicit char* to int* conversion
    //int* p2 = static_cast<int*>(&x); // error :(do check) no implicit char* to int* conversion
    int* p3 = reinterpret_cast<int*>(&x); // OK: on your head be it
    struct B { /* ... */ };
    struct D : B { /* ... */ }; // see §3.2.2 and §20.5.2
    B* pb = new D; // OK: implicit conversion from D* to B*
    //D* pd0 = pb; // error : no implicit conversion from B* to D*
    D* pd1 = static_cast<D*>(pb); // OK


}

/**  allows for a typesafe downcast.
 *
 * */ 

void test_dynamic_cast(){
    cout << "\n----- test_dynamic_cast " <<endl;
    D d; // the most derived object
    BB& bb = d; // upcast, dynamic_cast may be used, but unnecessary
    D& new_d = dynamic_cast<D&>(bb); // downcast
    B& new_b = dynamic_cast<B&>(bb); // sidecast
 
    Base* b1 = new Base;
    Derived* dd = static_cast<Derived*>(b1);
    dd->name(); // base的
    //Derived* dd = dynamic_cast<Derived*>(b1);
    //dd->name(); //这样直接调用，会运行错误的

    if(Derived* d = dynamic_cast<Derived*>(b1)){ // d变成 空， 失败了
        std::cout << "downcast from b1(point to base) to d successful\n";
        d->name(); // safe to call; call to deriver func
    }
 
    Base* b2 = new Derived;
    if(Derived* d = dynamic_cast<Derived*>(b2)) { /** 只有base指针直到 derived 才是安全了 */ 
        std::cout << "downcast from b2(point to derive) to d successful\n";
        d->name(); // safe to call
        d->a = 11;
        std::cout <<  d->a << "\n";
    }
    cout << "now destroy!" <<endl; 
    delete b1;
    delete b2; // because destructor virtual, both derived/base destructor called , or will not!

    /**  dynamic cast for pointer  
     * dynamic_cast, it just gives us the ability to check the validity of the cast,
     * whereas using static_cast can't know  whether it will succeed or not.  */ 
    Derived1* d1 = new Derived1;
    Base1* b2b = new Base1;
    Base1* b2d = d1;  // upcast is ok because Derived1 is a Base.
//    Derived1* x1 = b2d;  //error: downcast is unsafe and fails.
//    Derived2* x2 = b2d;  //error: downcast is unsafe and fails. 
    Derived1* xx1 = static_cast<Derived1*>(b2b);  // ok,but downcast is unsafe,
    //xx1->get_name(); // error !!! undefinde!
    xx1 = static_cast<Derived1*>(b2d);  // ok,though downcast is unsafe, 
    xx1->get_name();
//    Derived2* xx2 = static_cast<Derived2*>(d1);  //error, can't Derived1* to Derived2* 
    //uses RuntTime Type Info (RTTI) to determine if the cast is valid.
    Derived1* xxx1 = dynamic_cast<Derived1*>(b2d);  //ok, xxx1 is d1
    Derived2* xxx2 = dynamic_cast<Derived2*>(d1);  //ok, but  xxx2  == nullptr
    if (xxx1 == nullptr){
        cout << "1. dynamic_cast get null" <<endl;}
    if (xxx2 == nullptr){
        cout << "2. dynamic_cast get null" <<endl;}
    /**  dynamic_cast for reference */ 
    Base blue;
    Derived red;
    Base &b1_r = blue; // set base reference to object
    Base &b2_r = red; // set base reference to object
	//Derived &d1_r = dynamic_cast<Derived&>(b1_r); //!!!std::bad_cast;  dynamic cast for reference instead of a pointer
	Derived &d2_r = dynamic_cast<Derived&>(b2_r); //ok 

}


int main()
{
    /**  */  
    test_static_cast();
    /**  */ 
    test_dynamic_cast();

 
}
