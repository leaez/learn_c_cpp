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

//#include <stdio>

using namespace std;
using std::cout; // tell the compiler that cout means std::cout
#define MARK (cout << "--------------" <<'('<<__LINE__<<')' << '<' << __FUNCTION__ << '>' <<endl) 

#define printx(x) cout << #x " = " << int{x} << '\n'; 

//6 Types and Declarations
/**  */ 
void narrowing(double dval, int ival);

void test_basic()
{
  //bool test
  bool b1 = 7; // 7!=0, so b becomes true
  //bool b2 {7}; // warning: : narrowing conversion

  //char type
  for (int i=0; i!=10; ++i)
    cout << static_cast<char>('0'+i);   cout << '\n';
  char c = 255; // 255 is  hexadecimal 0xFF
  int i = c; printx(i); //print -1 
  signed char sc = -160; //warning: overflow in implicit constant conversion
  unsigned char uc = sc; cout << "uc:" << int{uc} <<'\n' ;// printx(uc) // uc == 96 (because 256-160==96)

  //intege
  cout << 0xF0UL << ' ' << 0LU << '\n';
  narrowing(5.2,257);

}

void narrowing(double dval, int ival)
{
  int i1 = dval; // if dval==7.9, x2 becomes 7
  int i2 {dval}; // warning: narrowing conversion from ‘double’ to ‘int’ 
  //int i4 {2.0}; //  error: narrowing conversion of ‘2.0e+0’ from ‘double’ to ‘int’ 
  
  char c2 = ival; // if val2==1025, c2 becomes 1
  char c3 {ival}; printx(c3);// narrowing conversion of ‘val2’ from ‘int’ to ‘char’
  char c4 {24}; // OK: 24 can be represented exactly as a char
  //char c5 {264}; // error: narrowing conversion of ‘264’ from ‘int’ to ‘char’ 
  char c6 = dval; printx(c6); //no warning 5.6=> 5
  
  int i3{c2}; //ok
  double d1 {ival}; //warning: narrowing conversion of ‘ival’ from ‘int’ to ‘double’

}

void fpoint(int* pi)
{
  //double* pd2 = pi; // error: cannot convert ‘int*’ to ‘double*’ 
  //int i = nullptr; //error: cannot convert ‘std::nullptr_t’ to ‘int’  
  int* x = 0; // x gets the value nullptr
  int* p = NULL; // ok

  char* pc = "Plato"; //warning: ISO C++ forbids converting a string constant to ‘char*’ 
  //reference
  int var = 1;  int& r {var};
  const double& cdr {1}; // OK

}

template<class T>
void swap(T& a, T& b) // "perfect swap" (almost)
{
  T tmp {move(a)}; // move from a 为x创建一了一个右值引用
  a = move(b); // move from b
  b = move(tmp); // move from tmp
}
void incr(vector<int>& v)
{
  for (int& x : v)
  ++x;
}

/**  */ 
void test_basic2()
{
  auto flambda =  [](double a) { return sqrt(a); };
  cout << "lamada:" <<flambda(9) << endl;


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
  case 1: test_basic();
  case 2: test_basic2();
  default:;
  }

}
