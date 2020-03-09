#include <iostream>
#include <cassert>
#include <cmath>
#include <array>
#include <map>
#include <tuple>
#include <vector>
#include <list>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <initializer_list>


using namespace std;
using std::cout; // tell the compiler that cout means std::cout
#define MARK (cout << "--------------" <<'('<<__LINE__<<')' << '<' << __FUNCTION__ << '>' <<endl) 

#define printx(x) cout << #x " = " << int{x} << '\n'; 


/**  */ 
class X1 {
  X1(int); // ‘‘ordinar y constructor’’: create an object
  X1(); // default constructor
  X1(const X1&); // copy constr uctor
  X1(X1&&); // move constructor
  X1& operator=(const X1&); // copy assignment: clean up target and copy
  X1& operator=(X1&&); // move assignment: clean up target and move
  ~X1(); // destructor: clean up
  // ...
};

struct X { int a;
  X(int i){a=i; }; 
};

void f(initializer_list<int> args)
{
  for (auto x : args) cout << x << "\n";
}

void test_constructor()
{
  //X x0; // error : no initializer
  //X x1 {}; // error : empty initializer
  X x2 {2}; // OK
  //X x3 {"two"}; // error : wrong initializer type
  //X x4 {1,2}; // error : wrong number of initializers
  X x5 {x2}; // OK: a copy constr uctor is implicitly defined (§17.6)

  vector<string> v1 {77}; //77 elements with the default value ""
  
  f({1,2,3});

}




















/********************* 
 *
 * */ 
int main(int argc, char *argv[])
{
  if(argc != 2) { 
    cout << "1 : base; "<< endl
       << "2 : x; "<< endl;
      exit(0);}
  int i = atoi(argv[1]);
  switch(i){
  /**  */ 
  case 1: test_constructor();
  default:;
  }

}

