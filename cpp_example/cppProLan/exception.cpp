#include <iostream>
#include <cassert>
#include <exception> // for std::exception

using namespace std;



void test_exception(){
    cout << "************* exception test. " << endl;
    /** exception  */ 
    //decouple handling of errors or  exceptional from the typical control flow

    try{ throw -1; // throw integer value        throw ENUM_INVALID_INDEX; // throw an enum 
    }catch(int x){
        std::cerr << "We caught an int exception with value: " << x << std::endl;
    }
    try{throw "error string"; // throw C-style string    throw dX; // throw a double 
    }catch(const char* str){
        std::cerr << "We caught an string exception with value: " << str << std::endl;
    }catch (...){ // catch-all handler
		std::cout << "We caught an exception unknown type\n";
	}

}

/**  */ 
class ArrayExcpt{
private:
	std::string m_error;
public:
	ArrayExcpt(std::string error): m_error(error){	}
    const char* getError() { return m_error.c_str(); }
};
class IntArr{
private:int m_data[3]; // assume array is length 3 for simplicity
public:	IntArr() {}
	int& operator[](const int index){
		if (index < 0 || index >= 3)throw ArrayExcpt("Invalid index"); //outside try block
		return m_data[index];} 
};

//many inherit from exception class :like: std::string can throw std::bad_alloc. A failed dynamic_cast will throw std::bad_cast.
//Deriving your own classes from std::exception
class ArrayException: public std::exception{
private:
	std::string m_error;
public:
	ArrayException(std::string error): m_error(error){}
    const char* what() { return m_error.c_str(); } // return the std::string as a const C-style string
};
class IntArray{
private:int m_data[3]; // assume array is length 3 for simplicity
public:	IntArray() {}
	int& operator[](const int index){
		if (index < 0 || index >= 3)throw ArrayException("Invalid index"); //outside try block
		return m_data[index];} 
};


void test_exception_class(){
    cout << "\n************* test class exception . " << endl;
    IntArr ar;
    try{
        int i = ar[5];
    }catch(ArrayExcpt ex){
        cout << "catch some exception:" << ex.getError() << endl;
    }
    IntArray arr;
    try{
        int i = arr[5];
    }catch(ArrayException ex){
        cout << "catch inherit Standard exception:" << ex.what() << endl;
    }

    try{
        std::string s;
        s.resize(-1); // will trigger a std::bad_alloc
    }catch (std::exception &exception){
		std::cerr << "Standard exception: " << exception.what() << '\n';//what() that returns a C-style string
	}

}

int main(int argc, char *argv[])
{
    /**  */ 
    test_exception();
    /**  */ 
    test_exception_class();
}
