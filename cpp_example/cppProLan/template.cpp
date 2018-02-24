#include <iostream>


using namespace std;


template< class T > void g(T);    // #1: overload for all types
template<>          void g(int*); // #2: specialization of #1 for pointers to int
template< class T > void g(T*);   // #3: overload for all pointer types

template<void (*pf)(int)> struct AF {};
template<int (pa)[5]> struct S_arr {};
template<const char*> struct S2 {};


void test_template_base(){
    /** template  */ 
    const int bt[5] = {1, 3 ,3, 4, 4};
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

template<class T> class X4{}; // declaration, not definition

template<typename T>void f_cout(T s){
    std::cout << s << '\n';
}

/** multiple parameters */ 
template<class... Types> void f2(Types... values){
   /* for(auto v: values){
        cout << v ; 
    }   cout << "\n"; */
}
template<typename T, typename... Tail> void ff(T head, Tail... tail){ //...indicate the rest
    g(head); /*  do something to head */ 
    f(tail...); }// try again with tail

template<int I, int J, class T> struct X5 { 
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
    X4<char> ch; //
    
    f_cout<string>("I am a string"); /** call template function */ 
    f_cout<>("auto deduce as a string");
    f_cout(12); 
    void (*ptr)(std::string) = f_cout;
    ptr("func ptr called");
   
    X5<2,3,int> x5; /** digital as para */ 
    x5.f(852);
 
}




int main(int argc, char* argv[])
{
    test_template_base();

    test_template();

    
    return 0;
}

