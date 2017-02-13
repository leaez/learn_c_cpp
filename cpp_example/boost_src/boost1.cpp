
#include <iostream>
#include <functional>
//#include <boost/bind.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "boost/multi_array.hpp"
#include <boost/program_options.hpp>
#include <thread>
#include <boost/timer.hpp>


namespace po = boost::program_options;

using namespace std;
using namespace boost::numeric::ublas;

double Function0(){
    cout << "function0 called !\n";
    return 1;
}
 
double Function1(const int a){
    cout << "function1 called !\n";
    return a+1;
}

class MyClass
{
private:
  double Update1() {
    std::cout << "Update1" << std::endl;
  }
  double Update2() {
    std::cout << "Update2" << std::endl;
  }
 
public:
  std::function< double() > Update;
  void SetUpdateMethod(int method) {
    if(method == 1) {
      this->Update = std::bind(&MyClass::Update1,this);
    }
    if(method == 2) {
      this->Update = std::bind(&MyClass::Update2,this);
    }
  }
  void thred_fun(){cout << "threadd run \n"; }

};
 
int main (int argc, char* argv[]) 
{
    /** Function */ 
    std::function<double ()> FunctionPointer0 = &Function0;
    std::function<double (const int)> FunctionPointer1 = &Function1;
    FunctionPointer0();
    FunctionPointer1(1);
    /** bind */ 
    MyClass a;
    a.SetUpdateMethod(1);
    a.Update();
    a.SetUpdateMethod(2);
    a.Update();
    /** matrix  */ 
    matrix<double> m (3, 3);
    for (unsigned i = 0; i < m.size1 (); ++ i)  {
        for (unsigned j = 0; j < m.size2 (); ++ j)    {
            m (i, j) = 3 * i + j;
        }
    }
    std::cout << m << std::endl; //direct ro print

    /** malti array  */ 
    // Create a 3D array that is 3 x 4 x 2
    typedef boost::multi_array<double, 3> array_type;
    typedef array_type::index index;
    array_type A(boost::extents[3][4][2]);
    // Assign values to the elements
    int values = 0;
    for(index i = 0; i != 3; ++i) 
        for(index j = 0; j != 4; ++j)
            for(index k = 0; k != 2; ++k)
                A[i][j][k] = values++;

    /**options_  */
#if 1
    int compression;
    std::vector<std::string> FileList;
    po::options_description desc("Allowed options");
    desc.add_options()
      ("help", "produce help message")
      ("compression,c", po::value<int>(&compression)->default_value(5), "set compression level") //automatically assign to a variable
      ("FileList", po::value<std::vector<std::string> >(&FileList)->multitoken(), "List of files.") //multiple values
      ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm); //assign the variables (if they were specified)
    if(vm.count("help"))   {
        std::cout << desc << std::endl;;
        return 1;
    }else{}
    if(vm.count("compression"))     {
        std::cout << "Compression level was set to " << vm["compression"].as<int>() << std::endl;
    } else {}
#endif
    /** thread */
    std::thread MyThread(&Function0);
    
    std::thread MyThread1(std::bind(&MyClass::thred_fun, a));
    MyThread.join();
    MyThread1.join();

    /** signal */ 




 
  return 0;
}


