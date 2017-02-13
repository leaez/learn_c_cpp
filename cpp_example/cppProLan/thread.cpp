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


class Message { // object to be communicated
    int a;// ...
    public:
    int get_v(){return a;}
};
bool ready = false;

queue<Message> mqueue; // the queue of messages
condition_variable mcond; // the var iable communicating events
mutex mmutex; // the locking mechanism

void consumer()
{
    while(true) {
        unique_lock<mutex> lck{mmutex}; // acquire mmutex
        while(!ready) mcond.wait(lck) /* do nothing */; // release lck and wait;
        //lck.lock();
        cout << "cons lock -- one!\n";
        // re-acquire lck upon wakeup
        //auto m = mqueue.front(); // get the message
        //mqueue.pop();
        //int a = m.get_v();
        //mmutex.unlock();
        cout << "cons --- one!"  << "\n";
        ready = false;
        lck.unlock(); // release lck
        // ... process m ...
    }
}

void producer()
{
    while(true) {
        //Message m;
        // ... fill the message ...
           
            //unique_lock<mutex> lck {mmutex}; // protect operations
            //mqueue.push(m);
            char a = '2';
            // cin >> a;
            this_thread::sleep_for(chrono::seconds(1));
            ready = true;
        mcond.notify_one(); // notify
            //lck.unlock();
            
            //mmutex.unlock();
            //mmutex.unlock();
            
       // this_thread::sleep_for(chrono::milliseconds{100});
        cout << "prod***  one!" << a << "\n";
    } // release lock (at end of scope)
}

#if 0
mutex cout_mutex; // initialized to ‘‘not owned by any thread’’
void hello(int n)
{
    for (int i=0; i!=n; ++i) {
        this_thread::sleep_for(chrono::seconds(2));
        cout_mutex.lock();
        cout << "Hello, \n";
        cout_mutex.unlock();
    }
}

void world(int n)
{
    for (int i=0; i!=n; ++i) {
        this_thread::sleep_for(chrono::seconds(1));
        cout_mutex.lock();
        cout << "World!\n";
        cout_mutex.unlock();
    }
}
#endif

int main()
{
    thread t1{consumer};
    thread t2{producer};
    t1.join();
    t2.join();

    //thread t1 {hello,5};
    //thread t2 {world,6};
    //t1.join();
    //t2.join();




}
