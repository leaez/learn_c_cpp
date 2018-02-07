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


/** ostringstream */ 
void ostring_test()
{
    cout << "--------------osstring test: \n";
    ostringstream oss {"Label: ",ios::ate}; // write at end
    cout << oss.str() << '\n'; // writes "Label: "
    oss<<"val";
    cout << oss.str() << '\n'; // writes "Label: val" ("val" appended after "Label: ")
    ostringstream oss2 {"Label: "}; // write at beginning
    cout << oss2.str() << '\n'; // writes "Label: "
    oss2<<"val";
    cout << oss2.str() << '\n'; // writes "valel: " (val overwr ites "Label: ")
}

/** vector */ 
void vector_test()
{
    /**  */ 
    cout << "----------------vector test"<<endl;
    int v[] = {0,1,2,3,4,5,6,7,8,9};
    for (auto x : v) // for each x in v
        cout << x << ' ';       cout << '\n';

    enum class Color { red, blue, green }; //strongly typed 
    //Color cx = red; // error :
    Color cz = Color::red; // OK

    vector<int> z{1000,22};
    vector<int> x{222,333};
    vector<int> y{444,555};
    z = x; // we get a copy
    cout <<"after copy:" << x[0] << x[1] << endl;
    y = std::move(x); // we get a move
    cout <<"after move:" << y[0] << y[1] << endl;

    vector<int> v1 = {1, 2, 3, 4};
    vector<string> v2;
    cout << v1[1] << endl;

    vector<int> vi1 {1,3,5,7,9,7,5,3}; // vector initialized by five ints
    vector<string> vs(7); // vector initialized by sev en empty strings
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

    //copy(vi1.begin(),vi1.end(),vi2.begin());
    //for (auto& x : vi2) // implicit use of v.begin() and v.end()
    //    cout << x << '\n';


}

void string_test()
{
    /** string */
    cout << "-------------string test: \n";
    string name = "l2345 string";
    string sub = name.substr(6,5); // s = "strin"
    cout << name<< " after sub:" << sub <<endl;
    name.replace(0,5,"nicholas"); // name becomes "nicholas string"
    name[0] = toupper(name[0]); // name becomes "Nicholas Stroustrup
    cout << name << endl;

    string ss = "12345678";
    size_t dist = 3; // put number of characters read here
    auto x = stoi(ss,&dist); // x = 123 (an int)
    cout << x <<"--" <<  dist << endl; /** 12345678--8 */ 

    string s = "but I have heard it works even if you don't believe in it";
    s.replace(0,4,"1"); // erase initial "but "
    s.replace(s.find("even"),4,"--------"); /** 4字符个数 */ 
    s.replace(s.find(" don't"),6,""); // erase by replacing with ""
    cout << const_cast<char*>(s.c_str()) << endl;
    
    string s2;
    s2.resize(20,'a');
    //int n2= s.copy(s2,3,0);
    int n2= s.copy(const_cast<char*>(s2.c_str()),3,0);
    cout << s2 << " len:" <<  n2 <<endl;
    cout << s << endl;

    char source[] = "Copy this!";  char dest[5]; // note dest is only 5 chars!
    strcpy(dest, source); // overflow! // Don’t use C-style strings




}

/********************* 
 *
 * */ 
int main()
{
    /**  */ 
    vector_test();

    /** array  */ 
    cout << "-----------------array\n";
    std::array<int, 3> a2 = {1, 2, 3};
    std::array<int, 3> a1 {1, 2, 3} ; //  in C++11 
    array<string, 4> aa = {"Churchill", "Clare"};
    for (auto& x : a1) // implicit use of v.begin() and v.end()
        cout << x << '\n';
    cout << aa.size();

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
   
    /**  */ 
    string_test();
    /** osstream */ 
    ostring_test();
    /**  */ 

}
