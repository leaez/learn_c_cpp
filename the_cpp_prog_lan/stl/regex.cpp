#include <unistd.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <array>
#include <bitset>
#include <tuple>
#include <mutex>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <cassert>
#include <iterator>
#include <memory>
#include <chrono>
#include <ratio>

#include <cctype>
#include <regex>


using namespace std;
using namespace std::chrono;
using std::cout; // tell the compiler that cout means std::cout
#define MARK (cout << "--------------" <<'('<<__LINE__<<')' << '<' << __FUNCTION__ << '>' <<endl) 

#define printx(x) cout << #x " = " << int{x} << '\n'; 
template <typename T>
void print(std::vector <T> const &a) {
  for(auto x:a) cout  << x << ", "; 
  cout << endl;
}
/** */ 



void test_base()
{ MARK;
  regex pat1 {R"(\w+\d∗)"}; // no way of outputting the pattern in pat1
  string s1 {R"(\w+\d∗)"};
  regex pat2 {s1};
  cout << s1 <<  '\n'; // the pattern in pat2

  /** smatch  */ 
  regex pat3 ("(AAAA)(BBB)?");
  string s2 = "AAAA";
  smatch m;
  regex_search(s2,m,pat3);
  cout << boolalpha;
  cout << m[0].matched << '\n'; // true: we found a match
  cout << m[1].matched << '\n'; // true: there was a first sub_match
  cout << m[2].matched << '\n'; // false: no second sub_match

}


/**  */ 

void test_serach()
{MARK;
  
  smatch matches;
  string line {"12abc33"};
  regex pat1 {R"(^(\d+)([[:alpha:]]+)(\d+)$)"};
  regex pat2 {R"([\w]+)"};
  if (regex_match(line,matches,pat1))
    cout << "match whole line: " << matches[0] <<" ,"<< matches[1] <<" ,"<< matches[2] << '\n'; //line: 12abc33 ,12 ,abc
  if (!regex_match(line,matches,pat2))
    cout << "matc hline part: " << matches[0] << '\n';
  /** search */ 
  smatch m;
  if (regex_search(line,m,pat2))
    cout << "search: " << m[0]  <<" ,"<< m[1]  <<" ,"<< m[2]<< '\n'; //12abc33 , ,




}//destruct bbb here

/** */ 

void test_replace()
{MARK;

  /**regex_replace */ 
  string input {"aa cc x 1 y2 22 zaq 34567 11 ss"};
  regex pat {R"((\w+)\s(\d+))"}; // word space number
  string format {"{$1,$2}\n"};
  cout << regex_replace(input,pat,format);
  cout << regex_replace(input,pat,format,regex_constants::format_no_copy);
}

/** */ 

void test_iterator()
{MARK;
  /**regex_iterator */ 
  string input = "aa as; asd ++eˆasdf asdfg";
  regex pat {R"(\s+(\w+))"};
  for (sregex_iterator p(input.begin(),input.end(),pat); p!=sregex_iterator{}; ++p)
  cout << (*p)[1] << '\n';

  string input2 {"aa::bb::cc::dd:ee::ff"};
  regex pat2 {R"((\w+)(:+)(\w+))"};
  sregex_token_iterator end {};
  for (sregex_token_iterator p{input2.begin(),input2.end(),pat2,{1,2,3}}; p!=end; ++p)
    cout << ":"<< *p << '\n';
  /*for (sregex_iterator p(input2.begin(),input2.end(),pat2); p!=sregex_iterator{}; ++p)
    cout << ":"<< (*p)[1] << '\n';*/

}

/********************* 
 *
 * */ 
int main(int argc, char *argv[])
{
  if(argc != 2) { 
    cout << "1 : base; "<< endl
       << "2 : x; "<< endl;
      exit(0);}
  int i = atoi(argv[1]);
  switch(i){
  /**  */ 
  case 1: test_base();break;
  case 2: test_serach();break;
  case 3: test_replace();break;
  case 4: test_iterator();break;
  default:;
  }

}
