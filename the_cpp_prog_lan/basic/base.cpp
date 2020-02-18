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

#define printx(x) cout << #x " = " << x << '\n'; 

//6 Types and Declarations
/**  */ 
void basic_test()
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

}

/********************* 
 *
 * */ 
int main(int argc, char *argv[])
{
    /**  */ 
    basic_test();

}
