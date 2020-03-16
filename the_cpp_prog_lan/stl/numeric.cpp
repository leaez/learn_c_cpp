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
void printx(TT const &a) {
  for(auto x:a) cout  << x << ", "; 
  cout << endl;
}

/** */ 



void test_base()
{ MARK;
  cout << FLT_MAX <<" ,"<< FLT_DIG <<" ,"<<  FLT_MAX_10_EXP << endl; 
  cout << DBL_MIN << " ,"<< DBL_MAX << " ,"<< DBL_EPSILON << endl;

  /**  */ 
  valarray<double> v0; // placeholder, we can assign to v0 later
  valarray<float> v1(1000); // 1000 elements with value float()==0.0F
  valarray<int> v2 {1,2,3,4,5,6,7,8};
  valarray<int> v3 = v2 *= 2; // v=={2,4,6,10,12,14,16}
  print(v3);
  v2 = 7; // v=={7,7,7,7,7,7,7,7}
  print(v2);
  v3+=v2;
  print(v3);

}


/**  */ 

void test_va()
{MARK;
  const double vd[] = {0,1,2,3,4};
  const int vi[] = {0,1,2,3,4};
  valarray<double> vd1(vd,4); // 4 elements: 0,1,2,3
  //valarray<double> v2(vi,4); //  error: vi is not pointer to double
  valarray<double> vd3(vd,8); // : too few elements in initializer 0, 1, 2, 3, 4, 0, 0, 0
  valarray<double> vd6 = cos(vd1); // v6[i] = cos(v[i]) for all i
  print(vd1);
  print(vd6);
  print(vd3);

 int alpha[] = { 1, 2, 3, 4, 5 ,6, 7, 8 };
  valarray<int> v(alpha,8); // 1, 2, 3, 4, 5, 6, 7, 8
  valarray<int> v2 = v.shift(2); // 3, 4, 5, 6, 7, 8, 0, 0
  valarray<int> v3 = v<<2; // 4, 8, 12, 16, 20, 24, 28, 32
  valarray<int> v4 = v.shift(-2); // 0, 0, 1, 2, 3, 4, 5, 6
  valarray<int> v5 = v>>2; // 0, 0, 0, 1, 1, 1, 1, 2
  valarray<int> v6 = v.cshift(2); // 3, 4, 5, 6, 7, 8, 1, 2
  valarray<int> v7 = v.cshift(-2); // 7, 8, 1, 2, 3, 4, 5, 6
  print(v2);
  print(v3);
  print(v4);
  print(v5);
  print(v6);
  print(v7);

}//destruct bbb here

/** */ 
size_t gslice_index(const gslice& s, size_t i, size_t j) // max (i,j) to their corresponding index
{
  return s.start()+i*s.stride()[0]+j*s.stride()[1];
}
void test_slice()
{MARK;
  valarray<double> d(8);
  slice_array<double> v_even = d[slice(0,d.size()/2+d.size()%2,2)];
  slice_array<double> v_odd = d[slice(1,d.size()/2,2)];
  v_even *= v_odd; // multiply element pairs and store results in even elements
  v_odd = 0; // assign 0 to every odd element of d
  //print( v_even);
  
  valarray<size_t> lengths {2,3};// 2 elements in the first dimension  // 3 elements in the second dimension
  valarray<size_t> strides {3,1}; // 3 is the stride for the first index   // 1 is the stride for the second index
  gslice s(0,lengths,strides);
  for (int i=0; i<3; ++i) // for each row
    for (int j=0; j<2; ++j) // for each element in row
      cout << "(" << i << "," << j << ")−>" << gslice_index(s,i,j) << "; "; // print mapping
  cout << endl;

  valarray<double> va1 { 1, 2, 3, 4, 5 ,6, 7, 8, 9 };
  va1[gslice(0,{2,2},{3,1})] = 99; //2*2 size sub matrix; 
  print(va1);
}

/** */ 

void test_numeric()
{MARK;
  /** accumulate */ 
  vector<int> price {1, 2, 3, 4, 5 ,6, 7, 8, 9};
  int i = accumulate(price.begin(),price.end(),0); // accumulate in int
  cout << i << endl;
  int prod = accumulate(price.begin(),price.end(),1,[](int a, int b){ return a*b; });
  cout << "accumulate:" << prod <<endl;

  /**  */ 
  vector<int> v1 {1, 2, 3, 4, 5 ,6, 7, 8, 9};
  i = inner_product(v1.begin(),v1.end(),price.begin(),0);
  cout <<"inner_product:" << i <<endl;

  /** iota */ 
  vector<int> v2(9);
  iota(v2.begin(),v2.end(),5);
  print(v2);

  /** partial_sum adjacent_difference */
  partial_sum(v1.begin(),v1.end(),v2.begin());
  print(v2);
  adjacent_difference(v1.begin(),v1.end(),v2.begin());
  print(v2);


}

/**  */ 
class Rand_int {
  public:
    Rand_int(int lo, int hi) : p{lo,hi} { } // store the parameters
    int operator()() const { return r(); }
  private:
    uniform_int_distribution<>::param_type p;
    function<int()> r = bind(uniform_int_distribution<>{p},default_random_engine{});
};
class Rand_double {
  public:
    Rand_double(double low, double high)
      :r(bind(uniform_real_distribution<>(low,high),default_random_engine())) { }
    double operator()() { return r(); }
  private:
    function<double()> r;
};


void test_radom()
{MARK;

  auto gen = bind(normal_distribution<double>{15,4.0},default_random_engine{});
  for (int i=0; i<5; ++i) cout << gen(); cout <<endl; 

  Rand_int ri {10,20}; // unifor m distr ibution of ints in [10:20)
  Rand_double rd {0,0.5}; // unifor m distr ibution of doubles in [0:0.5)
  for (int i=0; i<10; ++i)
    cout << ri() << ", "; cout << endl;
  for (int i=0; i<10; ++i)
    cout << rd() << ", "; cout << endl;

  uniform_int_distribution<> uid3 {0,5};
  default_random_engine e;
  for (int i=0; i<10; ++i)
  cout << uid3(e) << ' '; cout << endl; 
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
