#include <iostream>
#include <array>
#include <tuple>
#include <vector>
#include <cstddef>

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost; 

struct B {};
struct D : B {};
 
enum class E { ONE, TWO, THREE };
enum EU { ONE, TWO, THREE };

struct type_t {
    type_t() :i(3) {}
    void m1(int v) const {
        // this->i = v;                 // compile error: this is a pointer to const
        const_cast<type_t*>(this)->i = v; // OK as long as the type_t object isn't const
    }
    int i;
};

template<class F, class A>
void Fwd(F f, A a)
{
    f(a);
}
 
void g(int* i)
{
    std::cout << "Function g called\n";
}

int main(int argc, char* argv[])
{
    // 1: initializing conversion
    int n = static_cast<int>(3.14);  //float -> int 
    std::cout << "n = " << n << '\n';
    std::vector<int> v = static_cast<std::vector<int>>(10); //vector size
    std::cout << "v.size() = " << v.size() << '\n';
 
    // 2: static downcast
    D d;
    B& br = d; // upcast via implicit conversion
    D& another_d = static_cast<D&>(br); // downcast  base --> child
 
    // 3: lvalue to xvalue
    std::vector<int> v2 = static_cast<std::vector<int>&&>(v); //like move , v not point null
    std::cout << "after move, v.size() = " << v2.size() << '\n';
 
    // 4: discarded-value expression
    static_cast<void>(v2.size());
 
    // 5. inverse of implicit conversion
    void* nv = &n;
    int* ni = static_cast<int*>(nv); 
    std::cout << "*ni = " << *ni << '\n';
 
    // 6. array-to-pointer followed by upcast
    D a[10];
    B* dp = static_cast<B*>(a); 
 
    // 7. scoped enum to int or float
    E e = E::ONE;
    int one = static_cast<int>(e);
 
    // 8. int to enum, enum to another enum
    E e2 = static_cast<E>(one);
    EU eu = static_cast<EU>(e2);
 
    // 9. pointer to member upcast
    // todo
 
    // 10. void* to any type_t
    void* voidp = &e;
    std::vector<int>* p = static_cast<std::vector<int>*>(voidp);

    /********************************
     * const_cast<> */ 
    
    int i = 3;                    // i is not declared const
    const int& cref_i = i; 
    //cref_i = 5; //error 
    const_cast<int&>(cref_i) = 4; // OK: modifies i
    std::cout << "i = " << i << '\n';

    const int aa = 20;
    //int& bc = aa;  error
    int& bb = const_cast<int&>(aa);
    bb = 30; //aa not changed 
    std::cout << "aa = " << aa << bb<< '\n';

 
    type_t t; // note, if this is const type_t t;, then t.m1(4); is UB
    t.m1(4);
    std::cout << "type_t::i = " << t.i << '\n';
 
    const int j = 3; // j is declared const
    int* pj = const_cast<int*>(&j);
    *pj = 4;         // undefined behavior!
 
    void (type_t::*mfp)(int) const = &type_t::m1; // pointer to member function
//  const_cast<void(type_t::*)(int)>(mfp); // compiler error: const_cast does not
                                         // work on function pointers
    g(NULL);           // Fine
    g(0);              // Fine
 
    Fwd(g, nullptr);   // Fine
    //Fwd(g, NULL);  // ERROR: No function g(int)


    return 0;
}
