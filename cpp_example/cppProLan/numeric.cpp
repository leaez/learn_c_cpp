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
template <typename T> 
void printv(T &vi){
    for (auto& x :  vi) // implicit use of v.begin() and v.end()
        cout << x << "," ; cout << endl;
}

void test_math(){
    double x = 2.0;
    cout << "----------------test math" <<endl;
    cout << "fmax:" << fmax(12.0, 34.0)<< endl;
    cout << "exp"<< exp(x) << "loge;" <<log(x)<<endl;


}

class Rand_double {
    public:
        Rand_double(double low, double high)
            :r(bind(uniform_real_distribution<>(low,high),default_random_engine())) { }
        double operator()() { return r(); }
    private:
        function<double()> r;
};

void test_rand(){
    cout << "-----------------test rand " << endl;
    /**  */ 
    Rand_double rd{10,20}; 
    cout << rd();
  
}

/**  supports element-wise mathematical operations  */ 
void test_valarray(){
    cout << "\n-------------test valarray "<<endl;
    valarray<char> a(10); //10's char
    a[2] = '2'; printv(a);
    cout << "vsize :" << a.size()<< endl;

    valarray<int> v = { 1, 2, 3, 4, 5 ,6, 7, 8 };
    cout <<"vmax:" << v.max() << "; vsum:"  << v.sum() << "vsize :" << v.size() <<endl;

    //valarray<double> v2 = v*v;
    v = v*2; //every one *2 
    cout << "vsize:" << v.size(); printv(v);
    valarray<int> v2 = v>>1;  // every one /2
    v = v.shift(2); //size not change; every one positions are shifted left
    printv(v);
    v = v.apply([](int n){return n+=1;}); 
    printv(v);

    /** slice */ 
    valarray<int> v3 {00,01,02, 03,10,11,12, 13,20,21,22, 23}; // row 1
    valarray<int> v4 = v3[slice(3,3,4)]; //slice(start, size, stride ); 
    printv(v4); // 3,13,23  : from:03 , out 3 num;  strid:4

    valarray<char> v0 {"abcdefghijklmnop",11};
    printv(v0);
    valarray<char> v1 {"ABCDE",5};
    const valarray<size_t> len {2,3};//multi-level set of strides. 
    const valarray<size_t> str {7,2}; //multi-level set of sizes. 
    v0[gslice(3,len,str)] = v1; // v0=={"abcAeBgCijDlEnFp",16}
    printv(v0);
   

}


/********************* 
 *
 * */ 
int main()
{
    test_math();

    test_rand();

    test_valarray();

    return 0;
}
