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
using std::cout; // tell the compiler that cout means std::cout

/**  */ 
template<typename Container, typename Value> 
    Value sum(const Container& c, Value v)
{  for (auto x : c) v+=x;
    return v;
}
/** 可变长参数  */ 
template<typename T> void g(T x) { cout << x << " "; }
void func_arg_var() { cout << endl; } // do nothing
template<typename T, typename... Tail> void func_arg_var(T head, Tail... tail){ //...indicate the rest
    g(head); /*  do something to head */ 
    func_arg_var(tail...); }// try again with tail

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

void template_test()
{
    cout << "************* template test. " << endl;
    vector<int> va{1,2,3};
    int su;
    su= sum(va,0);
    cout << "get sum:" << su <<endl;

    /** 可变长参数 */ 
    func_arg_var(0.2,'c',"yuck!",0,1,2);

    /** template auto 推到  */ 
    f1({1,2,3,5});
    list<double> ld={2.0,33.3,4};
    double dd = sum1(ld,0.0); // auto deduce
    cout << "temp sum :" << dd << endl ;


}

struct S_for_init {
    int x;
    struct Foo {
        int i;
        int j;
        int a[3];
    } b;
};
enum Animal{
    ANIMAL_CAT = -3, ANIMAL_DOG,/** assigned -2 */ 
    ANIMAL_HORSE = 5,  ANIMAL_GIRAFFE = 5, /** shares same value as ANIMAL_HORSE */
    ANIMAL_CHICKEN /**  assigned 6 */ };
void enum_t(Animal a){
    switch(a){case ANIMAL_CAT: cout << a;default:;} cout <<" is enum value"<<endl; }

constexpr double getX() {return 123;} /** for efficient, compiler can decide const,then do it */  
namespace ns_b{ int x(20);}

void doSomething(std::nullptr_t ptr){ std::cout << "in doSomething()\n";}
//void addAndPrint(auto x, auto y){    std::cout << x + y;}

int basic_test()
{
    cout << "************* basic: list init; cout/cin;  . " << endl;
    using namespace ns_b; 
    int a = 5, b = 6;int c(7), d(8);int e{9}, f{10};
    std::cout << "v type:" << typeid(a + b).name()<< endl;
    double vd = 5.0;
    std::cout<<"double size:" << sizeof(vd) << endl;

    /** array */ 
    int array[] = { 13, 1, 21, 3, 5, 8, 1, 2 };
    std::cout << "The array has: " << sizeof(array) / sizeof(array[0]) << "elements\n";
    for(auto i:array){cout << i << " ";}
    std::sort(array, array+7);

    int ar2d1[2][2] = {{1, 2}, {3, 4}};
    std::array<int, 3> std_ar1 = {1, 2, 3};
    std::string ars[] = {std::string("one"), // copy-initialization
                         "two",              // conversion, then copy-initialization
                         {'t', 'h', 'r', 'e', 'e'} }; // list-initialization
    /** list-initialize  */ 
    S_for_init s1 = { 1, { 2, 3, {4, 5, 6} } }; /** only C++11  */ 
    S_for_init s2 = { 1, 2, 3, 4, 5, 6}; // same, but with brace elision
    S_for_init s3{1, {2, 3, {4, 5, 6} } }; // same, using direct-list-initialization syntax
    S_for_init s4{1, 2, 3, 4, 5, 6}; // error in C++11: brace-elision only allowed with equals sign
                            // okay in C++14
    constexpr int mf = 20;        //ok
    constexpr int limit = mf + 1; //ok compiler check if const
    const int consta = mf-1; /** ok */ 

    cout << " cin key input : (y or n)?\n"; // write question
    char answer = 0;
    //cin >> answer; // read answer
    switch (answer) {
        case 'y':;  cout << "you input y";   //return true;
        case 'n':;  cout << "you input n";   //return true;
        default:;
    }
    /*
    std::cout << "Enter your full name: ";    std::string name;
    std::getline(std::cin, name);
    double d1; cin >> d1;
    cout << "get double v:" << d1 <<endl;
    if (std::cin.fail()) cout << "input inalid" <<endl;
*/
    /** enum */ 
    enum_t(ANIMAL_CAT);

    //addAndPrint(1.2,1);
    /**  */ 
    int *ptr(NULL); // assign address 0 to ptr
    //doSomething(nullptr); // call doSomething with an argument of type std::nullptr_t
    doSomething(0); // call doSomething with an argument of type std::nullptr_t

    /** reference  */ 
    int n = 20;
    int& r1 = n;  // lvalue reference to the object n
    int&& rref = 1; // bound to rvalue

    std::vector<int> vl = {1, 2, 3, 4, 5, 6, 7};
    for(const int &i : vl) // access by const reference
        std::cout << i << ' ';
    for(int n: {0, 1, 2, 3, 4, 5}){
        cout << n ; }
        cout <<endl;

    /** print  */ 
    int x = 5;
    const char* pc = "Pedersen";
    printf(" printf test : x is '%d' s is '%s'\n", x,pc);
    char v[5] = "Os0r";

    return 0;
}

void lambda_func_test()
{
    cout << "************* lambda test. " << endl;
    /** lambda, function  */ 
    auto glambda = [](int a, int b) { return a < b; }; 
    bool b = glambda(3, 4); /** func name */ 

    int x = 5;
    std::vector<int> c = {1, 2, 3, 4, 5, 6, 7};
    c.erase(std::remove_if(c.begin(), c.end(), [x](int n) {return n < x; }), /**lambda as judge  */ 
            c.end());
    std::for_each(c.begin(), c.end(), [](int i){ 
        std::cout << i<< ' '; });
    std::cout << '\n';
    std::function<int(int)> func2 = [](int i) { /** lambda to func name */ 
        return i + 4; };
    std::cout << "lambda func2: " << func2(6) << '\n';

    /** lamada  */ 
    double (*fp1)(double) = [](double a) { return sqrt(a); };
    double (*fp2)(double) = [&](double a) { return sqrt(a); }; //  : the lambda captures
    //double (*fp3)(int) = [](int a) { return sqrt(a); }; //  
    auto fp3 = [](int a) { return sqrt(a); }; // 
    cout << "lamada func: " <<  fp3(2.2) <<endl;
    int y = 10;
    auto fz1 = [=](int su){ if (su) return su; else return 2; };
    cout << "lamada func: " <<  fz1(12) <<endl;
}

void exception_test(){
    /** exception  */ 
    struct Some_error { };
    try{ throw Some_error{};
    }catch(Some_error){
        cout << "catch some exception!\n";
    }
}

/********************* 
 *
 * */ 
int main()
{
    /**  */ 
    basic_test();
    /**  */
    lambda_func_test();

    /**  */ 
    exception_test();
    //abort();
    exit(1);
}
