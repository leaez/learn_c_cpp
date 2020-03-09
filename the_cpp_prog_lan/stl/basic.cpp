#include <iostream>
#include <cassert>
#include <cmath>
#include <array>
#include <map>
#include <tuple>
#include <vector>
#include <list>
#include <queue>
#include <mutex>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <initializer_list>


using namespace std;
using std::cout; // tell the compiler that cout means std::cout
#define MARK (cout << "--------------" <<'('<<__LINE__<<')' << '<' << __FUNCTION__ << '>' <<endl) 

#define printx(x) cout << #x " = " << int{x} << '\n'; 


/**  */ 
void f(initializer_list<int> lst)
{
  //for(int i=0; i<lst.size(); ++i)  cout << lst[i] << '\n'; // error no []
  const int* p = lst.begin();
  for(int i=0; i<lst.size(); ++i)    cout << p[i] << '\n'; // OK
  
  for (auto x : lst) cout << x << '\n';
}

void test_b()
{
  f({1,2,3});
}

/** container */ 

class Nocase { // case-insensitive string compare
public:
  bool operator()(const string&, const string&) const;
};
bool Nocase::operator()(const string& x, const string& y) const
  // return true if x is lexicographically less than y, not taking case into account
{
  auto p = x.begin(); auto q = y.begin();
  while (p!=x.end() && q!=y.end() && toupper(*p)==toupper(*q)) {
    ++p; ++q;
  }
  if (p == x.end()) return q != y.end();
  if (q == y.end()) return false;
  return toupper(*p) < toupper(*q);
}


void use_list(list<pair<string,double>>& lst)
{
  auto p = lst.begin();
  while (p!=lst.end() && p->first!="Denmark") // find an insertion point
    p++/* do nothing */ ;
  p=lst.emplace(p,"England",7.5); // nice and terse
  p=lst.insert(p,make_pair("France",9.8)); // helper function
  p=lst.insert(p,pair<string,double>{"Greece",3.14}); // verbose
}

void test_container()
{  
  vector<string> fruit {"apple ","pear", "Apple", "Pear","lemon" };
  sort(fruit.begin(),fruit.end(),Nocase());
  for(auto x: fruit) cout << x <<endl;

  vector<int> vi {1,3,5,7,9}; // vector initialized by five ints
  vector<string> vs(7); // vector initialized by seven empty strings

  vector<int> vi2;
  vi2 = {2,4,6,8}; // assign sequence of four ints to vi2
  vi2.assign(&vi[1],&vi[4]); // assign the sequence 3,5,7 to vi2
  vector<string> vs2;
  vs2 = {"The Eagle", "The Bird and Baby"}; // assign two str ings to vs2
  //vs2.assign("The Bear", "The Bull and Vet"); //  error  require iterator not char*

  list<pair<string,double>> lp{make_pair("France",9.8)};
  use_list(lp);

  /** map */
  map<string,string> dictionary;
  dictionary["sea"]="large body of water"; // inser t or assign to element
  cout << "dictionary " << dictionary["sea"]; // read value
  auto q = dictionary.find("seal"); // lookup; don’t insert
  if (q==dictionary.end()) {
    cout << "entry not found\n";
    dictionary.insert(make_pair("seal","eats fish"));
  } else
    cout<< "found:" << q->second << endl;
  
  multimap<string,int> mm {{"apple",2}, { "pear",2}, {"apple",7}, {"orange",2}, {"apple",9}};
  const string k {"apple"};
  auto pp = mm.equal_range(k);
  if (pp.first==pp.second)
    cout << "no element with value " << k << "\n";
  else {
    cout << "elements with value " << k << "\n";
    for (auto p=pp.first; p!=pp.second; ++p) cout << p->second << ' ';
  }

  /** priority_queue */ 
  struct Message {
    int priority;
    bool operator<(const Message& x) const { return priority < x.priority; }
    // ...
  };
  priority_queue<Message> pq;
  pq.push(Message{3});
  pq.push(Message{2});
  pq.push(Message{4});
  mutex mt;
  while (!pq.empty()) {
    Message mess;
    { lock_guard<mutex> lck(mt); // hold lock while extracting message
      if (pq.empty()) return; // somebody else got the message
      mess = pq.top();
      auto ms = pq.top(); pq.pop();
      cout << " > " << ms.priority;
    }
  // ser ve highest priority request
  }cout << endl;
}

map<string,pair<int,float>> locations {
  {"Copenhagen",{1,2}}, {"New York",{3,2}}
};





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
  case 1: test_b();
  case 2: test_container();
  default:;
  }

}
