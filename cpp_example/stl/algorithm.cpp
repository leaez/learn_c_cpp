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
using namespace placeholders;
template <typename T> 
void printv(T &vi){
    for (auto& x :  vi) // implicit use of v.begin() and v.end()
        cout << x << "," ; cout << endl;
}
//#define MARK (printf("--------------%s (%d) - <%s>\n",__FILE__,__LINE__,__FUNCTION__)) 
#define MARK (cout << "--------------" <<'('<<__LINE__<<')' << '<' << __FUNCTION__ << '>' <<endl) 


void test_sequantial_access(){
    MARK;
    vector<int> v{0, 1, 2, 3, 4, 5,6};
    vector<int> v1(3, 3);
    vector<int> v2(15, 4);
    /** all_of */ 
    if (all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
        cout << "All numbers are even\n";    }
    /** none_of */ 
    if (none_of(v.cbegin(), v.cend(), bind(modulus<int>(),_1, 2))) {
        cout << "None of them are odd\n";    }
    /** any_of */ 
    if (std::any_of(v.cbegin(), v.cend(), [](int n){return (n%3 == 0); })) {
        std::cout << "At least one number is divisible by 3"<<endl;    }
    /** for_each */ 
    for_each(v.begin(), v.end(), [](int &n){ n++; });
    printv(v);
    //for_each_n(v.begin(), 4, [](int &n){ n++; });    printv(v); //c++17
    cout <<"count:" << count(v.begin(), v.end(), 3)<< endl;
    cout << "count if:" << count_if(v.begin(), v.end(), [](int i){ return i % 2 == 0; })<< endl;
    /** find */
    auto result1 = std::find(std::begin(v), std::end(v), 3);
    if (result1 != std::end(v)) {  std::cout << "v contains: " << *result1 << '\n';}
    
    std::vector<int> t1{1, 2, 3};
    auto result2 = std::find_end(v.begin(), v.end(), t1.begin(), t1.end());
    if (result2 != v.end()) {   std::cout << "subsequence found\n";}
    
    auto result3 = std::adjacent_find(v1.begin(), v1.end());
    if (result3 != v1.end()) { std::cout << "matching adjacent elements\n";}
    
    /** search  */ 
    string cont{"fsdfs456789dfds"};
    string ss{"456789"};
    auto serch = search(cont.begin(), cont.end(), ss.begin(), ss.end());
    if(serch != cont.end())
        cout << "search get elements:"<< serch-cont.end() <<"\n";
    if (binary_search(v.begin(), v.end(), 3)){/**if an element exists in a certain range   */ 
        cout << "got 3 "<<endl; }

}


