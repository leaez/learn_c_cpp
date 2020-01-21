#include <iostream>
#include <array>
#include <map>
#include <tuple>
#include <numeric>
#include <vector>
#include <queue>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <thread>
#include <condition_variable> 
#include <mutex>
#include <chrono>
#include <future>
#include <cmath>

using namespace std;

#define MARK (cout << "--------------" <<'('<<__LINE__<<')' << '<' << __FUNCTION__ << '>' <<endl) 

/**  */ 
int g_num = 0;
mutex cout_mutex; // initialized to ‘‘not owned by any thread’’
timed_mutex t_mutex;
void hello(int n){
    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "thread id: " << this_id << endl;
    for (int i=0; i!=n; ++i) {
        this_thread::sleep_for(chrono::seconds(1));
        cout_mutex.lock();
        g_num++;
        cout << "Hello, " << g_num << endl;
        cout_mutex.unlock();
    }
}

void world(int n){
    for (int i=0; i!=n; ++i) {
        this_thread::sleep_for(chrono::seconds(1));
        cout_mutex.lock();
        g_num++;
        cout << "World," << g_num <<endl ;
        cout_mutex.unlock();
    }
}
void try_lk(){// Returns immediately. got lock :returns true, otherwise returns false
    while(1){ t_mutex.lock(); this_thread::sleep_for(chrono::seconds(1));
        t_mutex.unlock();
        if(cout_mutex.try_lock()){
            g_num++;
            cout << "Hello World ! : " << g_num << endl;
            cout_mutex.unlock(); return;
        }
    }
}
void t_mutexf(){
    while(1){ this_thread::sleep_for(chrono::seconds(1));
        if(t_mutex.try_lock_for(chrono::seconds(1))){//duration elapsed or get lock will triger return true/false
            g_num++;
            cout << "Timed mutex : " << g_num << endl;
            t_mutex.unlock(); return;
        }
    }
   
}

/**  */ 

void test_mutex(){
    MARK;
    auto start = std::chrono::high_resolution_clock::now();
    thread t1 {hello,5};
    thread t2 {world,6};
    thread t3 {try_lk};
    thread t4 {t_mutexf};
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "test elapsed: " << elapsed.count() << " ms\n";
}

/** lock_guard */ 
mutex do_mutex;
void func_guard(int n){
    this_thread::sleep_for(chrono::seconds(n));
    std::lock_guard<std::mutex> guard(do_mutex); /**  RAII-style owning a mutex , locking the given mutex  */
    cout << "thread do: " << n <<endl; 
    /** todo ... */ 
} //here release do_mutex,  unlocking the given mutex 
void test_lock_guard(){
    MARK;
    thread t2(func_guard,2);
    thread t1(func_guard,1);
    t1.join();
    t2.join();

}



/** condition_variable  */ 
bool ready = false;
queue<int> mqueue; // the queue of messages
condition_variable mcond; // the variable communicating events
mutex mmutex; // the locking mechanism
//using namespace std::chrono_literals; //only C++14
// ! condition_variable works only with std::unique_lock<std::mutex>
void consumer(int n){ /** 1. lock; 2, wait 3,wakeup(timespire/notified) */ 
    while(true) {  
        this_thread::sleep_for(chrono::seconds(1));
        unique_lock<mutex> lck{mmutex}; // acquire (call mmutex.lock()) 
        //cout << "consumer processed data : "<< endl;
        //while(!ready) {
        //mcond.wait(lck,[](){return ready;});// same as above
        //mcond.wait(lck, [](){return (mqueue.size()>0);});//same with: while()m.wait(lck);
        mcond.wait_for(lck,chrono::microseconds(100), [](){return (mqueue.size()>0);});//same with: while()m.wait(lck);
        int a; 
        a = mqueue.front(); // get the message
        if(!mqueue.empty()) mqueue.pop();
        if(!mqueue.empty()) mqueue.pop();
        cout <<n<< ". consumer processed data : " << a << ", queue size: " << mqueue.size() << endl;
        ready = false;    
    }//every loop end  unlock mmutex (unique_lock beyond scope)
}

