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

using namespace std;
using std::cout; // tell the compiler that cout means std::cout
#define MARK (cout << "--------------" <<'('<<__LINE__<<')' << '<' << __FUNCTION__ << '>' <<endl) 

#define printx(x) cout << #x " = " << int{x} << '\n'; 
template <typename T>
void print(std::vector <T> const &a) {
  for(auto x:a) cout  << x << ", "; 
  cout << endl;
}
/** */ 



void test_b()
{ MARK;
  array<string, 4> as = {"Churchill", "Clare"};
  array<int,7> ai = {1,2,3,5,8,13,25};
  auto x1 = get<5>(ai); // 13
  auto x2 = ai[5]; // 13

  bitset<10> b1; // all 0
  bitset<16> b2 = 0xaaaa; // 1010101010101010
  bitset<32> b3 = 0xaaaa; // 00000000000000001010101010101010
  bitset<10> b4 {"1010101010"}; // 1010101010
  bitset<10> b5 {"10110111011110",4}; // 0111011110

  bitset<9> bs {"110001111"};
  cout << bs << '\n'; // write "110001111" to cout
  auto bs2 = bs<<3; // bs2 == "001111000";
  cout << bs2 << '\n'; // write "001111000" to cout
  cin >> bs; // read from cin
  bs2 = bs>>3; // bs2 == "000110001" if the input were "110001111"
  cout << bs2 << '\n'; // write "000110001" to cout

  int i = 5;
  bitset<8*sizeof(int)> b = i; // assume 8-bit byte = 8*4
  cout << b.to_string<char,char_traits<char>,allocator<char>>() << '\n'; // general and verbose
  cout << b.to_string<char>() << '\n'; // use default traits and allocator
  //cout << b.to_string<>() << '\n'; // use all defaults
  cout << b.to_string() << '\n'; // use all defaults

  /**  */ 
  pair<string,int> pr {"Cambridge\n",1209};
  cout << pr.first; // print "Cambr idge"
  pr.second += 800; // update year
  using Tup = tuple<string,int>;
  Tup t1 {"Columbia",11};  Tup t2 {"Cambridge",2};// U.S. News 2012
  pair<Tup,Tup> p1 {t1,t2};

  /**  */ 
  auto t = make_tuple(2.71828,299792458,"Hannibal");
  double c;  string name;  tie(c,ignore,name) = t; // c=299792458; name="Hannibal"
  //double c = get<0>(t); string name = get<2>(t);  // c=299792458  // name="Hannibal"  

}

/******    */
unique_ptr<int[]> make_sequence(int n)
{
  unique_ptr<int[]> p {new int[n]};
  for (int i=0; i<n; ++i)  p[i]=i;
  return p;
}

unique_ptr<int> f(unique_ptr<int> p) { ++*p; return p; }
void f2(const unique_ptr<int>& p) { ++*p; }

struct S { int i; string bar; double d;
  S(int i,string bar, double d) : i(i),bar(bar),d(d){}
  ~S() {cout << "S: destructor, bar = " << bar << '\n'; }
  string getBar() const noexcept { return bar; }
};

void test_ptr()
{MARK;
  /**  */ 
  unique_ptr<int[]>  up;
  up = make_sequence(10);
  //auto x=up.get(); for ( int i=0; i<10; i++ ) cout << x[i]; cout << endl;
  for ( int i=0; i<10; i++ ) cout << up[i]; cout << endl;

  unique_ptr<int> p {new int{7}};
  //p=f(p); // error : no copy constru
  p=f(move(p)); // transfer ownership the
  f2(p); // pass a reference
    
  auto sp = make_shared<S>(1,"Aaaa aaa",4.65);
  auto sp1 = sp;
  cout << "uc:" << sp1.use_count() << sp.use_count() << endl;
  cout << "The first S's bar is " << sp->getBar() << "\n";
  sp.reset(new S{22,"Bbb bbb",2.22}); //destruct aaa
  cout << "The second S's bar is " << sp->getBar() << "\n";

}//destruct bbb here

/** */ 
std::weak_ptr<int> gw;
 
void observe()
{
  cout << "use_count == " << gw.use_count() << ": ";
  if (auto spt = gw.lock()) { // Has to be copied into a shared_ptr before usage
	  cout << *spt << "\n";
  } else {
    cout << "gw is expired\n";
  }
}


void test_weak()
{MARK;
  {
    auto sp = std::make_shared<int>(42);
	  gw = sp;
 	  observe();
  }
  observe();
  
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
  case 1: test_b();break;
  case 2: test_ptr();break;
  case 3: test_weak();break;
  default:;
  }

}
