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
#if 1
void test_reg0()
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
        if (regex_search(line, matches, pat)) {
            cout << lineno << ": " << matches[0] << '\n'; // the complete match
            if (1<matches.size() && matches[1].matched)
                cout << "\t: " << matches[1] << '\n';// submatch
        }
    }

}

void test_reg1()
{
    string input {"x 1 y2 22 zaq 34567"};
    regex pat {"(\\w+)\\s(\\d+)"}; // word space number
    string format {"{$1,$2}\n"};
    cout << regex_replace(input,pat,format);
}

void test_reg2()
{
    string input = "aa as; asd ++e^asdf asdfg";
    regex pat {R"(\s+(\w+))"};
    for (sregex_iterator p(input.begin(),input.end(),pat); p!=sregex_iterator{}; ++p)
        cout << (*p)[1] << '\n';
}

#endif

void test_reg3()
{
    cout << "-----------test3 \n";
    std::string s = "Some people, when confronted with a problem, think "
        "\"I know, I'll use regular expressions.\" "
        "Now they have two problems.";
    
    std::regex word_regex("(\\S+)");
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        if (match_str.size() > 6) {
            std::cout << "+  " << match_str << '\n';
        }
    }
 
    std::regex long_word_regex("(\\w{7,})");
    std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
    std::cout << new_s << '\n';

}




/********************* 
 *
 * */ 
int main()
{
   
    /** regex */ 
#if 1
    regex pat ("(\\w{4})\\s{1}(\\w{4})?");
    string rs = "AA 123456-45678";
    smatch m;
    regex_search(rs,m,pat);
    cout << boolalpha;
    cout << m[0].matched << m[0] << '\n'; // true: we found a match
    cout << m[1] << m[1].matched << '\n'; // true: there was a first sub_match
    cout << m[2] << m[2].matched << '\n'; // true: there was a first sub_match

    test_reg0();
    test_reg1();
    test_reg2();
#endif
    
    /**  */ 
    test_reg3();
}
