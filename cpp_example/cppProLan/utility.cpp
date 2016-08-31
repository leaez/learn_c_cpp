#include <iostream>
#include <vector>
#include <initializer_list>
#include <csignal>
#include <memory>
#include <functional>
#include <tuple>

using namespace std;
using namespace std::placeholders;

void t_init(initializer_list<int> l) {
    cout << "constructed with a " << l.size() << "-element list\n";
    for (int x : l)cout << x ; cout << '\n';
}

void fnoe() noexcept;
//void baz() noexcept { throw 42; }  

void signal_handler(int signal) 
{
    if (signal == SIGABRT) {
        std::cerr << "SIGABRT received\n";
    } 
    //std::_Exit(EXIT_FAILURE);
    std::exit(EXIT_FAILURE);
}

void f(int n1, int n2, int n3, const int& n4, int n5)
{
    std::cout <<"---"<< n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}
 
int g(int n1)
{
    return n1;
}
 
struct Foo {
    void print_sum(int n1, int n2)
    {
        std::cout << n1+n2 << '\n';
    }
    int data = 10;
};

std::tuple<double, char, std::string> get_student(int id)
{
    if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
    if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
    if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
    throw std::invalid_argument("id");
}


int main()
{
    /** initializer_list */ 
    for (int x : {-1, -2, -3}) // the rule for auto makes this ranged-for work
        std::cout << x << ' '; 
    cout << '\n';
    t_init({1,23,3});

    /**  */ 
    //baz();

    /** abort */ 
    auto previous_handler = std::signal(SIGABRT, signal_handler);
    //std::abort();  // Raise SIGABRT
    /** bind */
    int n = 7;
    auto f1 = std::bind(f, _2, _1, 42, std::cref(n), n);
    n = 10;
    f1(1, 2);
    auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
    f2(23,11, 12);

    /**  */ 
    std::string str = "Hello";
    std::vector<std::string> v;
    v.push_back(std::move(str));
    std::cout << "After move, str is \"" << str << "\"\n";

    /** tuple */
    auto student0 = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student0) << ", "
              << "grade: " << std::get<1>(student0) << ", "
              << "name: " << std::get<2>(student0) << '\n';
}
