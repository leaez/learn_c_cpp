#include <iostream>
#include <vector>
#include <initializer_list>
#include <csignal>
#include <memory>
#include <utility>
#include <functional>
#include <tuple>

using namespace std;
using namespace placeholders;

template <typename T> 
void printv(T &vi){
    for (auto& x :  vi) // implicit use of v.begin() and v.end()
        cout << x << "," ; cout << endl;
}

void t_init(initializer_list<int> l) { 
    cout << "constructed with a " << l.size() << "-element list\n";
    for (int x : l) cout << x << "," ; cout << '\n';
}
vector<int> v = {1, 2, 3, 4, 5}; // copy list-initialization
template <typename T>
void append(initializer_list<T> l) {
    v.insert(v.end(), l.begin(), l.end());
}

/**  */ 
void test_init_list(){
    printf("-------------init list\n");
    /** initializer_list */ 
    for (int x : {-1, -2, -3}) // the rule for auto makes this ranged-for work
        cout << x << ' '; 
    cout << '\n';
    t_init({1,23,3});
    t_init({1,2,3,4});
    append({6, 7, 8});      // list-initialization in function call
    printv(v);

}


/**  */ 
void signal_handler(int signal) {
    if (signal == SIGABRT) {
        cerr << "SIGABRT received\n";
    } 
    if (signal == SIGTERM) {
        cerr << "SIGTERM received\n";
    }
    //_Exit(EXIT_FAILURE);
    //exit(EXIT_FAILURE);
}
void test_signal(){
    printf("-------------signal \n");
    auto previous_handler = signal(SIGABRT, signal_handler);
    auto previous_handler1 = signal(SIGTERM, signal_handler);
    //raise(SIGTERM);
    //abort();  // Raise SIGABRT

}


/**  */ 
void f(int n1, int n2, int n3, const int& n4, int n5){
    cout <<"f called: "<< n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}
int g(int n1){
    return ++n1;
}
struct Foo {
    int data;
    Foo(int num = 10) : data(num) {}
    void print_sum(int n2)  {
        cout << "sum:" << data+n2 << '\n';
    }
};
struct func_obj{
    int operator()(int a, int b){   
        cout <<"(func obj:" << a+b << ")"; 
        return a + b;   } 
};

void test_bind(){
    printf("-------------bind\n");
    int n = 7;
//1. bind to func
    auto f1 = bind(f, _2, _1, 42, cref(n), n);
    f1(1, 2,1001, 1001); //  1001 is unused;  makes a call to f(2, 1, 42, n, 7)
    n = 10;
    f1(1, 2);
    // nested bind subexpressions share the placeholders
    auto f2 = bind(f, _3, bind(g, _2), _3, 4, 5);
    f2(10, 11, 12); // makes a call to f(12, g(11), 12, 4, 5)
    // bind to a pointer to member function
//2. bind to class member
    Foo foo;
    auto f3 = bind(&Foo::print_sum, &foo, _1);
    f3(5);
    // bind to a pointer to data member
    auto f4 = bind(&Foo::data, _1);
    cout << "data:"<< f4(foo) << '\n';

//3. bind to fun obj
    cout << "call func obj:" <<bind(func_obj(), _1, _2)(10,20)<<endl; //<int> is return type
    func_obj af;     
    cout <<"call ref func obj:"<< bind<int>(ref(af), _1, _2)(11, 22) << endl;     //object ref

}


/** template< class R, class... Args > * class function<R(Args...)>;
 * */ 
void print_num(int i) { cout << i << '\n'; }

void test_function(){
    printf("------------function\n");
//1. func/ lambda/ bind    
    //store func
    function<void(int)> f_display = print_num;
    f_display(-9);
    // store a lambda
    function<void()> f_display_42 = []() { print_num(42); };
    f_display_42();
    // store the result of a call to bind
    function<void()> f_display_31337 = bind(print_num, 31337);
    f_display_31337();
//2. class member data/ member func/
    // store a call to a member function
    Foo foo(314159);
    function<void(Foo&, int)> f_add_display = &Foo::print_sum; // 1st;
    f_add_display(foo, 1);
    // store a call to a data member accessor 
    function<int(Foo const&)> f_data = &Foo::data;
    cout << "data: " << f_data(foo) << '\n';
    // store a call to a member function and object
    function<void(int)> f_add_display2 = bind(&Foo::print_sum, foo, _1 ); //2nd
    f_add_display2(2);
    // store a call to a member function and object ptr
    function<void(int)> f_add_display3 = bind(&Foo::print_sum,&foo, _1 ); // 3th
    f_add_display3(3);
//3. func obj
    // store a call to a function object
    function<void(int,int)> f_display_obj = func_obj();
    f_display_obj(18,11);
}



/**  */ 
tuple<double, char, string> get_student(int id){
    if (id == 0) return make_tuple(3.8, 'A', "Lisa Simpson");
    if (id == 1) return make_tuple(2.9, 'C', "Milhouse Van Houten");
    if (id == 2) return make_tuple(1.7, 'D', "Ralph Wiggum");
    throw invalid_argument(" invalid_argument id");
}

