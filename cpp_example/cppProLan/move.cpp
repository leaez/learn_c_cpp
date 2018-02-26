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
#include <memory> // for std::unique_ptr


using namespace std;
//using namespace boost; 


/** default constructor，  */ 
struct A{
    string s;
    A() : s("test move copy constr") { }
    A(const A& o) : s(o.s) { /** copy constr */ 
        cout << "copy cons!\n"; }
    A(A&& o) : s(move(o.s)){ /** move constr */ 
        cout << "move cons!\n"; }
    A& operator=(const A& other){ //copy assigned
         s = other.s;
         cout << "copy assigned\n";
         return *this;
    }
    A& operator=(A&& other) { /** move assigned */ 
         s = move(other.s);
         cout << "move assigned\n";
         return *this;
    }
};


A f(A a){
    return a;}

struct B : A {
     string s2; 
     int n;    
    // implicit move constructor B::(B&&)
};

struct C : B{
    int n;
    string s1;
    // user-defined copy assignment, copy-and-swap form
    C& operator=(C other)
    {  cout << "copy assignment C\n";
        swap(n, other.n);
        swap(s1, other.s1);
        return *this;
    }
    //~C() { } // destructor prevents implicit move assignment
};
 
struct D : B{
    D() { }
    ~D() { } // destructor would prevent implicit move assignment
    D& operator=(D&&) = default; // force a move assignment anyway 
};

void test_move(){
    cout <<endl;
   /** move constructor */ 
    A a1, a2;
    cout << "----a = f(A()):" <<endl;
    a1 = f(A()); // call move-construct to f()'s parameter(rvalue temporary); if no move constr,call copy constr
        //f() return rvalue temporary && ,will call move assigned , move to a1
    
    cout << "----a = move():"<<endl;
    a2 = move(a1); // move-assignment from xvalue, if no move assignment,call A(const A&) copy constr

    cout << "----A a = move():"<<endl;
    A a3 = move(a1); // move-construct from xvalue,if no move constructor, call A(const A&) copy constr

    B b1, b2;
    cout << "----b = move():" <<endl;
    b2 = move(b1); // calls implicit move constr, if no move constructor,call A(const A&)copy constr 
    C c1, c2;
    //c1 = c2;  // user-defined copy assignment
    cout << "----c = move():" <<endl;
    c1 = move(c2);

    cout << "----Trying to move-assign D\n";
    D d1, d2;
    d2 = move(d1);


}

/** 
 *
 * */ 
void test_std_copymove(){
    cout <<endl;
    /** copy algorithm */ 
    vector<string> foo = {"air","water","fire","earth"};
    vector<string> bar (4);
    copy(foo.begin(), foo.begin()+4,  back_inserter(bar));
    // moving ranges:
    cout << "----Moving ranges size "<< bar.size() <<"\n";
    move (foo.begin(), foo.begin()+4, bar.begin() );
    for(auto x: bar){cout << x << "/ ";}
    cout << "\n";

}


/************************
 * */ 

template<class T>
void swap1(T& a, T& b) { 
  T tmp { std::move(a) }; // move constructor
  a = std::move(b); // move assignment
  b = std::move(tmp); // move assignment
}
 
void test_swap_move(){
    cout <<endl;
	std::string x{ "aaa"};	std::string y{ "bbb"};
 	std::cout << "x: " << x <<  ";  y: " << y << '\n';
	swap1(x, y);
 	std::cout << "x: " << x <<  ";  y: " << y << '\n';
}

/***********************
 *
 * */ 
class Resource{
public:	Resource() { std::cout << "Resource acquired\n"; }
    void print(){cout << "I am a res." <<endl;}
	~Resource() { std::cout << "Resource destroyed\n"; }
};
 
void test_smart_ptr(){
    cout <<endl;
    /** unique_ptr */ 
	std::unique_ptr<Resource> res1(new Resource); // Resource created here
	std::unique_ptr<Resource> res2; // Start as nullptr
 	std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n");
	std::cout << "res2 is " << (static_cast<bool>(res2) ? "not null\n" : "null\n");
 	// res2 = res1; // Won't compile: copy assignment is disabled
	res2 = std::move(res1); // res2 assumes ownership, res1 is set to null
 	std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n");
	std::cout << "res2 is " << (static_cast<bool>(res2) ? "not null\n" : "null\n");

    /** shared_ptr */ 
    Resource *res = new Resource;
	std::shared_ptr<Resource> ptr1(res);
	{	std::shared_ptr<Resource> ptr2(ptr1); // use copy initialization std::shared_ptr point to the same res
	} // ptr2 goes out of scope 
} 



int main(int argc, char* argv[])
{
    /**  */ 
    test_move();
    /**  */ 
    test_std_copymove();
    /**  */ 
    test_swap_move();
    /**  */ 
    test_smart_ptr();
    return 0;
}

