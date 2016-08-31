#include <iostream>
#include <array>
#include <map>
#include <tuple>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <functional>

using namespace std;
//using namespace boost; 

struct S {
    int x;
    struct Foo {
        int i;
        int j;
        int a[3];
    } b;
};

int main(int argc, char* argv[])
{
    S s1 = { 1, { 2, 3, {4, 5, 6} } };
    S s2 = { 1, 2, 3, 4, 5, 6}; // same, but with brace elision
    S s3{1, {2, 3, {4, 5, 6} } }; // same, using direct-list-initialization syntax
    S s4{1, 2, 3, 4, 5, 6}; // error in C++11: brace-elision only allowed with equals sign
                            // okay in C++14

    int ar2d1[2][2] = {{1, 2}, {3, 4}};
    std::array<int, 3> std_ar1 = {1, 2, 3};
    std::string ars[] = {std::string("one"), // copy-initialization
                         "two",              // conversion, then copy-initialization
                         {'t', 'h', 'r', 'e', 'e'} }; // list-initialization
    /** reference  */ 
    int n = 20;
    int& r1 = n;  // lvalue reference to the object n
    
    int&& rref = 1; // bound to rvalue

    /** lambda, function  */ 
    auto glambda = [](int a, int b) { return a < b; };
    bool b = glambda(3, 3.14); // ok
    std::vector<int> c = {1, 2, 3, 4, 5, 6, 7};
    int x = 5;
    c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; }), c.end());
    std::for_each(c.begin(), c.end(), [](int i){ std::cout << i<< ' '; });
    std::cout << '\n';
    std::function<int(int)> func2 = [](int i) { return i + 4; };
    std::cout << "func2: " << func2(6) << '\n';

    /**  */ 
    for(const int &i : c) // access by const reference
        std::cout << i << ' ';
    for(int n: {0, 1, 2, 3, 4, 5})


    return 0;
}
