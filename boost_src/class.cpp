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
    A(const A& o) : s(o.s) { std::cout << "move failed!\n"; }
    //A(A&& o) : s(std::move(o.s)) { }
    A& operator=(const A& other)
    {
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
    // implicit move constructor B::(B&&)
};

    template< class T > void g(T);    // #1: overload for all types
    template<>          void g(int*); // #2: specialization of #1 for pointers to int
    template< class T > void g(T*);   // #3: overload for all pointer types

    template<void (*pf)(int)> struct AF {};
template<int (pa)[5]> struct W {};
template<const char*> struct S2 {};

struct C
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
}; /** 如果有pointer，use deep copy; std::copy() */ 


int main(int argc, char* argv[])
{
   /**  */ 
    A a1 = f(A()); // move-construct from rvalue temporary
    A a2 = std::move(a1); // move-construct from xvalue

    A a3 = std::move(a1); // move-assignment from xvalue

    B b1;
    B b2 = std::move(b1); // calls implicit move ctor

    C c1, c2;
    c1 = c2;  // user-defined copy assignment

    /** template  */ 
    const int bt[5] = {1, 3 ,3, 4, 4};
    //W<bt> w; //error : no conversion
    
    //S2<"fail"> s2; // error: string literal cannot be used
    //char okay[] = "okay"; // static object with linkage
    //S2< &okay[0] > s2; // error: array element has no linkage
    //S2<okay> s2; // error

    //f(new int(1)); // calls #3, even though specialization of #1 would be a perfect match

    return 0;
}
