#include <iostream>

#include <fstream>
#include <array>
#include <string>
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

#define MARK (cout << "--------------" <<'('<<__LINE__<<')' << '<' << __FUNCTION__ << '>' <<endl) 

/**
 * regex 	basic_regex<char>   //regular expression object 
 * std::cmatch 	std::match_results<const char*>   // one regular expression match, 
 * std::smatch 	std::match_results<std::string::const_iterator>
 * regex_match  //match a regex to an entire character sequence/ only considers full matches 
 *  regex_search	//match a regex to any part of a character sequence
 *
 * */ 

void test_regex(){
    MARK;
#if 1
    regex pat ("(\\w{4})(\\s{1})(\\w{4})?");
   /* try { //only gcc 4.9 or above for regex
        regex pat ("(\\w{4})(\\s{1})(\\w{4})?");  
    } catch (const std::regex_error& e) {
        cout << "e catch :" << e.what() << endl;}
        */
    string rs = "AAaa 123456-45678";
    smatch m;
    regex_search(rs,m,pat);
    cout << boolalpha;
    cout << m[0].matched << m[0] << '\n'; // true: we found a match
    cout << m[1] << m[1].matched << '\n'; // true: there was a first sub_match
    cout << m[2] << m[2].matched << '\n'; // true: there was a first sub_match

    regex color_regex("#([a-f0-9]{2})""([a-f0-9]{2})""([a-f0-9]{2})");  
    smatch color_match;  
    string line = {"Roses are #ff0000 xxx"};
    if(regex_search(line, color_match, color_regex)) {
      cout << "Prefix:'" << color_match.prefix() << "'\n";
      for (size_t i = 0; i < color_match.size(); ++i) 
        cout << i << ": " << color_match[i] << '\n';
      cout << "Suffix: '" << color_match.suffix() << "\'\n\n";
    }
#endif 
}

/** regex_search  */ 
#if 1
void test_reg0()
{
    MARK;
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

/** regex_replace */ 
void test_replace()
{
    MARK;
    string input {"x 1 y2 22 zaq 34567"};
    regex pat {"(\\w+)\\s(\\d+)"}; // word space number
    string format {"{$1,$2}\n"};
    cout << regex_replace(input,pat,format);

  string text = "Quick brown fox";   regex vowel_re("a|e|i|o|u"); //例子
    regex_replace(ostreambuf_iterator<char>(cout),text.begin(), text.end(), vowel_re, "*");
    cout << '\n' << regex_replace(text, vowel_re, "[$&]") << '\n';
}

/** sregex_iterator */ 
void test_reg2()
{
    string input = "aa as; asd ++e^asdf asdfg";
    regex pat {R"(\s+(\w+))"};
    for (sregex_iterator p(input.begin(),input.end(),pat); p!=sregex_iterator{}; ++p)
        cout << (*p)[1] << '\n';

    std::string s = "Some people, when confronted with a problem, think "
        "\"I know, I'll use regular expressions.\" "
        "Now they have two problems.";
    
    std::regex word_regex("(\\S+)");
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        //std::cout << (*i)[1] << "+" << endl;
        //std::smatch match = *i;
        std::string match_str = (*i).str();// match.str();
        if (match_str.size() > 6) 
        {
            //std::cout << "+  " << match_str << '\n';
        }
    }
 
    std::regex long_word_regex("(\\w{7,})");
    //std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
    //std::cout << new_s << '\n';

}

#endif



/********************* 
 *
 * */ 
int main()
{
   
    test_regex();
    /** regex */ 
#if 1
    /** search */ 

    //test_reg0();

    /** replace */ 
    test_replace();
    /** iterator */ 
    //test_reg2();
#endif
    
}
