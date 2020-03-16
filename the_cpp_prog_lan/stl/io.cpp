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



void test_base()
{ MARK;
  ostringstream oss2 {"Label: "}; // write at beginning
  cout << oss2.str() << '\n'; // writes "Label: "
  oss2<<"val";
  cout << oss2.str() << '\n'; // writes "valel: " (val overwr ites "Label: ")
  /**  */ 
  istringstream iss;
  iss.str("Foobar"); // Fill iss
  cout<< iss.str() << '\n'; // OK: writes "Foobar"
}


/**  */ 

void test_serach()
{MARK;
  


}//destruct bbb here

/** */ 

void test_replace()
{MARK;


}

/** */ 

void test_iterator()
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
  case 2: test_serach();break;
  case 3: test_replace();break;
  case 4: test_iterator();break;
  default:;
  }

}
