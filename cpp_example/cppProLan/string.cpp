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



void test_string_constr()
{
    /** string */
    cout << "-------------string test: \n";
    string sSource("my string");
    string sOutput(sSource, 3);
    cout << sOutput<< endl;
    string sOutput2(sSource, 3, 4);
    cout << sOutput2 << endl;

}

void test_string_alg(){
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




/** ostringstream */ 
void test_ostring()
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

   
/********************* 
 *
 * */ 
int main()
{   
    /**  */ 
    test_string_constr();
    /**  */ 
    test_string_alg();
    /** osstream */ 
    test_ostring();
    /**  */ 

}

