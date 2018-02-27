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
    string s1("my string");
    const char *sc("my string");
    string s5(sc, 4);   cout << s5 << endl;
    string s3(sc, 3, 4);cout << s3 << endl;
    string s4(sc);      cout << s4 << endl;
    string s6(4, 'Q');  cout << s6 << endl;
    /** string to dig */ 
    std::ostringstream oStream;
    oStream << 6.8;
    string s2d = oStream.str(); cout << s2d << endl;
    /**  */ 
    std::istringstream iStream("88.88");
    double d;
    if(iStream >> d) cout << d << endl;
    /**  */ 
    string sString("012345678");
    sString += "f";     //sString.reserve(200);
    cout << "Length: " << sString.length() << ";  Capacity: " << sString.capacity() << endl;

;

}

void test_string_alg(){
    cout << "-------------string test: \n";
    string name = "l2345 string";
    string sub = name.substr(6,5); // s = "strin"
    cout << name<< "; sub string:" << sub <<endl;
    name.replace(0,5,"nicholas"); // name becomes "nicholas string"
    name[0] = toupper(name[0]); // name becomes "Nicholas Stroustrup
    name.at(2) = '2';
    name.append(sub, 2, 5);  name.append("---------", 5);
    name.push_back('a'); // only one char 
    name.insert(20, "cccc");
    cout <<"after append:" << name << endl;
    

    string ss = "12345678";
    size_t dist = 3; // put number of characters read here
    auto x = stoi(ss,&dist); // x = 123 (an int)
    cout << x <<"--" <<  dist << endl; /** 12345678--8 */ 

    string s = "but I have heard it works even if you don't believe in it";
    s.replace(0,4,"1"); // erase initial "but "
    s.replace(s.find("even"),4,"------"); /** 4字符个数 */ 
    s.replace(s.find(" don't"),6,""); // erase by replacing with ""
    /** to c-style string */ 
    cout << const_cast<char*>(s.c_str()) << endl;
    char szBuf[20];
    int nLength = s.copy(szBuf, 5, 10);    szBuf[nLength]='\0';
    cout <<"c-style string:" << szBuf<< "; length:" <<nLength<<endl;
    
    string s2;
    s2.resize(4,'a');
    //int n2= s.copy(s2,3,0);
    int n2= s.copy(const_cast<char*>(s2.c_str()),3,0);
    cout << s2 << " len:" <<  n2 <<endl;
    cout << s << endl;
    char source[] = "Copy this!";  char dest[5]; // note dest is only 5 chars!
    strcpy(dest, source); // overflow! // Don’t use C-style strings
    /**  */ 
    string s3;
    const string sTwo("Two");
    s3.assign(sTwo);    cout <<" s3:" << s3 ;
    s3.assign("Four");  cout <<"; s3:" << s3 ;
    s3.assign(s, 2, 6);cout <<"; s3:" << s3 << endl;

}



#include <iomanip>
/** ostringstream */ 
void test_ostring(){
    cout << "--------------osstring test: \n";
    /** cin */ 
    //char strBuf[11]; cin.get(strBuf, 11);    cout << strBuf << endl;
    /**  */ 
    //std::cout.setf(ios::hex,ios::basefield); // try to turn on hex output
    std::cout <<"hex:" <<hex << 27 << "/ dec:" << dec << 27 << '\n';
    std::cout << std::setw(10) << right << -12345 << '\n';// print right justified
    /**  */ 
    ostringstream oss {"Label: ",ios::ate}; // write at end
    cout << oss.str() << '\n'; // writes "Label: "
    oss<<"/val/"; oss<<"/val2/";  //  appended after "Label: ")
    cout << oss.str() << '\n'; 
    ostringstream oss2 {"Label: "}; // write at beginning
    cout << oss2.str() << '\n'; //  overwrite
    oss2<<"/val/";oss2<<"/val2/";
    cout << oss2.str() << '\n'; 

    //istringstream derived : istream & stringstreambase; 
    //ostringstream derived : ostream & stringstreambase;
    //stringstream  derived :iostream & stringstreambase
    /**  */ 
    stringstream ss;
    ss << "en garde!" << endl; // insert
    string strValue;    ss >> strValue; //read
    cout << ss.str() <<endl;
    /** string <-> dig */  
    ss.str(""); // erase the buffer
    ss << "12345 67.89"; // insert a string of numbers into the stream
    int nValue; double dValue;
    ss >> nValue >> dValue;
    cout << nValue << " " << dValue << endl;
    ss << nValue << " " << dValue;
    string strValue1, strValue2;
    ss >> strValue1 >> strValue2; // read to string
    cout << strValue1 << " " << strValue2 << endl;

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