void test_pair_tuple(){
    printf("\n-----------pair--tuple \n");
    /** pair  */ 
    auto p = make_pair(1, 3.14);
    cout << '(' << get<0>(p) << ", " << get<1>(p) << ")\n";
    //cout << '(' << get<int>(p) << ", " << get<double>(p) << ")\n";
    int n = 11; int a[5] = {1, 2, 3, 4, 5};
    auto p1 = make_pair(n, a[1]); n = 22; //only value in
    cout << "p1 is " << "(" << p1.first << ", " << p1.second << ")\n"; //11, 2
    auto p2 = make_pair(ref(n), a); //
    n = 33;
    cout << "p2 is " << "(" << p2.first << ", " << *(p2.second + 2) << ")\n"; //33,3
    /** tuple */ 
    auto student0 = get_student(2);
    cout << "GPA: " << get<0>(student0) << ",   "
            << "grade: " << get<1>(student0) << ",   "
            << "name: " << get<2>(student0) << '\n';
    double gpa1;    char grade1;    string name1;
    tie(gpa1, grade1, name1) = get_student(1);
    cout  << "GPA:" << gpa1 << ", g:"  << grade1 << ", n: " << name1 << '\n';


}

/**  */ 
struct A {
    A(int&& n) { cout << "rvalue overload, n=" << n << "\n"; }
    A(int& n)  { cout << "lvalue overload, n=" << n << "\n"; }
};
class B {
public:
    template<class T1, class T2, class T3>
    B(T1&& t1, T2&& t2, T3&& t3) :
        a1_{forward<T1>(t1)},
        a2_{forward<T2>(t2)},
        a3_{forward<T3>(t3)} {}
private:
    A a1_, a2_, a3_;
};
 
template<class T, class U>
unique_ptr<T> make_unique1(U&& u){
    return unique_ptr<T>(new T(forward<U>(u)));
}
template<class T, class... U>
unique_ptr<T> make_unique(U&&... u){
    return unique_ptr<T>(new T(forward<U>(u)...));
}
 

void test_move_forward(){
    printf("-------------move forward  \n");
    string str = "Hello";
    vector<string> v;
    v.push_back(move(str)); //After move, str is ""
    /** forward */ 
    auto p1 = make_unique1<A>(2); // rvalue
    int i = 1;
    auto p2 = make_unique1<A>(i); // lvalue
    cout << "B\n";
    auto t = make_unique<B>(2, i, 3); // r, l, r
}

/**  */ 
// a non-optimized way of checking for prime numbers:
#include <future>         // async, future
#include <chrono>         // chrono::milliseconds
bool is_prime (int x) {
  for (int i=2; i<x; ++i);// if (x%i==0) return false;
  return true;
}

void test_future()
{
  // call function asynchronously:
    printf("-------------functional \n");
    try{
        future<bool> fut = async (is_prime,444443); 

    // do something while waiting for function to set future:
    cout << "checking, please wait\n";
    //chrono::milliseconds span (100);
    //while (fut.wait_for(span)==future_status::timeout)
    //  cout << '.' << flush;
    bool x = fut.get();     // retrieve return value
    //cout << "\n444444443 " << (x?"is":"is not") << " prime.\n";
    } catch (exception& e) {  
        cout << "[exceptioncaught: "<< e.what() << "]\n";  
    } 
}

/**  */ 
void test_time(){
    printf("-------------time  \n");
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now - chrono::hours(24));
    printf("24 hours ago, the time was  %s",ctime(&now_c)) ;
 
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    cout << "Hello World\n";
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Printing took "
              << chrono::duration_cast<chrono::microseconds>(end - start).count() << "us.\n";

    /** chrono::duration */  
    constexpr auto year = 31556952ll; // seconds in average Gregorian year
    /** template< Rep, class Period = ratio<1>> class duration
     * Rep:  type representing the number of ticks ;
     * Period : a ratio representing the tick period (i.e. the number of seconds per tick) 
     */
    using shakes = chrono::duration<int, ratio<1, 100000000>>;
    using jiffies = chrono::duration<int, centi>; //ratio<1, 100>
    using microfortnights = chrono::duration<float, ratio<14*24*60*60, 1000000>>;
    using nanocenturies = chrono::duration<float, ratio<100*year, 1000000000>>;
 
    chrono::seconds sec(1);
    cout << "1 second is:\n";
     // integer scale conversion with no precision loss: no cast
    cout << chrono::microseconds(sec).count() << " microseconds\n"
              << shakes(sec).count() << " shakes\n"// count	returns the count of ticks
              << jiffies(sec).count() << " jiffies\n";
     // integer scale conversion with precision loss: requires a cast
    cout << chrono::duration_cast<chrono::minutes>(sec).count() << " minutes\n";
    // floating-point scale conversion: no cast
    cout << microfortnights(sec).count() << " microfortnights\n"
              << nanocenturies(sec).count() << " nanocenturies\n";
}


int main()
{
    /**  */ 
    test_init_list();
    /** bind */
    test_bind();
    test_function();
    /** tuple */
    test_pair_tuple();
    test_move_forward();
    /**  */ 
    test_future();
    /**  */ 
    test_time();
    /**  */ 
    test_signal();

}

