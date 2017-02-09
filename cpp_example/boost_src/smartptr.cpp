#include "boost/scoped_ptr.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include "boost/shared_ptr.hpp"
#include <cassert>
#include "boost/weak_ptr.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/utility.hpp"
#include "boost/operators.hpp"
#include "boost/regex.hpp"

#include "boost/tuple/tuple.hpp"
#include "boost/math/common_factor.hpp"

#include "boost/bind.hpp"

#include "boost/lambda/lambda.hpp"
#include "boost/lambda/bind.hpp"
#include "boost/lambda/if.hpp"
#include "boost/lambda/loops.hpp"

#include "boost/function.hpp"

#include "boost/signals2/signal.hpp"


//using namespace boost::lambda;

class A {  
    boost::shared_ptr<int> no_;
    public:  A(boost::shared_ptr<int> no) : no_(no) {}  
    void value(int i) {*no_=i;  }
};
class B {  
    boost::shared_ptr<int> no_;public:  
    B(boost::shared_ptr<int> no) : no_(no) {}  
    int value() const {return *no_;  } /** read */ 
};
class codebreaker {
    public:  int operator&() const {    return 13;  }};

class some_class:boost::equivalent<some_class> { //derived from operators
    int value_;
    public:  some_class(int value) : value_(value) {}  
    bool less_than(const some_class& other) const {return value_<other.value_;  }};
bool operator<(const some_class& lhs, const some_class& rhs)
    { return lhs.less_than(rhs);}

boost::tuple<int,int> gcd_lcm(int val1,int val2) {  
    return boost::make_tuple(boost::math::gcd(val1,val2),boost::math::lcm(val1,val2));}

void nine_arguments(  int i1,int i2,int i3,int i4,  int i5,int i6,int i7,int i8, int i9) {  
    std::cout << i1 << i2 << i3 << i4 << i5    << i6 << i7 << i8 << i9 << '\n';}

class some_class1 {
    public:  typedef void result_type;  
    void print_string(const std::string& s) const {std::cout << s << '\n';  }
};
void print_string(const std::string s) 
    {std::cout << s << '\n';}

boost::lambda::placeholder1_type Arg1; // just  like _1, _2,_3
boost::lambda::placeholder2_type Arg2;
boost::lambda::placeholder3_type Arg3;
template <typename T,typename Operation>
void for_all(T& t,Operation Op) {
  std::for_each(t.begin(),t.end(),Op);  //op as a lambda fun
}

bool some_func(int i,double d) {std::cout<< "Function\n"; return i>d;}

class some_class2 {
    public:  bool some_function(double d) {std::cout<< "sig Fun called\n";return d>3.14;  } 
    bool another_function(double d) {std::cout<< "sig Fun called\n";return d<0.0;  }};

int main() 
{   
    {  
        boost::scoped_ptr<std::string> p(new std::string("Use scoped_ptr often."));  // 打印字符串的值  
        if (p) 
            std::cout << *p << '\n';      // 获取字符串的大小  
        size_t i = p->size();  // 给字符串赋新值  
        *p="Acts just like a pointer";    
    } // 这里p被销毁，并删除std::string 

    boost::shared_ptr<int> temp(new int(14));
    A a(temp);
    B b(temp); /** point to same v */ 
    a.value(28);
    std::cout<<b.value()<<"\n";
    assert(b.value()==28);

    /** weak ptr */

    boost::shared_ptr<std::string> sp(new std::string("Some resource"));  
    boost::weak_ptr<std::string> wp(sp);
    if (boost::shared_ptr<std::string> p=wp.lock())
        std::cout << "Got it: " << *p << '\n';

    /** lexical_cast */ 
    // string to int  
    std::string s="42";  
    int i=boost::lexical_cast<int>(s);  
    // float to string  
    float f=3.14151;  
    s=boost::lexical_cast<std::string>(f);  
    // literal to double  
    double d=boost::lexical_cast<double>("2.52");
    
    /** addressof */ 
    codebreaker  ss ;//= new A();  
    std::cout<<boost::addressof(ss)<<"\n";

    /** operator  */ 
    some_class s1(12);  
    some_class s2(11);  
    if (s1==s2)    std::cout << "s1==s2\n"; //Operators库为我们生成的operator== 

    /** regx */ 
    boost::regex reg("(Colo)(u)(r)",
            boost::regex::icase|boost::regex::perl);
    std::string s3="Colour, colours, color, colourize"; 
    s3=boost::regex_replace(s3,reg,"$1$3"); //第1，3个子表达式
    std::cout << s3 << "\n";

    /**  tuple */ 
    int gcd, lcm;
    boost::tie(gcd,lcm)=gcd_lcm(15,20);   //get returned tuple value
    std::cout << "Greatest common divisor: " << gcd << '\n';  
    std::cout << "Least common multiple: " << lcm << '\n';
    
    /** bind */ 
    int i1=1,i2=2,i3=3,i4=4,i5=5,i6=6,i7=7,i8=8,i9=9; 
    (boost::bind(&nine_arguments,_9,_2,_1,_6,_3,_8,_4,_5,_7))(i1,i2,i3,i4,i5,i6,i7,i8,i9);

    (boost::bind(&print_string,_1))("bind func!");  
    some_class1 sc; 
    (boost::bind(&some_class1::print_string,_1,_2))(sc,"bind  member fun!");

    (boost::bind(&some_class1::print_string, some_class1(),"bind member fun! & para const"))(); //连参数也固定了

    /** lambda */ 
    (std::cout << Arg1 << " " << Arg2 << " " << Arg3 << "!\n")("lambda","fun","called"); //lambda expression
    boost::function<void(int,int,int)> f0=  std::cout << Arg1 << "*" << Arg2 << "+" << Arg3 << "=" <<Arg1*Arg2+Arg3 << "\n";
    f0(1,2,3);  //call lambda 
    f0(3,2,1);

    std::vector<std::string> vec;
    vec.push_back("What are");
    vec.push_back("the names");
    vec.push_back("of the");
    vec.push_back("placeholders?");
    for_all(vec,std::cout << Arg1 << " ");
    std::cout << "\n";
    {
        using namespace boost::lambda;
        (if_then(Arg1<5,std::cout << constant("Less than 5\n")))(3);
        int val1=1;
        int val2=4;
        (while_loop(Arg1<Arg2,
                (++Arg1,std::cout << constant("Inc...\n"))))(val1,val2);
        
    }

    /** function */ 
    boost::function<bool (int,double)> f2;  
    f2=&some_func;  
    f2(10,1.1);

    /** signals */ 
    boost::signals2::signal<bool (double)> sig0;  
    boost::signals2::signal<bool (double)> sig1;  
    some_class2 sc2;  
    sig0.connect(boost::bind(&some_class2::some_function,&sc2,_1));  
    sig1.connect(boost::bind(&some_class2::another_function,&sc2,_1));  
    sig0(3.1);  
    sig1(-12.78);


}
