#include <iostream>
#include <cassert>
#include <cmath>
#include <array>
#include <map>
#include <tuple>
#include <vector>
#include <list>
#include <queue>
#include <mutex>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <cassert>
#include <cctype>
#include <iterator>

using namespace std;
using std::cout; // tell the compiler that cout means std::cout
#define MARK (cout << "--------------" <<'('<<__LINE__<<')' << '<' << __FUNCTION__ << '>' <<endl) 

#define printx(x) cout << #x " = " << int{x} << '\n'; 
template <typename T>
void print(std::vector <T> const &a) {
  for(auto x:a) cout  << x << ", "; 
  cout << endl;
}
/**for_each/find_if/search/transform  */ 
void test_b()
{
  vector<int> v {1,2,3,4};
  for_each(v.begin(),v.end(), [](int& x) {++x;});
  print(v);

  assert(all_of(v.begin(),v.end(),[](int x){ return 0<x; }));
  string s{"xxx fsdflksd lee xfs"};
  auto p_whitespace = find_if(s.begin(),s.end(), ::isspace); //must ::isspace

  array<int, 3> ax = {1,3,4 };
  array<int, 5> ay = {0,2,3,4,5}; 
  auto p_first = find_first_of(ax.begin(),ax.end(),ay.begin(),ay.end()); // p = &x[1] get 3(int ay) equal ax's 

  string quote {"Why waste time learning, when ignorance is instantaneous?\n"}; 
  string ss{"when"};
  auto p_search = search(quote.begin(),quote.end(),ss.begin(),ss.end()); // find s in quote
  if(p_search!=quote.end()) cout << "found\n";

  transform(ss.begin(),ss.end(),quote.begin(),::toupper);
  cout << quote; 



}

/****** unique/remove/generate/nth_element/binary_search/merge   */ 
void test_modify()
{
  string s ="abbcccde";
  auto p = unique(s.begin(),s.end());
  cout << s << ' ' << p-s.begin() << '\n'; //5
  s.erase(p,s.end()); // shrink
  cout << s << ' ' << s.size() << '\n'; //5
  
  remove(s.begin(),s.end(),'c');
  cout << s << ' ' << s.size() << '\n'; //5

  vector<int> vi {1,2,3,4};
  random_shuffle(vi.begin(),vi.end());
  print(vi);
  vector<int> v1(9), v2(9),v3{};
  //vector<int> v2{};  vector<int> v3{};
  fill(begin(v1),end(v1),9); // set all elements of v1 to 99
  //generate(begin(v2),end(v2),::rand); // set to random values (§40.7)
  generate(v2.begin(), v2.end(), [] ()  { return ::rand()%100; });
    // output 200 random integers in the interval [0:100):
  generate_n(ostream_iterator<int>{cout},10,[] ()  { return ::rand()%100; }); // see §40.7
  fill_n(back_inserter(v3),11,33); // add 20 elements with the value 33 to v3
  print(v1);
  print(v2);
  print(v3);

  swap_ranges(v1.begin(),v1.end(),v2.begin());
  print(v1);

  nth_element(v1.begin(), v1.begin() + v1.size()/2, v1.end());
  nth_element(v2.begin(), v2.begin() + v2.size()/2, v2.end());
  print(v2);

  if (binary_search(v1.begin(),v1.end(),7)){
    cout << "found !";  }
  vector<int> v4 {22,33,44};
  sort(v1.begin(),v1.end());
  sort(v2.begin(),v2.end());
  print(v1);
  print(v2);
  merge(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v2));
  print(v2);

  string n1 = "Zebra"; string n2 = "Aardvark";
  if(lexicographical_compare(n1.begin(),n1.end(),n2.begin(),n2.end())) 
      cout << "yes !\n"; // b2 == false

  auto pm = minmax_element(v1.begin(),v1.end(), [](int c1,int c2) { return c1 < c2; });
  cout << "min==" << *(pm.first) << ' ' << "max==" << *(pm.second) << '\n';
}

/** bind && function  */ 
using namespace placeholders;
void incr(int& i) { ++i; }

int roundx(double x) { return static_cast<double>(floor(x+0.5)); } // conventional 4/5 rounding
function<int(double)> f; // f can hold anything that can be called with a double and return an int
enum class Round_style { truncate, round };
struct Round { // function object carrying a state
  Round_style s;
  Round(Round_style ss) :s(ss) { }
  int operator()(double x) const { return (s==Round_style::round) ? (x+0.5) : x; };
};


void test_bind()
{
  int i = 1;
  incr(i); // i becomes 2
  auto inc = bind(incr,_1);
  inc(ref(i)); // i becomes 3
  cout << i <<endl;

  /** function */ 
  function<int(double)> fct {}; // 
  fct = [](double d) { return round(d); };
  cout << fct(3.5) <<endl;

  f = roundx;
  cout << f(7.6) << '\n'; // call through f to the function round
  f = Round(Round_style::truncate);
  cout << "call the function:" << f(7.6) << '\n'; // call the function object
  Round_style style = Round_style::round;
  f = [style] (double x){ return (style==Round_style::round) ? x+0.5 : x; };
  cout << "call lambda: " << f(7.6) << '\n'; // call the lambda

  vector<double> v {7.6, 6.3};
  f = Round(Round_style::round);
  std::transform(v.begin(),v.end(),v.begin(),f); // pass to algorithm
  cout <<"func obj:"<< v[0] << v[1] << '\n'; // transformed by the lambda
  
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
  case 1: test_b();
  case 2: test_modify();
  case 3: test_bind();
  default:;
  }

}
