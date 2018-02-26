#include <iostream>
#include <cassert>
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
//int sumArray(int array[]) // array is a pointer
//int sumArray(int (&array)[]) // pass ref
// tempPtr is now a reference to a pointer, so any changes made to tempPtr will change the argument as well!
void setToNull(int *&tempPtr);
int returnByValue(){return 4;}
int& returnByReference(){
     static int x = 5; /** return ref must not destroy!! */ 
     return x;}


int basic_test()
{
    cout << "************* basic test1. :list init/cout/cin; " << endl;
    using namespace ns_b; 
    int a = 5, b = 6;
    int c(7), d(8);int e{9}, f{10};
    std::cout << "v type:" << typeid(a + b).name()<< endl;
    double vd = 5.0;
    std::cout<<"double size:" << sizeof(vd) << endl;
    using distance_t = double; /** c++11 */ /** typedef double distance_t; */  
    srand(5); // set initial seed value to 5323  only called one time;
    for (int count=0; count < 5; ++count) 
        std::cout << rand() << "\t"; /**  0 and RAND_MAX */ 
    static_assert(sizeof(long) == 8, "long must be 8 bytes"); //while compile

    /** array */ 
    int array[] = { 13, 1, 21, 3, 5, 8, 1, 2 };  // initializer list
    int *array2 = new int[5] { 5, 4, 3, 2, 1 };
    std::cout << "The array has: " << sizeof(array) / sizeof(array[0]) << "elements\n";
    std::sort(array, array+8);
    for(auto i:array){cout << i << " ";} /** c++ 11 */ 

    int ar2d1[2][2] = {{1, 2}, {3, 4}};
    std::array<int, 3> std_ar1 = {1, 2, 3};
    std::string ars[] = {std::string("one"), // copy-initialization
                         "two",              // conversion, then copy-initialization
                         {'t', 'h', 'r', 'e', 'e'} }; // list-initialization
    /** struct list-initialize  */ 
    S_for_init s1 = { 1, { 2, 3, {4, 5, 6} } }; /** only C++11  */ 
    s1 = { 7, { 2, 3, {4, 5, 6} } }; /** only C++11  */ 
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
    enum class Color { red, blue, green }; //strongly typed 
    //Color cx = red; // error :
    Color cz = Color::red; // OK

    //addAndPrint(1.2,1);
    /**  */ 
    int *ptr(NULL); // assign address 0 to ptr
    //doSomething(nullptr); // call doSomething with an argument of type std::nullptr_t
    doSomething(0); // call doSomething with an argument of type std::nullptr_t

    /** print  */ 
    int x = 5;
    const char* pc = "Pedersen";
    printf(" printf test : x is '%d' s is '%s'\n", x,pc);
    char v[5] = "Os0r";

    return 0;
}

void test_pointer_ref(){
    cout << "************* basic test2 : ref/pointer/ " << endl;
    /** Dynamic alloc mem */ 
    int *array = new int[3];
    delete[] array;

    /** const pioint */ 
    int abc = 123;
    const int *ptr_c= const_cast<const int *>(&abc); // cast to const
    //*ptr_c = 23; //error readonly
    const int *ptr_c2 = &abc; // ptr point to const int
    int *p = const_cast<int *>(ptr_c); //remove const
    *p = 10;
    int * const cp2 = p; // here the static_cast is optional
    cout << "change throw ptr: "<< abc << "\n";

    /** pointer */
    //constexpr int *ptrc= &abc;
    const int valc = 5;  int val1=1; int val2 = 2;
    int *ptr = &val2;
    int **ptrptr = &ptr;
    const int *ptr_c1 = &valc; // okay, ptr pointing to a "const int"

    ptr_c1 = &val2; // ok too, but    *ptr_c1 = 12; error
    //int *const c_ptr = &value; //error; is a const ptr
    std::cout << "ptr:" << **ptrptr <<endl; // dereference pointer to int to get int value
    int **arr_p = new int*[10]; // allocate an array of 10 int pointers
    arr_p[2] = new int[5]{1,2,3,4,5}; 
    cout << "array pointer val: " << arr_p[2][3] <<endl; //4
    int (*fcnPtr)() = returnByValue; // assign fcnPtr to function foo
    (*fcnPtr)(); // call function foo(5) through fcnPtr.


    /** reference */ 
    const int &ref = valc; // ref is a reference to const value;  = val2; =5;(r-value) //ok
    //ref = 10;  // error ; read only
    //int &invalidRef; //error must init;
    int &ref1 = val2; //ok ;  = valc;error ref to non const
    ref1 = val1; /** only: val2=1; can not be changed to reference another variable  */ 
    std::cout << "ref val2:" << val2 <<endl; // dereference pointer to int to get int value
    
    /** l-value reference */ 
    int x; 	int &ref2 = x; // ok
	//int &ref3 = 5; // error  can't from an rvalue
	const int &refc1 = x; // C
	const int &refc2 = 5; // D
    //int &ref2 = returnByValue(); //error ; r-value  can't bind to a non-const reference
    int &ref4 = returnByReference(); //ok
    const int &refc3 = returnByReference(); // ok
    int rvalue = returnByReference();

    assert(returnByReference()>0 && "Car could not be found in database");
    /** r-value */ 
    int n = 1;  const int xc= 12;
    double&& copy_ref = n; // bind to an rvalue temporary with value 1.0
	//int &&rref1 = x; // error can't from lvalue to 
	int &&rref2 = 5; // 
	//const int &&rrefc1 = x; // error  can't lvalue to ‘const int&&’
	//const int &&rrefc2 = xc; // error  can't lvalue to ‘const int&&’
	const int &&rrefc3 = 5; // 
    
}

void test_lambda_func()
{
    cout << "************* lambda test. :lambda " << endl;
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



/********************* 
 *
 * */ 
int main(int argc, char *argv[])
{
    /**  */ 
    basic_test();
    /**  */ 
    test_pointer_ref();
    /**  */
    test_lambda_func();

    //abort();
    if (argc ==0){
        cout << "no args\n";
    }else if(argc == 2){
        cout << "cmd:" << argv[0] <<"args:"<< argv[1] <<endl;}
    exit(1);
}
