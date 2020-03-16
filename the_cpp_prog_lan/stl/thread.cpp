#include <unistd.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <array>
#include <bitset>
#include <tuple>
#include <mutex>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <cassert>
#include <iterator>
#include <memory>
#include <chrono>
#include <ratio>

#include <cctype>
#include <regex>
#include <climits>
#include <cfloat>
#include <valarray>
#include <numeric>
#include <random>

using namespace std;
using namespace std::chrono;
using std::cout; // tell the compiler that cout means std::cout
#define MARK (cout << "--------------" <<'('<<__LINE__<<')' << '<' << __FUNCTION__ << '>' <<endl) 

#define printX(x) cout << #x " = " << int{x} << '\n'; 
//template <template <typename> class  V>
template <typename T> 
void print(T const &a) {
  for(auto x:a) cout  << x << ", "; 
  cout << endl;
}
template <typename T, class TT >
void printa(TT const &a) {
  for(auto x:a) cout  << x << ", "; 
  cout << endl;
}

/** */ 



void test_base()
{ MARK;


}


/**  */ 

void test_va()
{MARK;


}//destruct bbb here

/** */ 

void test_slice()
{MARK;

}

/** */ 

void test_numeric()
{MARK;



}

/**  */ 




void test_radom()
{MARK;


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
  case 1: test_base();break;
  case 2: test_va();break;
  case 3: test_slice();break;
  case 4: test_numeric();break;
  case 5: test_radom();break;
  default:;
  }

}
