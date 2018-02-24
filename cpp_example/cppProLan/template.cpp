#include <iostream>
#include <assert.h> 

using namespace std;


template< typename T > void g(T);    // #1: overload for all types
template<>          void g(int*); // #2: specialization of #1 for pointers to int
template< typename T > void g(T*);   // #3: overload for all pointer types


template<void (*pf)(int)> struct AF {}; // function
template<int (pa)[5]> struct S_arr {}; // array

template<const char*> struct S2 {};



void test_template_base(){
    /** template  */ 
    constexpr int bt[5] = {1, 3 ,3, 4, 4};
    //S_arr<bt> s_arr; //error : no conversion
 
    //S2<"fail"> s2; // error: string literal cannot be used
    //char okay[] = "okay"; // static object with linkage
    //S2< &okay[0] > s2; // error: array element has no linkage
    //S2<okay> s2; // error

    //f(new int(1)); // calls #3, even though specialization of #1 would be a perfect match



}

/** template */ 
int arr[2]= {1, 2};
const int b[3] = {1,2,3}; 
template<int (&pa)[3]> struct W {};
template<const int* pci> struct X2 {};
template<int (*pf)(int)> struct X3 {X3(){pf(99);}};  //like call back


template<typename T>void f_cout(T s){
    std::cout << s << '\n';
}

/** multiple parameters */ 
template<typename... Types> void f2(Types... values){
   /* for(auto v: values){
        cout << v ; 
    }   cout << "\n"; */
}
template<typename T, typename... Tail> void ff(T head, Tail... tail){ //...indicate the rest
    g(head); /*  do something to head */ 
    f(tail...); }// try again with tail

template<int I, int J, typename T> struct X5 { 
    T i = 55;
    void f(T i){
    cout << I << J  << i << "\n";}};

int print_a(int a){
    cout <<"print_a called :" << a <<"\n";
    return a;}

void test_template(){
    cout << "\n----- test_template " <<endl;
    //W<b> w; // eror: no conversion
    //int * pai = const_cast<int * >(arr);
    /** passing real parameter */ 
    X2<arr> xi;  // ok: array to pointer conversion and cv-qualification conversion
    X3<&print_a> x3; //call back
    
    f_cout<string>("I am a string"); /** call template function */ 
    f_cout<>("auto deduce as a string");
    f_cout(12); 
    void (*ptr)(std::string) = f_cout; // instantiates f_cout<string>(string)
    ptr("func ptr called");
   
    X5<2,3,int> x5; /** digital as para */ 
    x5.f(852);
 
}


/** for function */ 
template <typename T> // this is the template parameter declaration
const T& get_max(const T& x, const T& y){
    return (x > y) ? x : y;}

void test_template_func(){
    cout << "\n----- test_function_template " <<endl;
    int i = get_max<int>(3, 7); // calls max(int, int)
    double d = get_max(6.34, 18.523); // calls max(double, double)
}

/** template for class */ 
template <typename T, int size> /** size is the non-type parameter */ 
class Array{
private:
    int m_length;    T *m_data;
    T m_array[size];
public:
    Array(int length = 0) {
        if(length >0) m_data = new T[length];
        else m_data = nullptr;
        m_length = length;
    }
    ~Array()   {  delete[] m_data; }
    T& operator[](int index) { assert(index >= 0 && index < m_length);
        return m_data[index];
    }
    T& operator()(int index)  {assert(index >= 0 && index < size);
        return m_array[index];
    }
};

void test_template_class(){
    cout << "\n----- test_function_class" <<endl;
    Array<int,10> intArray(12); intArray[10] = 11;
	Array<double,10> doubleArray(12); doubleArray[10] = 12.12; //instantiate template Array<double>
    cout << "intArray: "<< intArray[10] << ";  doubleArray:" << doubleArray[10] <<endl; 
    doubleArray(8) = 12.10;
    cout << "access m_array: "<< doubleArray(8) <<endl; 
    
}

int main(int argc, char* argv[])
{
    test_template_base();

    test_template_func();
    /**  */ 
    test_template();

    test_template_class(); 
    return 0;
}

