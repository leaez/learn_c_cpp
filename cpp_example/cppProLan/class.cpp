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
#include <cstring>

using namespace std;
//using namespace boost; 

class clist{
    private: int a,b,c;
    public:    
        static int s_value;
    //clist(){a=2;b=3; c=4;} /** user-defined default ctor */
    clist():a(2),b(3),c(4){} /** user-defined default ctor */
    clist(int aa =1){a =aa;} /** user-defined default ctor;delegate/ might ambiguous!! */ 
    clist(int aa,int bb):clist(10){a =aa;} /** user-defined default ctor;delegate/ might ambiguous!! */ 
};
int clist::s_value = 23;

struct A
{
    std::string s;
    A() : s("test") { 
        std::cout << " user-defined default ctor!\n"; }
    A(const A& o) : s(o.s) { 
        std::cout << " user-defined copy ctor!\n"; }
    //A(A&& o) : s(std::move(o.s)) { }
    A& operator=(const A& other)  {/**  */ 
         s = other.s;
         std::cout << "copy assigned\n";
         return *this;
    }
    A& operator=(A&& other)   { /**  */ 
         s = std::move(other.s);
         std::cout << "move assigned\n";
         return *this;
    }
};

class Point{
private:
    double m_x, m_y;
    char *name;
public:
    explicit Point(double x=0.0, double y=0.0 ): m_x(x), m_y(y) {
        name = new char[10]; strcpy(name, "I'm point"); name[9] = '\0';} /** default cnstr */ 
    Point(double) = delete; /**  */ 
    /** deep copy: use containner!! like std::vector(self mem manage), not self implement deep copy   */ 
    Point& operator= (const Point &point){ /** assign cnstr / use deep copy */ 
        if (this == &point)  return *this; /** check for self-assignment  */ 
        m_x=(point.m_x); m_y=(point.m_y);
        if(point.name){name = new char[10]; 
            strcpy(name,point.name); name[9] = '\n';}
        return *this;  
    } 
    Point(const Point& p1){/** copy cnstr */
        m_x = p1.m_x; m_y = p1.m_y; 
        if(p1.name){name = new char[10]; 
            strcpy(name,p1.name); name[9] = '\n';}
    } 
    Point operator- () const{
        return Point(-m_x, -m_y );}
    bool operator== (const Point &p1){ /** must only one args */ 
        return ( this->m_x == p1.m_x && p1.m_y == this->m_y );
    }
    Point& operator++(){ /**  unary operators */ 
        this->m_x++; this->m_y++; return *this; /** return self */ 
    }
    double& operator[] (int index){ /**  */ 
        m_x+=index;return m_x;
    }
    double& operator() (int a, int b){ /** just like function; but can stored member var */ 
        m_x=m_y+a+b; return m_x;
    }

    ~Point(){ // destructor
        delete[] name; 
        cout << "Point destroy \n";
    }
    friend std::ostream& operator<< (std::ostream &out, const Point &point);
};
 
std::ostream& operator<< (std::ostream &out, const Point &point){
    out <<"Point:"<< point.name << "(" << point.m_x << ", " << point.m_y << " " << ")";
    return out;
}



A f(A a){ return a;}

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

void cast_test(){
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

}



int main(int argc, char* argv[])
{
    /**  */ 
    Point p1(1,2);
    Point p2(p1);
    Point p3 = p2;
    if(p1 == p3)
        cout << p1 <<" []operator :" << p1[2] <<endl;


   /**  */
    //clist aa{1,2,3}; //only no use-defined constr
    clist cl(2);

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

    cast_test();


    return 0;
}
