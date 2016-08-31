#include <iostream>
#include <array>
#include <tuple>

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost; 

bool NotH(const char &ch)   {if(ch == ' ' || ch == 'H' || ch == 'h')
         return true;     else      return false;}


int main(int argc, char* argv[])
{
    std::string stringNumber = "2.0";
    float floatNumber = boost::lexical_cast<float>(stringNumber);  // string to float
    std::cout << floatNumber << std::endl;

    /** format */ 
    boost::format fff = boost::format("%1% %2%  %3% %2% %1% \n") ; //  %3%  is 3rd argu
    cout << fff % 1 % 2 % 3 << endl;
  
    cout << boost::format("\n\n%s" 
            "%1t 十进制 = [%d]\n" 
            "%1t 格式化的十进制 = [%5d]\n" 
            "%1t 格式化十进制，前补'0' = [%05d]\n" 
            "%1t 十六进制 = [%x]\n" 
            "%1t 八进制 = [%o]\n" 
            "%1t 浮点 = [%f]\n" 
            "%1t 格式化的浮点 = [%3.3f]\n" 
            "%1t 科学计数 = [%e]\n" 
            ) % "example :\n" % 15 % 15 % 15 % 15 % 15 % 15.01 % 15.01 % 15.01 << endl; 
   
    /** to_upper */ 
    string str2("Hello");
    string str1(" hello world! ");
    to_upper(str1);  /**   str1 == " HELLO WORLD! " */
    str2 = to_upper_copy(str1);  // str2 == " HELLO WORLD! "
    
    /** 去掉字符 */ 
    trim_left(str1);      // str1 == "hello world! " del space   
    trim_left_if(str1, NotH);      // str1 == "ello world! "将字符串开头的符合的“谓词”字符去掉
    /** starts_with() 、ends_with() 、contains() 、equals() 、lexicographical_compare() 、all() */ 
    bool result = istarts_with(str1, str2); // result == true
    //ends_with()
    bool result1 = contains(str1, str2); // result == true

    cout << str1 << str2  << endl;

    equals(str1, str2);  // 判断两个字符串是否相等
    //iequals()  (不区分大小写)
    char text[]="hello";    
    bool is_all_lower = boost::algorithm::all(text, is_lower()); // is lower
    boost::format fmt = boost::format("<%1%> %2% in the lower case") % text % (is_all_lower? "is": "is not");
    std::cout << fmt << std::endl;

    /** find()、first()、find_last()、find_nth() 、find_head()、find_tail()、find_token()、find_regex()  */ 
    //bool result = all(str1, is_123digit); // result == true;  is_123digit is fun reture bool
    //iterator_range<string::iterator> result2 = find_first(str1,"ll");
    //transform( result2.begin(), result2.end(), result2.begin(), ToUpper ); // str1 == "heLLo dolly!"
    auto result3 = find_first("hello world", "world");
    cout << result3 << endl;

    /**replace_all() 、replace_first()、 replace_last()  */ 
    cout << replace_all_copy(string("hello world"), "l", "-") << endl; 

    /** joint  split */
    std::array<string, 3> k = {"hello", "world", "123"}; /** must c++11 */ 
    cout << join(k, "-") <<endl;     // hello-world-123
    
    str1 = "hello -*-ABC-*- goodbye";
    vector<string> SplitVec; 
    split(SplitVec, str1, is_any_of("-*"), token_compress_on);
    copy(SplitVec.begin(), SplitVec.end(),std::ostream_iterator<string>(std::cout, " ")); // print vector !
    cout << endl;

    /** array */
    std::array<int, 3> a = {1,2,3};
    //std::array<std::string, 2> a = { std::string("a"), "b" }; /** = compare  */ 
    std::reverse_copy(a.begin(), a.end(),std::ostream_iterator<int>(std::cout, " "));//逐个写入 std::basic_ostream 

    /** tuple */ 
    auto foo = std::make_tuple("bar", "foo", "can");
    std::cout << std::get<0>(foo) << std::get<1>(foo) << std::get<2>(foo)<<endl;
    
    /** ostream_iterator */ 
    std::ostream_iterator<int> i1(std::cout, ", ");//ostream_iterator(ostream_type& stream, const CharT* delim)
    std::fill_n(i1, 5, 123); // pirnt: 123, 123, 123, 123, 123,  fill 5 * 123, delim :, 


    return 0;
}
