/*  $ g++ simple.cpp -lpthread
 */

#include <iostream>
// #include <functional>
#include <thread>
#include <mutex>
#include <cassert>
#include "../toolkit.h"
using namespace std;

void hello()
{
    cout << "Welocme to Concurrent  world!" << endl;
}

void test_hello()
{
    thread t{hello};
    FUNC_HEAD();

    t.join();

    thread t2{hello};
    cout << "orginnal thrad id\t" << t2.get_id() << endl;
    thread t3{move(t2)};
    cout << "new thrad id via move\t" << t3.get_id() << endl;
    t3.join();
}

struct FO //function objec
{

    void operator()(int i)
    {
        cout << "the param is\t" << i << endl;
    }
};

thread create_thread_func()
{
    FO f;
    f(555);
    thread t{f, 666};
    return t;
}

void test_thread_function_object()
{
    FUNC_HEAD();
    thread t;
    t = create_thread_func();

    if (t.joinable())
    {
        t.join();
    }
    thread t2{FO(), 777};
    t2.detach();
    assert(!t2.joinable());
}

void func_using_ref(int n1, int &n2, const int &n3)
{
    std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    ++n1; // increments the copy of n1 stored in the function object
    ++n2; // increments the main()'s n2
    // ++n3; // compile error
}

void test_thread_ref()
{
    FUNC_HEAD();
    int n1 = 1, n2 = 2, n3 = 3;
    std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    thread t{func_using_ref, n1, ref(n2), cref(n3)};
    t.join();
    std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
}

mutex mtx_balance;
long long int g_balance = 100;
long long int g_count = 0;

void save_withdraw(int money)
{
    unique_lock<mutex> lock(mtx_balance);
    lock.unlock();
    for (long int i = 0; i < 1000000; i++)
    {
        lock.lock();
        g_count++;
        g_balance += money;
        g_balance -= money;
        lock.unlock();
    }
}

void save_withdraw_wo_lock(int money)
{
    for (long int i = 0; i < 1000000; i++)
    {
        g_count++;
        g_balance += money;
        g_balance -= money;
    }
}

void test_unique_lock()
{
    FUNC_HEAD();
    thread thd1{save_withdraw, 10};
    thread thd2{save_withdraw, -20};
    thd1.join();
    thd2.join();
    cout << "balacne=" << g_balance << " g_count=" << g_count << endl;
}

void test_wo_unique_lock() //comparation /contrast to test_unique_lock()
{
    FUNC_HEAD();
    thread thd1{save_withdraw_wo_lock, 10};
    thread thd2{save_withdraw_wo_lock, -20};
    thd1.join();
    thd2.join();
    cout << "balacne=" << g_balance << " g_count=" << g_count << endl;
}

int main()
{
    test_hello();
    test_thread_function_object();
    test_thread_ref();

    test_unique_lock();
    test_wo_unique_lock();

    return 0;
}