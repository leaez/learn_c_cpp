#include <iostream>
#include <array>
#include <map>
#include <tuple>
#include <vector>
#include <list>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <initializer_list>

//#include <stdio>

using namespace std;

/** vector */ 
bool accept3()
{
    cout << "Do you want to proceed (y or n)?\n"; // write question
    char answer = 0;
    //cin >> answer; // read answer
    switch (answer) {
        case 'y':;
                 //return true;
        case 'n':;
                 //return false;
        default:;
    }
    /**  */ 
    int v[] = {0,1,2,3,4,5,6,7,8,9};
    for (auto x : v) // for each x in v
        cout << x << '\n';

    enum class Color { red, blue, green }; //strongly typed 
    //Color cx = red; // error :
    Color cz = Color::red; // OK

    vector<int> z{1000,22};
    vector<int> x{222,333};
    vector<int> y0{444,555};

    z = x; // we get a copy
    //y0 = std::move(x); // we get a move
    cout << x[0] << endl;
   
    return false;
}

template<typename Container, typename Value> 
    Value sum(const Container& c, Value v)
{  for (auto x : c) v+=x;
    return v;
}

/** 可变长参数  */ 
template<typename T> void g(T x) { cout << x << " "; }
void f() { cout << endl; } // do nothing
template<typename T, typename... Tail> void f(T head, Tail... tail){ //...indicate the rest
    g(head); /*  do something to head */ 
    f(tail...); }// try again with tail

void f1(initializer_list<int> args)
{
    for (int i = 0; i!=args.size(); ++i)
        cout << args.begin()[i] << "\n";
}

template<typename Container, typename Value> Value sum1(const Container& c, Value v)
{for (auto x : c) 
    v+=x; 
    return v;
}

struct S {
    int x;
    struct Foo {
        int i;
        int j;
        int a[3];
    } b;
};

int test1()
{
    S s1 = { 1, { 2, 3, {4, 5, 6} } };
    S s2 = { 1, 2, 3, 4, 5, 6}; // same, but with brace elision
    S s3{1, {2, 3, {4, 5, 6} } }; // same, using direct-list-initialization syntax
    S s4{1, 2, 3, 4, 5, 6}; // error in C++11: brace-elision only allowed with equals sign
                            // okay in C++14

    int ar2d1[2][2] = {{1, 2}, {3, 4}};
    std::array<int, 3> std_ar1 = {1, 2, 3};
    std::string ars[] = {std::string("one"), // copy-initialization
                         "two",              // conversion, then copy-initialization
                         {'t', 'h', 'r', 'e', 'e'} }; // list-initialization
    /** reference  */ 
    int n = 20;
    int& r1 = n;  // lvalue reference to the object n
    
    int&& rref = 1; // bound to rvalue

    /** lambda, function  */ 
    auto glambda = [](int a, int b) { return a < b; };
    bool b = glambda(3, 3.14); // ok
    std::vector<int> c = {1, 2, 3, 4, 5, 6, 7};
    int x = 5;
    c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; }), c.end());
    std::for_each(c.begin(), c.end(), [](int i){ std::cout << i<< ' '; });
    std::cout << '\n';
    std::function<int(int)> func2 = [](int i) { return i + 4; };
    std::cout << "func2: " << func2(6) << '\n';

    /**  */ 
    for(const int &i : c) // access by const reference
        std::cout << i << ' ';
    for(int n: {0, 1, 2, 3, 4, 5})


    return 0;
}


/********************* 
 *
 * */ 
int main()
{
    accept3();
    vector<int> va{1,2,3};
    int su;
    su= sum(va,0);
    cout << "get sum:" << su <<endl;

    /** 可变长参数 */ 
    f(0.2,'c',"yuck!",0,1,2);

    /** strign  */ 
    string name = "Niels Stroustrup";
    string s = name.substr(6,10); // s = "Stroustrup"
    name.replace(0,5,"nicholas"); // name becomes "nicholas Stroustrup"
    name[0] = toupper(name[0]); // name becomes "Nicholas Stroustrup
    cout << name << endl;

    /** vectro */ 
    vector<int> v1 = {1, 2, 3, 4};
    vector<string> v2;
    cout << v1[1] << endl;

    /** lamada  */ 
    double (*fp1)(double) = [](double a) { return sqrt(a); };
    double (*fp2)(double) = [&](double a) { return sqrt(a); }; //  : the lambda captures
    //double (*fp3)(int) = [](int a) { return sqrt(a); }; //  
    auto fp3 = [](int a) { return sqrt(a); }; // 
    cout << "lamada" <<  fp3(2.2) <<endl;
    int y = 10;
    auto fz1 = [=](int su){ if (su) return su; else return 2; };
    cout << "lamada" <<  fz1(12) <<endl;

    /** cast  */ 
    char x = 'a';
    //int* p1 = &x; // error : no implicit char* to int* conversion
    //int* p2 = static_cast<int*>(&x); // error : no implicit char* to int* conversion
    int* p3 = reinterpret_cast<int*>(&x); // OK: on your head be it
    struct B { /* ... */ };
    struct D : B { /* ... */ }; // see §3.2.2 and §20.5.2
    B* pb = new D; // OK: implicit conversion from D* to B*
    //D* pd0 = pb; // error : no implicit conversion from B* to D*
    D* pd1 = static_cast<D*>(pb); // OK
    /** exception  */ 
    struct Some_error { };
    try{ throw Some_error{};
    }catch(Some_error){
        cout << "exception!\n";
    }

    /** template auto 推到  */ 
    f1({1,2,3,5});
    list<double> ld={2.0,33.3,4};
    double dd = sum1(ld,0.0); // auto deduce
    cout << "temp sum :" << dd << endl ;

    /** print  */ 
    int xa = 5;
    const char* pc = "Pedersen";
    printf("the value of x is '%d' and the value of s is '%s'\n",xa,pc);
    char v[5] = "Os0r";

    /**  */ 
    test1();
    /**  */ 
    //abort();
    exit(1);
}
