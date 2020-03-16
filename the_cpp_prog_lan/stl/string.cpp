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
  char c{'z'};
  if (islower(c)) cout << "low c\n";// a lowercase characte

  string s1 {"As simple as that!"}; // construct from C-style string
  string s2 {s1}; // copy constr uctor
  string s5 {7,'a'}; // OK: 7 'a's
  string ss {"Fleetwood Mac"};
  string ss2 {ss,0,9}; // "Fleetwood"
  string ss3 {ss,10,string::npos}; // "Mac
  
  int max = 100;
  ss.reserve(max); //size:13 ca:100 make sure there is enough allocated space 
  cout << "size:" << ss.size() << "ca:"<< ss.capacity() <<endl; 
  ss.resize(10);  //size:10 ca:100
  cout << "size:" << ss.size() << "ca:"<<ss.capacity() <<endl; 
  ss.shrink_to_fit(); //size:10 ca:10
  cout << "size:" << ss.size() << "ca:"<< ss.capacity() <<endl; 

  string si = "123.4567801234";
  size_t dist = 0; // put number of characters read here
  auto x = stoi(si,&dist); // x = 123 (an int) dist = 3
  cout << x << "," << dist <<endl;
  ++dist; // ignore the dot
  auto y = stoll(&si[dist]); // x = 4567801234 (a long long)
  cout << y <<endl;
  string s4 = "149F";
  auto x5 = stoi(s4); // x5 = 149
  auto x6 = stoi(s4,nullptr,10); // x6 = 149
  auto x7 = stoi(s4,nullptr,8); // x7 = 014
  auto x8 = stoi(s4,nullptr,16); // x8 = 0x149F

  /**  */ 
  auto p = s1.find(' ');
  s1.insert(p,"_"); cout << s1 <<endl;
  /** insert */ 
  string s = "but I have heard it works even in if you don't believe in it";
  s.replace(0,4,""); // erase initial "but "
  s.replace(s.find("even"),4,"only");
  s.replace(s.find(" don't"),6,""); // erase by replacing with ""
  cout << s << endl;
  string s6 = "but I have heard it works even if you don't believe in it";
  s6.replace(0,4,"").replace(s6.find("even"),4,"only").replace(s6.find(" don't"),6,"");
  cout << s6 << endl;

}


/**  */ 

void test_find()
{MARK;

  /** find */ 
  string s = "xxxx abc, efg ,abc, yyyy, efg\n";
  auto i1 = s.find("abc"); cout << i1 <<","<< endl; //5
  i1 = s.find("abc",8); cout << i1 <<","<< endl; //15
  i1 = s.find("abcc",0,3); //find abc from 0
  if(i1== string::npos){
    cout << "not found\n";
  }else
    cout << i1 <<","<< endl; //45

  i1 = s.find("abcc",14,4); //find abcc from 14
  if(i1== string::npos){
    cout << "not found\n";
  }else
    cout << i1 <<","<< endl; //45

  /**  */ 
  string s1 = "Mary had a little lamb";
  string s2 = s1.substr(0,4); // s2 == "Mary"
  s2 = "Rose"; // does not change s1

}//destruct bbb here

/** */ 

void test_move()
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
  case 2: test_find();break;
  case 3: test_move();break;
  default:;
  }

}
