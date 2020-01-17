#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <tuple>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <random>
#include <regex>
#include <unordered_set>
#include <cstring>

using namespace std;
#define MARK (cout << "--------------" <<'('<<__LINE__<<')' << '<' << __FUNCTION__ << '>' <<endl) 
template <typename T> 
void printv(T &vi){
    for (auto& x :  vi) // implicit use of v.begin() and v.end()
        cout << x << "," ; cout << endl;
}

/** vector */ 
void test_vector()
{
    /**  */ 
    MARK;
    int v[] = {0,1,2,3,4,5,6,7,8,9};
    for (auto x : v) // for each x in v
        cout << x << ' ';       cout << endl;

    std::vector<int> vl = {1, 2, 3, 4, 5, 6, 7};
    for(const int &i : vl) // access by const reference
        std::cout << i << ' ';
    for(int n: {0, 1, 2, 3, 4, 5}){
        cout << n ; }        cout <<endl;

    vector<int> z{1000,22};
    vector<int> x{222,333};
    vector<int> y{444,555};
    z = x; // we get a copy
    cout <<"after copy:" << x[0] << x[1] << endl;
    y = std::move(x); // we get a move
    cout <<"after move:" << y[0] << y[1] << endl;
    //cout  << x[1] ; //error! after move  is delete!!

    vector<int> vi1 {1,3,5,7,9,7,5,3}; // vector initialized by five ints
    vi1[15] = 2; // no bounds checking!!!
    vi1.at(7) = 3; // does bounds checking ; throw std::out_of_range
    try{ vi1.at(15) = 3; // does bounds checking ; throw std::out_of_range
    }catch(exception &e){ 
        cout <<"excption :" << e.what() <<endl; }
    vi1.resize(5); //1,3,5,7,9
    vector<string> vs(7); // vector initialized by seven empty strings
    vector<int> vi2;
    vi2 = {2,4,6,8,6,4,2}; // assign sequence of four ints to vi2
    auto cnt = find_if(vi1.begin(),vi1.end(),[](int& x) { return (x==7);}) ;
    if(cnt != vi1.end())
        cout <<"find:" << *cnt << endl; /**return iterator */ 
    replace(vi1.begin(),vi1.end(),3,8); //1,3,5,7,9 -> 1, 8, 5, 7, 9, 
    //generate(begin(vi2),end(vi2),Randint{});
    printv(vi1);
    vi2.assign(&vi1[1],&vi1[4]); // assign the sequence 8,5,7 to vi2(resize to 3)
    vi2.push_back(100);
    printv(vi2);
    vi1.assign(3,11); printv(vi1); // vi1: 11,11,11 
    vi2.pop_back(); cout << "vi2:"; printv(vi2);


    vector<string> vs2;
    vs2 = {"The Eagle", "The Bird and Baby"}; // assign two str ings to vs2
    //vs2.assign("The Bear","The Bull and Vet");// run-time error
    cout <<"vs size:" << vs2.size() << "cap:" << vs2.capacity() << "\n"; //2; 2

}


/**  */ 
void test_array(){
    /** array  */ 
    MARK;
    std::array<int, 3> a2 = {1, 5 }; printv(a2); // 1,5,0 
    std::sort(a2.begin(), a2.end());
    std::array<int, 3> a1 {1, 2, 3} ; //  in C++11
    a1[0] = 111; a1.at(2) = 333;
    cout << "a1:" << a1.back() << a1.front() <<", size:" <<a1.size() <<endl; 
    array<string, 4> as = {"Churchill", "Clare"};//Churchill,Clare,,, 2 empty
    printv(as);
    cout <<"size:" << as.size() << "at:" << as.at(1) <<endl;
    as.fill("fill");
    printv(as);

    
}


void test_deque ()
{
    MARK;
    deque<int> first;                                // empty deque of ints
    deque<int> second (4,100);                       // four ints with value 100
    second[0] = 11; second.at(1) = 22;
    second.back() = 44; second.front() = 0;
    first.assign(5,123); // 5's 123 
    first.push_back(456);
    first.pop_front();
    printv(first);
    printv(second);
    deque<int>::iterator it = first.begin();  ++it;
    first.insert(it,789);
    first.emplace(first.end(),999);
    printv(first);

}

void test_list(){
    MARK;
    list<int> l = { 1,100,2,3};
    list<int> first;                                // empty list of ints
    list<int> second (4,100);                       // four ints with value 100
    second.front() = 0;second.back() = 444;
    first.assign (3,100);
    first.pop_front(); first.push_back(123);
    printv(first);
    list< std::pair<int,char> > mylist;
    mylist.emplace (mylist.begin(), 100, 'x' );
    first.splice(first.end(),second); /**moves elements from another list; second empty */ 
    printv(first); printv(second);
    second.assign({1,2,3,4});
    list<int>::iterator it = second.begin(); it++;
    first.splice(first.end(),second,it,second.end()); //2,3,4 move to first ; second only:1,
    printv(first); printv(second);
    first.unique();printv(first);//	removes consecutive duplicate elements (only adjacent element same)
    first.sort(); printv(first);
    
    first.remove(0);
    first.remove_if([](int n){ return n > 100; });
    printv(first);
    first.merge(second); printv(first);

}

void test_set(){
    /** set */ 
    MARK;
    set<int> first = {1, 2, 3, 4};
    set<int> second;
    second = first;
    auto search = first.find(2);
    if(search != first.end()) {
        std::cout << "set Found " << (*search) << endl;  }
    second.emplace(111);
    auto it = second.begin();
    second.erase(it);
    //second.count(3) /** only c++14 */ 
    printv(first);printv(second);
}

