#include <iostream>
#include <array>
#include <map>
#include <tuple>
#include <vector>
#include <queue>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <thread>
#include <condition_variable> 
#include <mutex>
#include <chrono>

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

/**  */ 
bool ready = false;
queue<int> mqueue; // the queue of messages
condition_variable mcond; // the variable communicating events
mutex mmutex; // the locking mechanism
//condition_variable works only with std::unique_lock<std::mutex>
void consumer(){ /** 1. lock; 2, wait 3,wakeup(timespire/notified) */ 
    while(true) {  
        unique_lock<mutex> lck{mmutex}; // acquire mmutex(lock())
        while(!ready) mcond.wait(lck) /* do nothing */; // release lck and wait;
        //lck.lock();
        int a = mqueue.front(); // get the message
        mqueue.pop();
        //mmutex.unlock();
        cout << "consumer processed data : " << a << ", queue size: " << mqueue.size() << endl;
        ready = false;
        lck.unlock(); // release lck
    }
}

void producer(){
    while(true) {
        cout <<  ", queue size: " << mqueue.size() << endl;
           g_num++;{
            std::lock_guard<std::mutex>  lck {mmutex};
            //unique_lock<mutex> lck {mmutex}; // protect operations
            mqueue.push(g_num);
            this_thread::sleep_for(chrono::seconds(1));
            ready = true;
           }
            mcond.notify_one(); // notify
            //lck.unlock();
            //mmutex.unlock();
        cout << "producer prepare data: " << g_num << ";size:"<<mqueue.size()<< endl;
    } // release lock (at end of scope)
}
/**  */ 
void test_condition(){
    MARK;
    thread t1{consumer};
    thread t2{producer};
    t1.join(); //waits for a thread to finish its execution 
    t2.join();

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
        test_condition();
        break;
    default:;
    }


}
