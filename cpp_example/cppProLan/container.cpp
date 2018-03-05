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
template <typename T> 
void printv(T &vi){
    for (auto& x :  vi) // implicit use of v.begin() and v.end()
        cout << x << "," ; cout << '\n';
}

/** vector */ 
void test_vector()
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
    //cout  << x[1] ; //error! after move  is delete!!

    vector<int> vi1 {1,3,5,7,9,7,5,3}; // vector initialized by five ints
    vi1[15] = 2; // no bounds checking!!!
    vi1.at(7) = 3; // does bounds checking ; throw std::out_of_range
    vi1.resize(5); //1,3,5,7,9
    vector<string> vs(7); // vector initialized by seven empty strings
    vector<int> vi2;
    vi2 = {2,4,6,8,6,4,2}; // assign sequence of four ints to vi2
    auto cnt = find_if(vi1.begin(),vi1.end(),[](int& x) { return (x==7);}) ;
    if(cnt != vi1.end())
        cout <<"find:" << *cnt << endl; /**return iterator */ 
    replace(vi1.begin(),vi1.end(),3,8); //1,3,5,7,9 -> 1, 8, 5, 7, 9, 
    //generate(begin(vi2),end(vi2),Randint{});
    printv(vi1);
    vi2.assign(&vi1[1],&vi1[4]); // assign the sequence 8,5,7 to vi2(resize to 3)
    vi2.push_back(100);
    printv(vi2);
    vi1.assign(3,11); printv(vi1); // vi1: 11,11,11 
    vi2.pop_back(); cout << "vi2:"; printv(vi2);


    vector<string> vs2;
    vs2 = {"The Eagle", "The Bird and Baby"}; // assign two str ings to vs2
    //vs2.assign("The Bear","The Bull and Vet");// run-time error
    cout <<"vs size:" << vs2.size() << "cap:" << vs2.capacity() << "\n"; //2; 2

}


/**  */ 
void test_array(){
    /** array  */ 
    cout << "-----------------array test :\n";
    std::array<int, 3> a2 = {1, 5 }; printv(a2); // 1,5,0 
    std::sort(a2.begin(), a2.end());
    std::array<int, 3> a1 {1, 2, 3} ; //  in C++11
    cout << "a1:" << a1.back() << a1.front() <<", size:" <<a1.size() <<endl; 
    array<string, 4> as = {"Churchill", "Clare"};//Churchill,Clare,,, 2 empty
    printv(as);
    cout <<"size:" << as.size() << "at:" << as.at(1) <<endl;
    as.fill("fill");
    printv(as);

    
}

void test_map()
{
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

void test_set(){
    /** set */ 
    cout << "-------------set:\n";
    std::unordered_set<int> example = {1, 2, 3, 4};
    auto search = example.find(2);
    if(search != example.end()) {
        std::cout << "unordered set Found " << (*search) << '\n';
    }

}

/********************* 
 *
 * */ 
int main()
{
    /**  */ 
    test_vector();
    /**  */ 
    test_array();

    /** set */ 
    test_set();
    /**  */ 
    test_map();

}