void test_multiset(){
    MARK;
    multiset<int> first {3, 1, 4, 6, 5, 9};
    multiset<int> second = first;
    first.emplace(5);
    printv(first); /** sort out: 1,3,4,5,5,6,9 */ 
    auto search = first.find(5);
    if(search != first.end()) {
        std::cout << "Found "  << first.count(5) <<": "<< (*search) << endl;
    } else { std::cout << "Not found\n";}

}

void test_map()
{
    /** map emplace */ 
    MARK;
    std::map<std::string, std::string> m;
    m.emplace(std::make_pair(std::string("a"), std::string("a")));
    m.emplace(std::make_pair("b", "abcd"));
    m.emplace("d", "ddd");
    // uses pair's piecewise constructor
    m.emplace(std::piecewise_construct,
              std::forward_as_tuple("c"),
              std::forward_as_tuple(10, 'c'));
    for (const auto &p : m) {cout << p.first << " => " << p.second << endl;}
    m.at("a") = "aaa";
    m["b"] = "bbb";
    for(auto it = m.begin(); it != m.end(); ++it){
        if(0==strcmp(it->first.c_str(),"a")) 
            it = m.erase(it);}
    for (const auto &p : m) {cout << p.first << " => " << p.second << endl;}
    auto search = m.find("b"); //find key
    if(search != m.end()) {
        std::cout << "map Found " << search->second << endl;  }

}
void test_multimap(){
    MARK;
    multimap<int, int> m = {{1,1},{2,2},{3,3},{4,4},{5,5},{4,4},{3,3},{2,2},{1,1}};
    for(auto& p: m) std::cout << p.first << "=>" << p.second <<"; " ; cout << endl;
    cout <<"count for key 3 maps:" << m.count(3) <<endl;
    m.emplace(std::make_pair(6,10 ));
    m.emplace(7,17);
    for(auto& p: m) std::cout << p.first << "=>" << p.second <<"; " ; cout << endl;
    auto search = m.find(5); //find key
    if(search != m.end()) {
        std::cout << "set Found " << search->second << endl; }
}

/**
 * unordered_set (C++11)	collection of unique keys, hashed by keys
 * unordered_map(C++11)	collection of key-value pairs, hashed by keys, keys are unique 
 * */ 

void test_stack(){
    MARK;
    stack<int> s;
    s.push(5);
    s.emplace(123); // in-place at the top 
    cout << "s size:" << s.size() <<"; top:" << s.top()<<endl ;
    s.pop();

}
void test_queue(){ //fifo first in first out
    MARK;
    deque<int> deq {3, 1, 4, 1, 5}; //3 is first 
    queue<int> q(deq);
    cout <<"f:"<< q.front() <<", b:" << q.back() <<", s:" << q.size() <<endl;
    q.push(123); // at end
    cout <<"f:"<< q.front() <<", b:" << q.back() <<", s:" << q.size() <<endl;
    q.pop(); //remove first , return void 
    cout <<"f:"<< q.front() <<", b:" << q.back() <<", s:" << q.size() <<endl;

}

void test_iterator(){
    MARK;
    /** reverse_iterator */ 
    std::string s = "Hello, world";
    std::reverse_iterator<std::string::iterator> r = s.rbegin(); //from end to begin
    r[7] = 'O'; // replaces 'o' with 'O' 
    r += 7; // iterator now points at 'O'
    std::string rev(r, s.rend());
    std::cout << rev << '\n';
    /** back front inserter */ 
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    generate_n(back_insert_iterator<std::vector<int>>(v), // can be simplified
                    10, [](){ return std::rand() % 10; });        // with std::back_inserter
    printv(v);
    fill_n(std::back_inserter(v), 3, -1); //fill back 3's -1 //more simple than back_insert_iterator
    printv(v);
    deque<int> d;
    copy(v.begin(), v.end(),front_insert_iterator<deque<int>>(d)); // or std::front_inserter(d)
    printv(d);
    fill_n(front_inserter(d), 3, -1);
    printv(d);
    vector<int> v1{8, 9, 10};
    vector<int> l {1, 2, 3, 4, 5};
    copy(v1.begin(), v1.end(), insert_iterator<vector<int>>(l, next(l.begin())));
    printv(l);
    copy(v1.begin(), v1.end(), inserter(l, next(l.begin())));//more simple than insert_iterator
    printv(l);
    /** advance, distance next prev */
    auto it = l.begin();
    advance(it, 2);    //move iter by given distance
    printv(l);
    cout <<"distance :" << distance(v.begin(), v.end())  <<endl; //return int 
    it = l.begin(); 
    auto nx = std::next(it, 2);
    it = l.end(); auto fr = prev(it, 2);
    cout << "next: " << *nx << ", prev: " << *fr <<endl;
    //copy(std::rbegin(v), std::rend(v), std::ostream_iterator<int>(std::cout, " ")); //rbegin rend  c++14

}

/********************* 
 *
 * */ 
int main()
{
/** Sequence containers: */
    test_vector();
    /**  */ 
    test_array();
    /**  */ 
    test_deque();
    /**  */ 
    test_list();


    /** set */ 
    test_set();
    test_multiset();
    /**  */ 
    test_map();
    test_multimap();

    /**  */ 
    test_stack();
    test_queue();
    /**  */ 
    test_iterator();


}
