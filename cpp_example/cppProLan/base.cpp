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

    /**  */ 
    f1({1,2,3,5});
    list<double> ld={2.0,33.3,4};
    double dd = sum1(ld,0.0); //
    cout << "temp sum :" << dd << endl ;
    /**  */ 
    int xa = 5;
    const char* pc = "Pedersen";
    printf("the value of x is '%d' and the value of s is '%s'\n",xa,pc);
    char v[5] = "Os0r";
    //abort();
    exit(1);
}
