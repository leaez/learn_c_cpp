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

struct C
{
    int n;
    std::string s1;
    // user-defined copy assignment, copy-and-swap form
    C& operator=(C other)  {
        std::cout << "copy assignment C\n";
        std::swap(n, other.n);
        std::swap(s1, other.s1);
        return *this;
    }
}; /** 如果有pointer，use deep copy; std::copy() */ 


void test_class(){
    /**  */ 
    Point p1(1,2);
    Point p2(p1);
    Point p3 = p2;
    if(p1 == p3)
        cout << p1 <<" []operator :" << p1[2] <<endl;
    

}

void test_constructor(){
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

}


int main(int argc, char* argv[])
{
    test_class();

    test_constructor();



    return 0;
}
