#include <iostream>
#include <array>
#include <map>
#include <tuple>
#include <vector>
#include <stack>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <exception>

#include <boost/timer/timer.hpp>
#include <cmath>

using namespace std;
using namespace boost; 

struct S {

};
/**  */
using namespace boost::timer;
using namespace std;
int time_test()
{
  cpu_timer timer;
    cout << "time:" <<  timer.format()<< '\n';
  for (int i = 0; i < 1000000; ++i)
    std::pow(1.234, i);
  auto ts = timer.elapsed();
  std::cout << timer.format() << '\n';
      cout << ts.user <<'\n'; //cpu 用户代码执行时间
}

/**  */ 
#include <boost/assign.hpp>
using namespace boost::assign;

int test_assign()
{
  std::vector<int> v = list_of(1)(2)(3);

  std::stack<int> s = list_of(1)(2)(3).to_adapter();

  std::vector<std::pair<std::string, int>> v2 =
    list_of<std::pair<std::string, int>>("a", 1)("b", 2)("c", 3);

  std::map<std::string, int> m =
    map_list_of("a", 1)("b", 2)("c", 3);

  std::vector<boost::tuple<std::string, int, double>> v3 =
    tuple_list_of("a", 1, 9.9)("b", 2, 8.8)("c", 3, 7.7);
}

/** singleteon */
#include <boost/serialization/singleton.hpp>
using boost::serialization::singleton;
class point : public singleton<point> {
    public:
    void print(); };
void  point::print() {cout << "this is singleton\n"; }
 
/**  */ 
#include <boost/exception/all.hpp>
typedef boost::error_info < struct tag_err_no, int> err_no;     //tag是一个标记,常是是一个空类；T（int）是真正存储的信息数据
typedef boost::error_info<struct tag_err_str, string> err_str;
struct my_exception :    virtual std::exception,virtual boost::exception{}; //自定义的异常
class my_exception_test : public std::logic_error {}; 
void test_exceptio()
{
    try  {
    point * pb = 0;
    //typeid(*pb);  // throws a bad_typeid exception
    throw my_exception() << err_no(12);
  }
  catch (my_exception& e)  {
    cout << *get_error_info<err_no>(e) << endl;
    std::cout << "exception caught: " << e.what() << '\n';
  }
}

/**  */ 
#include <boost/bimap.hpp>
void test_bimap()

{
  typedef boost::bimap<std::string, int> ibimap;
  ibimap animals;

  //animals.insert({"cat", 4});
  animals.left.insert({"cat", 8});
  animals.right.insert({0,"shark"});
  animals.insert({"spider", 8});
    //animals["a123"] = 123;
    //animals.left[123] = "a123";
  for (auto it = animals.begin(); it != animals.end(); ++it)
    std::cout << it->left << " has " << it->right << " legs\n";

   //boost::bimap<boost::bimap::set_of<int>, boost::bimap::vector_of<string> > bm;
    //bm.left.insert(make_pair(1, "111"));//bm.left[2] = "222";      bm.left[300] = "bimap";
    //bm.left.insert(make_pair(2, "11e"));

}

/**  */ 
#include <boost/circular_buffer.hpp>
void test_circular_buff()
{
    circular_buffer<int> cb(5);    //声明一个大小为5的循环缓冲区, 还是empty
    assert(cb.empty());
    cb.push_back(1);
    cb.push_front (2);//向后端添加元素1     //向前端添加元素2
    cb.push_back(5);
    cb.push_front (6);//向后端添加元素1     //向前端添加元素2
    if(cb.full()){printf("cb full!\n"); }     //是否满
    cb.insert(cb.begin(),8);    //向前端添加元素3
    if(cb.full()){printf("cb full!\n"); }     //是否满
    cb.pop_front();    //弹出最开始的3
    //assert(cb.front() == 2);     //访问
    cb.push_front (11);//向后端添加元素1     //向前端添加元素2
    cb.push_front (12);//向后端添加元素1     //向前端添加元素2
    int *p = cb.linearize();     //获取线性数组
    for(int i = 0; i<=2; i++){
        cout << p[i];}
    if(cb.full()){printf("cb full!\n"); }     //是否满
    for (auto& x: cb)    {   cout << x << ",";   }  //遍历
    printf("\n");
}

/**  */ 
#include <boost/any.hpp>
#include <boost/variant.hpp>
void test_any_var()
{
    any  a(10);  //创建 一个，并初始化
    int n=any_cast<int>(a);     //获得一个值的拷贝
    a = string("char*");     //转存 存储一个string字符串
    //a = vector<vector<int>>();     //any存储一个二维vector
    cout<< any_cast<string>(a) << endl;     //用any cast取得存储的值

    /**  */ 
    variant<int,float,string> v; //可容纳int，float和string, 必须指定 类型范围（any可以不用）
    v = 123;//
    cout << v << endl; //不用cast
    v = "Boost";
    //std::cout << boost::get<std::string>(v) << '\n';
    std::cout << v << '\n';
}


int main(int argc, char* argv[])
{
    time_test();
    printf("------------------\n");
    
    test_assign();
    printf("------------------\n");

    /** singleton */
    point::get_mutable_instance().print();
    printf("------------------\n");
    //point::get_const_instance().print();

    /**  */ 
    test_exceptio();
    printf("------------------\n");

    test_bimap();
    printf("------------------\n");
    /**  */ 
    test_circular_buff();
    printf("------------------\n");
    /**  */ 
    test_any_var();
    printf("------------------\n");

    return 0;
}
