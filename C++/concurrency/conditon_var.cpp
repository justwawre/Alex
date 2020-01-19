/*  $ g++  condition_var.cpp  -lpthread

 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

#include "../toolkit.h"
using namespace std;

void test_consumer_producer()
{
    FUNC_HEAD();
    queue<int> products;
    mutex cv_m;
    condition_variable cv_p, cv_c;
    bool done = false;

    thread producer([&]() {
        for (int i = 0; i < 5; ++i)
        {

            cout << " producing " << i << '\n';
            products.push(i);
            cv_p.notify_one();
            //this_thread ::sleep_for(90ms);
            unique_lock<mutex> lk(cv_m);
            cv_c.wait_for(lk, 100ms, [] { return false; });
        }
        done = true;
    });

    // 消费者线程
    thread consumer([&]() {
        while (!done)
        {
            unique_lock<mutex> lk(cv_m);
            cv_p.wait_for(lk, 100ms, [] { return false; });
            while (!products.empty())
            {
                cout << " consuming " << products.front() << '\n';
                products.pop();
            }
            cv_c.notify_one();
        }
    });

    producer.join();
    consumer.join();
}

mutex m;
condition_variable cv;
string str;
bool ready = false;
bool processed = false;

void worker_thread()
{
    // Wait until main() sends str
    unique_lock<mutex> lk(m);
    cv.wait(lk, [] { return ready; });

    // after the wait, we own the lock.
    cout << "Worker thread is processing str\n";
    str += " after processing";

    // Send str back to main()
    processed = true;
    cout << "Worker thread signals str processing completed\n";

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}

void test_inter_threads()
{
    FUNC_HEAD();
    thread worker(worker_thread);

    str = "Example str";
    // send str to the worker thread
    {
        lock_guard<mutex> lk(m);
        ready = true;
        cout << "main() signals str ready for processing\n";
    }
    cv.notify_one();

    // wait for the worker
    {
        unique_lock<mutex> lk(m);
        cv.wait(lk, [] { return processed; });
    }
    cout << "Back in main(), str = " << str << '\n';

    worker.join();
}

int main()
{
    test_consumer_producer();

    test_inter_threads();
    return 0;
}