#include <iostream>
#include <fstream>
#include <array>
#include <map>
#include <tuple>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <random>
#include <regex>
#include <unordered_set>

using namespace std;


/********************* 
 *
 * */ 
int main()
{
    std::vector<int> v(10, 2);
    std::vector<int> v1(3, 3);
    std::vector<int> v2(15, 4);
    std::partial_sum(v.cbegin(), v.cend(), v.begin());
    std::cout << "Among the numbers: ";
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
    /** all_of */ 
    if (std::all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
        std::cout << "All numbers are even\n";
    }
    /** none_of */ 
    if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<int>(), 
                                                     std::placeholders::_1, 2))) {
        std::cout << "None of them are odd\n";
    }
    /** copy  */ 
    std::for_each(v.begin(), v.end(), [](int &n){ n++; });
    //std::for_each_n(v.begin(), 4, [](int &n){ n++; });
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
    string cont{"fsdfs456789dfds"};
    string ss{"456789"};
    
    auto serch = std::search(cont.begin(), cont.end(), ss.begin(), ss.end());
    cout << serch-cont.end() <<"\n";
    std::copy_n(v.begin(), 4, std::back_inserter(v1));
    std::copy_backward(v1.begin(), v1.end(), v2.end());
    std::copy(v2.cbegin(), v2.cend(), std::ostream_iterator<int>(std::cout, " "));
    cout << "\n";

    std::array<int, 10> sr{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    std::replace(sr.begin(), sr.end(), 8, 88);
    std::copy(sr.cbegin(), sr.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
    std::replace_if(sr.begin(), sr.end(),std::bind(std::less<int>(), std::placeholders::_1, 5), 55);
    std::reverse(std::begin(sr), std::end(sr));
    std::copy(sr.cbegin(), sr.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    /** copy */ 
    auto last = std::unique(sr.begin(), sr.end());
    std::copy(sr.cbegin(), sr.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::string s1 = "The      striiiiiiiing    with many       spaces!";
    std::cout << "before: " << s1 << '\n';
    std::string s2;
    std::unique_copy(s1.begin(), s1.end(), std::back_inserter(s2),
                     [](char c1, char c2){ return c1 == 'i' && c2 == 'n'; });
     std::cout << "after:  " << s2 << '\n';

    /** partion  */ 
     std::array<int, 9> v3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto is_even = [](int i){ return i % 2 == 0; };
    std::cout.setf(std::ios_base::boolalpha);
    std::cout << std::is_partitioned(v3.begin(), v3.end(), is_even) << ' ';
 
    std::partition(v3.begin(), v3.end(), is_even);
    std::copy(v3.cbegin(), v3.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::is_partitioned(v3.begin(), v3.end(), is_even) << ' ';
 
    std::reverse(v3.begin(), v3.end());
    std::copy(v3.cbegin(), v3.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::is_partitioned(v3.begin(), v3.end(), is_even);
    
    /** product,  */ 
    std::vector<int> a{0, 1, 2, 3, 4};
    std::vector<int> b{5, 4, 2, 3, 1};
 
    int r1 = std::inner_product(a.begin(), a.end(), b.begin(), 0);
    std::cout << "Inner product of a and b: " << r1 << '\n';
 
    int r2 = std::inner_product(a.begin(), a.end(), b.begin(), 0,
                                std::plus<int>(), std::equal_to<int>());
    std::cout << "Number of pairwise matches between a and b: " <<  r2 << '\n';

    /** transform generate */ 
    std::cout << '\n';
    std::string st("hello");
    std::transform(st.begin(), st.end(), st.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    std::cout << st;

    int n=2;
    std::cout << '\n';
    std::generate(a.begin(), a.end(), [&n]{ return n=n*n; });
    std::copy(a.cbegin(), a.cend(), std::ostream_iterator<int>(std::cout, " "));
}
