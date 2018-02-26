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
#include <cstring>

using namespace std;


/** vector */ 
void vector_test()
{
    /**  */ 
    cout << "----------------vector test"<<endl;
    int v[] = {0,1,2,3,4,5,6,7,8,9};
    for (auto x : v) // for each x in v
        cout << x << ' ';       cout << '\n';

    std::vector<int> vl = {1, 2, 3, 4, 5, 6, 7};
    for(const int &i : vl) // access by const reference
        std::cout << i << ' ';
    for(int n: {0, 1, 2, 3, 4, 5}){
        cout << n ; }        cout <<endl;

    vector<int> z{1000,22};
    vector<int> x{222,333};
    vector<int> y{444,555};
    z = x; // we get a copy
    cout <<"after copy:" << x[0] << x[1] << endl;
    y = std::move(x); // we get a move
    cout <<"after move:" << y[0] << y[1] << endl;

    vector<int> vi1 {1,3,5,7,9,7,5,3}; // vector initialized by five ints
    vi1[15] = 2; // no bounds checking!!!
    vi1.at(7) = 3; // does bounds checking ; throw std::out_of_range
    vi1.resize(5); 
    vector<string> vs(7); // vector initialized by seven empty strings
    vector<int> vi2;
    vi2 = {2,4,6,8,6,4,2}; // assign sequence of four ints to vi2
    auto cnt = find_if(vi1.begin(),vi1.end(),[](int& x) { return (x==7);}) ;
    cout << *cnt << "if\n"; /**返回 iterator */ 
    replace(vi1.begin(),vi1.end(),3,8);
    
    //generate(begin(vi2),end(vi2),Randint{});
    for (auto& x : vi1) // implicit use of v.begin() and v.end()
        cout << x ; cout << '\n';

    vi2.assign(&vi1[1],&vi1[4]); // assign the sequence 3,5,7 to vi2
    vector<string> vs2;
    vs2 = {"The Eagle", "The Bird and Baby"}; // assign two str ings to vs2
    //vs2.assign("The Bear","The Bull and Vet");// run-time error
    cout << vi2.size() << vi2.capacity() << "\n";




}


/**  */ 
void array_test(){
    /** array  */ 
    cout << "-----------------array test :\n";
    std::array<int, 3> a2 = {1, 5, 3};
    std::sort(a2.begin(), a2.end());
    std::array<int, 3> a1 {1, 2, 3} ; //  in C++11 
    array<string, 4> aa = {"Churchill", "Clare"};
    for (auto& x : a1) // implicit use of v.begin() and v.end()
        cout << x << '\n';
    cout <<"size:" << aa.size() << "at:" << aa.at(1) <<endl;
    
}


/********************* 
 *
 * */ 
int main()
{
    /**  */ 
    vector_test();
    /**  */ 
    array_test();

    /** set */ 
    cout << "-------------set:\n";
    std::unordered_set<int> example = {1, 2, 3, 4};
    auto search = example.find(2);
    if(search != example.end()) {
        std::cout << "unordered set Found " << (*search) << '\n';
    }

    /** map emplace */ 
    cout << "-------------map\n";
    std::map<std::string, std::string> m;
    m.emplace(std::make_pair(std::string("a"), std::string("a")));
    m.emplace(std::make_pair("b", "abcd"));
    m.emplace("d", "ddd");
    // uses pair's piecewise constructor
    m.emplace(std::piecewise_construct,
              std::forward_as_tuple("c"),
              std::forward_as_tuple(10, 'c'));
    for (const auto &p : m) {
        std::cout << p.first << " => " << p.second << '\n';
    }
   

}
