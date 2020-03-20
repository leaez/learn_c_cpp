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

#include <thread>
#include <mutex>
#include <condition_variable>

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

void tick(int n)
{
  for (int i=0; i!=n; ++i) {
    this_thread::sleep_for(seconds{1}); // §42.2.6
    cout<< "Alive! ";
  }
  thread::id me {this_thread::get_id()};
  cout << "id:" << me <<endl;
}

void test_base()
{MARK;
  thread timer {tick,3};
  timer.join();

  /**  */



}

/** mutex */
mutex cout_mutex; // initialized to ‘‘not owned by any thread’’
void hello()
{
  cout_mutex.lock();
  cout << "Hello, \n";
  cout_mutex.unlock();
}

void world()
{
  cout_mutex.lock();
  cout << "World! \n";
  cout_mutex.unlock();
}
void bad_mutex(){
  //mutex mtx; //
  recursive_mutex mtx;
  try { mtx.lock(); mtx.lock(); // try to lock a second time }
  } catch (system_error& e) {
    mtx.unlock();
    cout << e.what() << '\n';
    cout << e.code() << '\n';
  }
}

mutex mtx;
timed_mutex mtx2;
void use_unique()
{
  //unique_lock<mutex> lck {mtx,try_to_lock_t};
  unique_lock<mutex> lck(mtx,defer_lock);
  unique_lock<timed_mutex> lck2 {mtx2, defer_lock };
  //lck.try_lock_for(milliseconds{2}); // error : mutex does not have member try_lock_for()
  if(lck2.try_lock_for(milliseconds{2})){
    cout << "lock got !\n";
  }; // OK
  try{lck2.try_lock_until(steady_clock::now()+milliseconds{2});
  } catch (system_error& e) {
    mtx.unlock();
    cout << e.what() << "!!\n";   cout << e.code() << '\n';
  }

  lck2.unlock();
  {
    unique_lock<timed_mutex> lck3 {mtx2};
    if(mtx2.try_lock()){ //lock yet
      cout<< "in mtx2 got!\n";
    }
  }//will unlock!!
  if(mtx2.try_lock()){
    cout<< "out mtx2 got !\n";
  }


// ...
}

void test_mutex()
{MARK;
  thread t1 {hello};
  thread t2 {world};
  t1.join();
  t2.join();
  
  bad_mutex();
  use_unique();
}




/** */ 
void simple_timer(int delay)
{
  condition_variable timer;
  mutex mtx; // mutex protecting timer
  auto t0 = steady_clock::now();
  unique_lock<mutex> lck(mtx); // acquire mtx
  timer.wait_for(lck,milliseconds{delay}); // release and reacquire mtx
  auto t1 = steady_clock::now();
  cout << duration_cast<milliseconds>(t1-t0).count() << "milliseconds passed\n";
} // implicitly release mtx

void test_condition_variable()
{MARK;
  simple_timer(1000);
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
  case 2: test_mutex();break;
  case 3: test_condition_variable();break;
  case 4: test_numeric();break;
  case 5: test_radom();break;
  default:;
  }

}
