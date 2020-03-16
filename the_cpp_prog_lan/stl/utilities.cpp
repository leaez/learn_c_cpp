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
#include <cctype>
#include <iterator>
#include <memory>
#include <chrono>
#include <ratio>

using namespace std;
using namespace std::chrono;
using std::cout; // tell the compiler that cout means std::cout
#define MARK (cout << "--------------" <<'('<<__LINE__<<')' << '<' << __FUNCTION__ << '>' <<endl) 

#define printx(x) cout << #x " = " << int{x} << '\n'; 
template <typename T>
void print(std::vector <T> const &a) {
  for(auto x:a) cout  << x << ", "; 
  cout << endl;
}
/** */ 



void test_time()
{ MARK;
  /** time_point  */ 
  auto t = steady_clock::now();
  usleep(100000);
  auto d = steady_clock::now(); // something took d time units
  cout << "something took " << duration_cast<milliseconds>(d-t).count() << "ms\n"; // print as milliseconds
  using nanoseconds = duration<long long,nano>;
  cout << "sleep took " << nanoseconds(d-t).count() << " nanoseconds\n";

  duration<long long,milli> d1 {7}; // 7 milliseconds
  duration<int,ratio<1,1>> d2 {7},d3{}; // 7 seconds
  d1 += duration<long long,milli>{5}; // OK: milliseconds
  //d2 += 5; // error
  d3 += decltype(d2){5}; // OK: seconds
  
  /** time_point  */ 
  /** Clocks */ 
  auto t1 = system_clock::now();
  cout << "min " << system_clock::duration::min().count()
    << ", max " << system_clock::duration::max().count()
    << ", " << (treat_as_floating_point<system_clock::duration>::value ? "FP" : "integral") << '\n';
  cout << (system_clock::is_steady?"steady\n": "not steady\n");

  /** ratio */ 
  static_assert(ratio_add<ratio<1,3>, ratio<1,6>>::num == 1, "problem: 1/3+1/6 != 1/2");
  static_assert(ratio_add<ratio<1,3>, ratio<1,6>>::den == 2, "problem: 1/3+1/6 != 1/2");

}


/**  */ 
template<typename T>
void f(T& a)
{
  static_assert(std::is_floating_point<T>::value,"FP type expected");
  // ...
}
void test_compile()
{MARK;
  //int x = 12;  f(x); //fail!
  double d1 = 12; f(d1);



}//destruct bbb here

/** */ 

void test_move()
{MARK;

  /** swap */ 
  vector<int> v1 {1,2,3,4}, v2{};
  swap(v1,v2);
  print(v1);
  print(v2);
 
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
  case 1: test_time();break;
  case 2: test_compile();break;
  case 3: test_move();break;
  default:;
  }

}
