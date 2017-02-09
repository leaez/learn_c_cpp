#include <iostream>
#include <array>
#include <map>
#include <tuple>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <limits>
#include <cmath>
#include <valarray>
#include <random>


using namespace std;


double incr(double d) 
{ return d+1; }

class Rand_double {
    public:
        Rand_double(double low, double high)
            :r(bind(uniform_real_distribution<>(low,high),default_random_engine())) { }
        double operator()() { return r(); }
    private:
        function<double()> r;
};

/********************* 
 *
 * */ 
int main()
{

    //cout << numeric_limits<unsigned char>::max() << "\n";

    valarray<char> v0 {"abcdefghijklmnop",16};
    valarray<char> v1 {"ABCDE",5};
    const valarray<size_t> len {2,3};
    const valarray<size_t> str {7,2};
    v0[gslice(3,len,str)] = v1; // v0=={"abcAeBgCijDlEnFp",16}

    //valarray<double> v = { 1, 2, 3, 4, 5 ,6, 7, 8 };
    valarray<int> v = { 1, 2, 3, 4, 5 ,6, 7, 8 };
    valarray<double> vv = {1, 3,4,5};
    //valarray<double> v2 = v.apply(incr); 
    //valarray<double> v2 = v*vv;
    valarray<int> v2 = v>>2;
    valarray<int> v3 {00,01,02,03,10,11,12,13, 20,21,22,23}; // row 1
   //     {20,21,22,23} // row 2
   // };
   valarray<int> v4 = v3[slice(3,3,4)]; 
   // slice_array<int> v4 = v3[slice(0,4,3)]; 

    for(auto x: v4 ){
        cout <<"-"<< x ;
    } cout <<"\n";
    
    /**  */ 
    Rand_double rd{10,20}; 
    cout << rd();

}
