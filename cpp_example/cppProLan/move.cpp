#include <iostream>
#include <array>
#include <map>
#include <tuple>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <utility>
#include <string>


using namespace std;
//using namespace boost; 


/** default constructor，  */ 
/*
struct A
{
    int x;
    A(int x = 1): x(x) {} // user-defined default constructor
    //A() 该constr is not declared because another constructor exists
    A(const A& a) : x(a.x) { } // user-defined copy ctor
    //A(A&& o) noexcept : x(std::move(o.x)) { cout << "move constr called \n"; }
    A& operator=(A&& other) {   //"move assigned\n";
        cout <<"move assigned\n";
         x = std::move(other.x);
         return *this;
    }
};
*/
struct A
{
    std::string s;
    A() : s("test") { }
    A(const A& o) : s(o.s) { std::cout << "copy cons!\n"; }
    A(A&& o) : s(std::move(o.s)){ std::cout << "move cons!\n"; }
    A& operator=(const A& other){
         s = other.s;
         std::cout << "copy assigned\n";
         return *this;
    }

    A& operator=(A&& other)
    {
         s = std::move(other.s);
         std::cout << "move assigned\n";
         return *this;
    }
};


A f(A a){    return a;}

struct B : A {
     std::string s2; 
     int n;    
    // implicit move constructor B::(B&&)
};

template< class T > void g(T);    // #1: overload for all types
template<>          void g(int*); // #2: specialization of #1 for pointers to int
template< class T > void g(T*);   // #3: overload for all pointer types

template<void (*pf)(int)> struct AF {};
template<int (pa)[5]> struct W {};
template<const char*> struct S2 {};

struct C22
{
    int n;
    std::string s1;
    // user-defined copy assignment, copy-and-swap form
    C22& operator=(C22 other)
    {  std::cout << "copy assignment C\n";
        std::swap(n, other.n);
        std::swap(s1, other.s1);
        return *this;
    }
}; /** 如果有pointer，use deep copy; std::copy() */ 

struct C : B
{
    int n;
    std::string s1;
    // user-defined copy assignment, copy-and-swap form
    C& operator=(C other)
    {  std::cout << "copy assignment C\n";
        std::swap(n, other.n);
        std::swap(s1, other.s1);
        return *this;
    }
    ~C() { } // destructor prevents implicit move assignment
};
 
struct D : B
{
    D() { }
    ~D() { } // destructor would prevent implicit move assignment
    D& operator=(D&&) = default; // force a move assignment anyway 
};
int main(int argc, char* argv[])
{
   /** move constructor */ 
    A a1, a2;
    cout << "a = f(A()):";
    a1 = f(A()); // call move-construct from rvalue temporary; 如果move constructor没有就 调用A(const A&)拷贝构造函数 的move-construct from rvalue temporary
    cout << "a = move():";
    a2 = std::move(a1); // move-construct from xvalue如果move constructor没有就 调用A(const A&)拷贝构造函数 

    cout << "A a = move():";
    A a3 = std::move(a1); // move-assignment from xvalue如果move constructor没有就 调用A(const A&)拷贝构造函数 

    B b1, b2;
    cout << "b = move():";
    b2 = std::move(b1); // calls implicit move ctor如果move constructor没有就 调用A(const A&)拷贝构造函数 

    C c1, c2;
    //c1 = c2;  // user-defined copy assignment
    cout << "c = move():";
    c1 = std::move(c2);

    std::cout << "Trying to move-assign D\n";
    D d1, d2;
    d2 = std::move(d1);

    /** template  */ 
    const int bt[5] = {1, 3 ,3, 4, 4};
    //W<bt> w; //error : no conversion
    
    //S2<"fail"> s2; // error: string literal cannot be used
    //char okay[] = "okay"; // static object with linkage
    //S2< &okay[0] > s2; // error: array element has no linkage
    //S2<okay> s2; // error

    //f(new int(1)); // calls #3, even though specialization of #1 would be a perfect match

    /** move algorithm */ 
    std::vector<std::string> foo = {"air","water","fire","earth"};
    std::vector<std::string> bar (4);
    
    std::copy(foo.begin(), foo.begin()+4,  back_inserter(bar));
    
    // moving ranges:
    std::cout << "Moving ranges..."<< bar.size() <<"\n";
    std::move ( foo.begin(), foo.begin()+4, bar.begin() );

    for(auto x: bar){cout << x << " ";}
    std::cout << "\n";


    
    return 0;
}

