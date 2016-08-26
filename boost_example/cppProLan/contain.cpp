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

using namespace std;

void use()
{
    ifstream in("file.txt"); // input file
    if (!in) cerr << "no file\n";
        //exit();
      regex pat {"\\w{2}\\s*\\d{5}(-\\d{4})?"}; // U.S. postal code pattern
    //regex pat {R"(\w{2}\s*\d{5}(-\d{4})?)"};
    int lineno = 0;
    for (string line; getline(in,line);) {
        ++lineno;
        cout << line << endl;
        smatch matches; // matched strings go here
    //    regex_search(line, matches, pat);
    //    cout << matches[0]<< endl;
    //    cout << matches[1]<< endl;
    //    cout << matches[2]<< endl;
    

#if 1
        if (regex_search(line, matches, pat)) {
            cout << lineno << ": " << matches[0] << '\n'; // the complete match
            if (1<matches.size() && matches[1].matched)
                cout << "\t: " << matches[1] << '\n';// submatch
        }
    }
#endif

}

void test1()
{
    string input {"x 1 y2 22 zaq 34567"};
    regex pat {"(\\w+)\\s(\\d+)"}; // word space number
    string format {"{$1,$2}\n"};
    cout << regex_replace(input,pat,format);
}

void test()
{
    string input = "aa as; asd ++e^asdf asdfg";
    regex pat {R"(\s+(\w+))"};
    for (sregex_iterator p(input.begin(),input.end(),pat); p!=sregex_iterator{}; ++p)
        cout << (*p)[1] << '\n';
}

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
    vector<int> vi1 {1,3,5,7,9,7,5,3}; // vector initialized by five ints
    vector<string> vs(7); // vector initialized by sev en empty strings
    vector<int> vi2;
    vi2 = {2,4,6,8,6,4,2}; // assign sequence of four ints to vi2
    auto cnt = find_if(vi1.begin(),vi1.end(),[](int& x) { return (x==7); }) ;
    cout << *cnt << "if\n";
    replace(vi1.begin(),vi1.end(),3,8);
    
    //generate(begin(vi2),end(vi2),Randint{});
    for (auto& x : vi1) // implicit use of v.begin() and v.end()
        cout << x << '\n';


    vi2.assign(&vi1[1],&vi1[4]); // assign the sequence 3,5,7 to vi2
    vector<string> vs2;
    vs2 = {"The Eagle", "The Bird and Baby"}; // assign two str ings to vs2
    //vs2.assign("The Bear","The Bull and Vet");// run-time error
    cout << vi2.size() << vi2.capacity() << "\n";

    //copy(vi1.begin(),vi1.end(),vi2.begin());
    //for (auto& x : vi2) // implicit use of v.begin() and v.end()
    //    cout << x << '\n';

    /**  */ 
    array<string, 4> aa = {"Churchill", "Clare"};
    for (auto& x : aa) // implicit use of v.begin() and v.end()
        cout << x << '\n';

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
    /**  */ 
    use();
    regex pat ("(\\w{4})\\s{1}(\\w{4})?");
    string rs = "AA 123456-45678";
    smatch m;
    regex_search(rs,m,pat);
    cout << boolalpha;
    cout << m[0].matched << m[0] << '\n'; // true: we found a match
    cout << m[1] << m[1].matched << '\n'; // true: there was a first sub_match
    cout << m[2] << m[2].matched << '\n'; // true: there was a first sub_match

    test1();
    test();

    test2();

    for (int i; cin>>i && 0<i;)
        cout << i << '\n';

}
