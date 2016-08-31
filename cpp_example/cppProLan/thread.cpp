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
};


queue<Message> mqueue; // the queue of messages
condition_variable mcond; // the var iable communicating events
mutex mmutex; // the locking mechanism

void consumer()
{
    while(true) {
        unique_lock<mutex> lck{mmutex}; // acquire mmutex
        cout << "cons lock -- one!\n";
        mcond.wait(lck) /* do nothing */; // release lck and wait;
        // re-acquire lck upon wakeup
        auto m = mqueue.front(); // get the message
        mqueue.pop();
        lck.unlock(); // release lck
        cout << "cons --- one!\n";
        // ... process m ...
    }
}

void producer()
{
    while(true) {
        Message m;
        // ... fill the message ...
        {   
            unique_lock<mutex> lck {mmutex}; // protect operations
            mqueue.push(m);
            char a;
            cin >> a;
            //lck.unlock();
            }
        mcond.notify_one(); // notify
       // this_thread::sleep_for(chrono::milliseconds{100});
        cout << "prod***  one!\n";
    } // release lock (at end of scope)
}


mutex cout_mutex; // initialized to ‘‘not owned by any thread’’
void hello(int n)
{
    for (int i=0; i!=n; ++i) {
        cout_mutex.lock();
        this_thread::sleep_for(chrono::seconds(5));
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

int main()
{
    //thread t1{consumer};
    //thread t2{producer};
    //t1.join();
    //t2.join();

    thread t1 {hello,5};
    thread t2 {world,6};

    t1.join();
    t2.join();




}