void producer(int n){
    while(true) {
        this_thread::sleep_for(chrono::seconds(1));
        g_num++;
        { lock_guard<mutex>  lck {mmutex}; //call mmutex.lock
        //unique_lock<mutex> lck{mmutex}; // acquire (call mmutex.lock())
        mqueue.push(g_num);
        mqueue.push(g_num);
        mqueue.push(g_num);
        ready = true;
        }
        mcond.notify_all(); // notify
        cout <<n<<". producer prepare data: " << g_num << ";size:"<<mqueue.size()<< endl;
    }
}
/**  */ 
void test_condition_variable(){
    MARK;
    thread t1{consumer,1};
    thread t2{consumer,2};
    thread t3{producer,3};
    t1.join(); //waits for a thread to finish its execution 
    t2.join();
    t3.join();

}

/** 1. a thread: pass promise & promise.set_value()
 *  2. another thead: from promise.get_future(); future.get() the result;
 * */ 
#define sleep(n) this_thread::sleep_for(chrono::seconds(n))

void acc(std::vector<int>::iterator first,
                std::vector<int>::iterator last, //input
                std::promise<int> accumulate_promise){ // output to promise
    int sum = std::accumulate(first, last, 0);
    accumulate_promise.set_value(sum);  // Notify future
}
bool is_prime (int x) {
  std::cout << "is_prime doing...\n";
  for (int i=2; i<x; ++i) if (x%i==0) return false;
  return true;
}
int f(int x, int y) { sleep(2);return std::pow(x,y); }
 
void test_promise_future(){
    MARK;
  // using promise<int> to transmit a result between threads.
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    std::promise<int> accumulate_promise;
    std::future<int> accumulate_future = accumulate_promise.get_future(); // future from a promise
    std::thread work_thread(acc, numbers.begin(), numbers.end(),
                            move(accumulate_promise)); //can not copy
    accumulate_future.wait();  // wait for result
    std::cout << "accumulate result=" << accumulate_future.get() << '\n';
    work_thread.join();  // wait for thread completion
  cout << "-----------------\n";
 /** future */ 
    // 1. future from a packaged_task
    std::packaged_task<int()> task([]{ sleep(2);cout << "   I'm packaged_task 7 \n"; return 7; }); // wrap the function
    std::future<int> f1 = task.get_future();  // get a future
    std::thread t(std::move(task)); // launch on a thread
    // 2. future from an async() //a new thread is launched to execute 
    std::future<int> f2 = std::async(std::launch::async, []{sleep(1);
            cout << "   I'm async 8\n"; return 8; });
    // 3. future from a promise
    std::promise<int> p;
    std::future<int> f3 = p.get_future();
    std::thread( [&p]{sleep(3);cout <<" I'm thread promise  9 \n"; 
            p.set_value(9); }).detach();//make thread independently. resources will be freed once thread exits. 
 
    std::cout << "Waiting..." << std::flush;
    //f1.wait(); //Blocks until the result becomes available. 
    //f2.wait(); //got also wait , some time can be ignored
    //f3.wait();
    f1.wait(); f2.wait(); f3.wait(); //here 3 thread got done
    std::cout << "after 3 thread done,  Got Results are: " //f.get()//waits until the future has a valid * retrieves it
              << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
    t.join();

  cout << "-----------------\n";
  /** async */  //runs a function asynchronously
    std::future<bool> fut = std::async (is_prime,313222313);
    bool ret = fut.get();  //wait result
    cout <<"prime result:" << ret <<endl;

  cout << "-----------------\n";
  /** packaged_task */ //packages a function to store its return value
    std::packaged_task<int()> task1(std::bind(f, 2, 11));
    std::future<int> ftask1 = task1.get_future();
    task1();//not new thread, just run function. 
    cout <<"task1() is not in a new thread!" <<endl;
    std::packaged_task<int()> task2(std::bind(f, 2, 10));
    std::future<int> ftask2 = task2.get_future();
    task2();//not new thread , Calls the stored task 
    std::packaged_task<int(int,int)> task3(f);
    std::future<int> ftask3 = task3.get_future();
    std::thread task_td(std::move(task3), 2, 9); //this is a way new thread

    std::cout << "1. task_bind:\t" << ftask1.get() << '\n';
    std::cout << "2. task_bind:\t" << ftask2.get() << '\n';
    task_td.join();
    std::cout << "3. task_thread:\t" << ftask3.get() << '\n';

}



int main(int argc, char* argv[])
{
    /**  */ 
    if(argc != 2) { 
        cout << "1 : lock; "<< endl
            << "2 : muxtex; "<< endl;
        exit(0);}
    int i = atoi(argv[1]);
    switch(i){
    case 1:
        test_mutex();
        break;
    case 2:
        test_lock_guard();
        break;
    case 3:
        test_condition_variable();
        break;
    case 4:
        test_promise_future();
        break;
    default:;
    }


}
