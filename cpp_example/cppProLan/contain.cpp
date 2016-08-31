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


/** regex */ 

void test2()
{
    ostringstream oss {"Label: ",ios::ate}; // write at end
    cout << oss.str() << '\n'; // writes "Label: "
    oss<<"val";
    cout << oss.str() << '\n'; // writes "Label: val" ("val" appended after "Label: ")
    ostringstream oss2 {"Label: "}; // write at beginning
    cout << oss2.str() << '\n'; // writes "Label: "
    oss2<<"val";
    cout << oss2.str() << '\n'; // writes "valel: " (val overwr ites "Label: ")
}



/********************* 
 *
 * */ 
int main()
{
    /**  */ 
    vector<int> vi1 {1,3,5,7,9,7,5,3}; // vector initialized by five ints
    vector<string> vs(7); // vector initialized by sev en empty strings
    vector<int> vi2;
    vi2 = {2,4,6,8,6,4,2}; // assign sequence of four ints to vi2
    auto cnt = find_if(vi1.begin(),vi1.end(),[](int& x) { return (x==7); }) ;
    cout << *cnt << "if\n";
    replace(vi1.begin(),vi1.end(),3,8);
    
    //generate(begin(vi2),end(vi2),Randint{});
    for (auto& x : vi1) // implicit use of v.begin() and v.end()
        cout << x ; cout << '\n';

    vi2.assign(&vi1[1],&vi1[4]); // assign the sequence 3,5,7 to vi2
    vector<string> vs2;
    vs2 = {"The Eagle", "The Bird and Baby"}; // assign two str ings to vs2
    //vs2.assign("The Bear","The Bull and Vet");// run-time error
    cout << vi2.size() << vi2.capacity() << "\n";

    //copy(vi1.begin(),vi1.end(),vi2.begin());
    //for (auto& x : vi2) // implicit use of v.begin() and v.end()
    //    cout << x << '\n';

    /** array  */ 
    cout << "-----------------array\n";
    std::array<int, 3> a2 = {1, 2, 3};
    std::array<int, 3> a1 {1, 2, 3} ; //  in C++11 
    array<string, 4> aa = {"Churchill", "Clare"};
    for (auto& x : a1) // implicit use of v.begin() and v.end()
        cout << x << '\n';
    cout << aa.size();

    /** set */ 
    std::unordered_set<int> example = {1, 2, 3, 4};
    auto search = example.find(2);
    if(search != example.end()) {
        std::cout << "unordered set Found " << (*search) << '\n';
    }

    /** map emplace */ 
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

    /** string */
    string ss = "12345678";
    size_t dist = 3; // put number of characters read here
    auto x = stoi(ss,&dist); // x = 123 (an int)
    cout << x <<"--" <<  dist<< endl;

    string s = "but I have heard it works even if you don't believe in it";
    s.replace(0,4,"1"); // erase initial "but "
    s.replace(s.find("even"),4,"--------");
    s.replace(s.find(" don't"),6,""); // erase by replacing with ""
    string s2;
    s2.resize(20,'a');
    cout << const_cast<char*>(s.c_str()) << endl;
    //int n2= s.copy(s2,3,0);
    int n2= s.copy(const_cast<char*>(s2.c_str()),3,0);
    cout << s2 << "\n" <<  n2 <<endl;
    cout << s << endl;
    
    /** regex */ 
    /** osstream */ 
    test2();
    //for (int i; cin>>i && 0<i;)
    //    cout << i << '\n';
    
    /**  */ 

}