array<int, 10> sr{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
void test_sequantial_modify(){
    MARK;
    /** copy  */ 
    std::vector<int> from_v(10);
    std::vector<int> to_v{1,2,3};
    std::iota(from_v.begin(), from_v.end(), 22);
    copy(sr.cbegin(), sr.cend(), ostream_iterator<int>(cout, " ")); //only print
    cout << '\n';
    copy(from_v.begin(),from_v.end(), back_inserter(to_v));cout<<"copy:"; printv(to_v);
    copy_n(from_v.begin(), 4, back_inserter(to_v));  printv(to_v); //copy 4 elements
    copy_backward(from_v.begin(), from_v.end(), to_v.end()); printv(to_v); // in backwards order 
    move_backward(from_v.begin(), from_v.end(), to_v.end()); printv(to_v); // in backwards order 
    printv(from_v);

    /**fill */
    fill(from_v.begin(),from_v.end(), 11);cout<<"fill:"; printv(from_v);
    fill_n(from_v.begin(), 5, 22);  printv(from_v);

    /** transform generate */ 
    string st("hello\n");
    transform(st.begin(), st.end(), st.begin(), /** applies a function to a range of elements  */ 
                   [](unsigned char c) { return toupper(c); });
    cout <<st;
    //assigns the results of successive function 
    int n=2; 
    generate(from_v.begin(), from_v.end(), [&n]{n++; return n*n; });cout<<"generate:"; printv(from_v);
    generate_n(from_v.begin(), 5, [n = 0] () mutable { return n++; }); printv(from_v);
    /** remove */ 
    string str1 = "Text with Some   Upaces12456789\n";
    //remove(str1.begin(), str1.end(), ' ');
    str1.erase(std::remove(str1.begin(), str1.end(), ' '), str1.end()); //erase make str short because of remove
    cout <<str1 ;
    str1.erase(remove_if(str1.begin(),str1.end(),[](unsigned char x){return std::isupper(x);}),str1.end());
    cout <<"after remove_if:" << str1 ;
    string str2 = "Text with some   spaces\n";
    remove_copy(str2.begin(), str2.end(),std::ostream_iterator<char>(std::cout), ' ');//remove ' '
    /** replace */ 
    replace(sr.begin(), sr.end(), 8, 88);cout<<"replace:"; printv(sr); //8->88
    replace_if(sr.begin(), sr.end(),bind(less<int>(), _1, 5), 55); printv(sr); // <5 -> 55
    replace_copy_if(sr.begin(), sr.end(),std::ostream_iterator<int>(std::cout, " "), //if / then copy
        [](int n){return n > 9;}, 99); cout <<endl; //if >9 -> 99 
    /** reverse */ 
    reverse(begin(sr), end(sr)); printv(sr);
    reverse_copy(begin(sr), end(sr), to_v.begin());cout<<"reverse:"; printv(to_v); //copy from end
    /** rotate */ 
    rotate(sr.begin(), sr.begin() + 1, sr.end());   cout<<"rotate:";printv(sr);//rotate left
    rotate(sr.rbegin(), sr.rbegin() + 1, sr.rend());printv(sr); //rotate right 
    /** unique */ 
    auto last = unique(sr.begin(), sr.end()); printf("unique:");printv(sr); //delete adjecent same element ;
    //sr.erase(last,sr.end());
    string s1 = "The      string    with many       spaces!";
    string s2;
    unique_copy(s1.begin(), s1.end(), back_inserter(s2), //copy if no consecutive duplicates
            [](char c1, char c2){ return c1 == ' ' && c2 == ' '; });
    cout << "before: " << s1 << '\n';
    cout << "after:  " << s2 << '\n';
    /**  */ 

}

void test_partition(){
    MARK;
    /** partion  */ 
     array<int, 9> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto is_even = [](int i){ return i % 2 == 0; };
    cout.setf(ios_base::boolalpha);
    cout << is_partitioned(v1.begin(), v1.end(), is_even) << endl;
    partition(v1.begin(), v1.end(), is_even); printv(v1);
    cout << is_partitioned(v1.begin(), v1.end(), is_even) << endl;
    int true_arr [5] = {0};    int false_arr [5] = {0};
    partition_copy(std::begin(v1), std::end(v1), std::begin(true_arr),std::begin(false_arr),
                        [] (int i) {return i > 5;});
    printv(true_arr); printv(false_arr);

    std::vector<int> v2{0, 0, 3, 0, 2, 4, 5, 0, 7};
    stable_partition(v2.begin(), v2.end(), [](int n){return n>3;});  //preserving their relative order
    printv(v2);

    auto p = std::partition_point(v1.begin(), v1.end(), is_even);  //position to partition
    std::copy(v1.begin(), p, std::ostream_iterator<int>(std::cout, " "));
    cout <<endl;

}

void test_sort(){
    MARK;
    int digits[] = {3, 1, 4, 1, 5};
    cout << is_sorted(std::begin(digits), std::end(digits)) << '\n';
    sort(std::begin(digits), std::end(digits));
    cout << is_sorted(std::begin(digits), std::end(digits)) << '\n';
    array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    partial_sort(s.begin(), s.begin() + 3, s.end());
    printv(s);
    vector<int> v{5, 6, 4, 3, 2, 6, 7, 9, 3};
    std::nth_element(v.begin(), v.begin() + v.size()/2, v.end()); /** nth = v.size()/2,  */ 
    cout<<"atter nth:";printv(v); /** after sort : before nth will smaller than nth; after nth will bigger than nth */ 
    std::nth_element(v.begin(), v.begin()+1, v.end(), std::greater<int>());
    std::cout << "The second largest element is " << v[1] << '\n';
    printv(v);

    /**  */ 
    std::vector<int> v1 = {1, 2, 3, 4, 5}; 
    std::vector<int> v2 = {3, 4, 5, 6, 7}; 
    cout <<"include:" << includes(v1.begin(),v1.end(),v2.begin(),v2.end()) <<endl; // v1 &&v2  must sorted range
    vector<int> dest1;
    set_union(v1.begin(), v1.end(),v2.begin(), v2.end(),std::back_inserter(dest1));//v1 &&v2  must sorted range
    cout<<"union:"; printv(dest1);


}


void test_numeric(){
    MARK;
    /** max */ 
    cout << max(1, 9999) <<endl;
    vector<int> v{5, 6, 4, 3, 2, 6, 7, -9, 3};
    vector<int>::iterator result;
    result = max_element(v.begin(), v.end());
    cout << *result <<endl;
    result = max_element(v.begin(), v.end(), [](int a, int b){return abs(a) < abs(b);} );
    cout << *result <<endl;
    pair<int, int> bounds = minmax(std::rand() % v.size(),std::rand() % v.size());
    cout << "minmax: f:" << bounds.first << ", s:" <<bounds.second <<endl;
    auto result1 = std::minmax_element(v.begin(), v.end()); /**  smallest and the largest elements in a range  */ 
    std::cout << "min element at: " << (result1.first - v.begin()) << '\n';


    /** accumulate */ 
    cout << "accu sum:" << accumulate(v.begin(), v.end(), 0) << endl;
    cout << "accu pro:" << accumulate(v.begin(), v.end(), 1, std::multiplies<int>())<< endl; //1 is init value
    /** product,  */ 
    vector<int> a{0, 1, 2, 3, 4};
    vector<int> b{5, 4, 2, 3, 1};
    int r1 = inner_product(a.begin(), a.end(), b.begin(), 0);
    cout << "Inner product of a and b: " << r1 << '\n';
    int r2 = inner_product(a.begin(), a.end(), b.begin(), 0, plus<int>(), equal_to<int>());
    cout << "Number of pairwise matches between a and b: " <<  r2 << '\n';

    adjacent_difference(v.begin(), v.end(), v.begin()); //
    printv(v);
    partial_sum(v.cbegin(), v.cend(), v.begin()); // add previous
    printv(v);
    
        


}

int main(){
    /**  */ 
    test_sequantial_access();
    /**  */ 
    test_sequantial_modify();
    /**  */ 
    test_partition();
    /**  */ 
    test_sort();
    test_numeric();
    /**  */ 




}
