/* 
* g++ -Wall -std=c++1z mutex.cpp -lpthread
*/
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include "../toolkit.h"

using namespace std;
mutex mutex_simple;

struct F
{ // function object
  vector<double> &v;
  double *res;
  F(vector<double> &vv, double *r) : v{vv}, res(r) {}

  // fuction object
  void operator()()
  {
    cout << __func__ << endl;
    *res = 0;
    for (auto x : v)
    {
      mutex_simple.lock();
      cout << x << "\t";
      mutex_simple.unlock();
      *res += x;
    }
    cout << endl;
  };
};

void f(vector<double> &v, double &sum)
{
  FUNC_HEAD();
  sum = 0;
  for (auto x : v)
  {
    mutex_simple.lock();
    cout << x << "\t";
    mutex_simple.unlock();
    sum += x;
  }
  cout << endl;
}

mutex m_cout;
void f_seq(vector<double> &v, double &sum)
{
  FUNC_HEAD();
  sum = 0;
  //比std:lock_guard更加灵活。
  unique_lock lck{m_cout};
  for (auto x : v)
  {
    cout << x << "\t";
    sum += x;
  }
  cout << endl;
  cout.flush();
}

#include <utility>
void mutex_test()
{
  FUNC_HEAD();
  vector<double> some_vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<double> vec2{10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

  double res1;
  double res2;
  cout << "two thread will print 0~19 in two sequence" << endl;
  thread t1(f, ref(some_vec), ref(res1));
  thread t2{F{vec2, &res2}}; // F(vec2)() executes in a separate thread
  t1.join();
  t2.join();
  cout << "thread 1 return:" + to_string(res1) +
              "\t thread 2 return:" + to_string(res2) + "\n" +
              "two thread will print 0~19 in one sequence\n";

  thread t3(f, ref(some_vec), ref(res1));
  thread t4(f, ref(vec2), ref(res2));
  t3.join();
  t4.join();
  cout << "thread 1 return:" + to_string(res1) +
              "\t thread 2 return:" + to_string(res2) + "\n";
}

class some_data
{
  int a;
  std::string b;

public:
  void do_something() { cout << "do_something\n"; };
};

class data_wrapper
{
private:
  some_data data;
  std::mutex mutex_simple;

public:
  template <typename Function>
  void process_data(Function func)
  {
    std::lock_guard<std::mutex> l(mutex_simple);
    func(data); // 1 传递“保护”数据给用户函数
  }
};

some_data *unprotected;

void malicious_function(some_data &protected_data)
{
  unprotected = &protected_data;
}

void bypass_mutex_test()
{
  data_wrapper x;
  FUNC_HEAD();
  x.process_data(malicious_function); // 2 传递一个恶意函数
  unprotected->do_something();        // 3 在无保护的情况下访问保护数据
}

thread_local int g_n = 1;
void f_local()
{
  for (auto i = 0; i < 100000; i++)
    g_n++;
  cout << __func__ << ":\t" << g_n << endl;
}

void g_local()
{
  thread_local int j = 0;
  for (auto i = 0; i < 100000; i++)
    j++;
  cout << __func__ << ":\t" << g_n << "\t" << j << endl;
}

void thread_local_test()
{
  FUNC_HEAD();
  thread t1(f_local);
  thread t2(f_local);
  thread t3(g_local);
  thread t4(g_local);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
}

// 一个函数被称为线程安全的（thread-safe），当且仅当被多个并发进程反复调用时，它会一直产生正确的结果
int gi = 1000;
mutex m_gi;

void thread_safe_1()
{
  int i = 0;
  i++;
  //C++17中添加了一个新特性，称为模板类参数推导，这样类似std::locak_guard这样简单的模板类型的模板参数列表可以省略。
  //lock_guard<mutex> guard(m_gi);
  lock_guard guard(m_gi);

  /*
    C++中通过实例化std::mutex创建互斥量实例，通过成员函数lock()对互斥量上锁，unlock()进行解锁。不过，实践中不推荐直接去调用成员函数，调用成员函数就意味着，必须在每个函数出口都要去调用unlock()，也包括异常的情况。C++标准库为互斥量提供了一个RAII语法的模板类std::lock_guard，在构造时就能提供已锁的互斥量，并在析构的时候进行解锁，从而保证了一个已锁互斥量能被正确解锁。
   */

  //m_gi.lock();
  gi += 100;
  //m_gi.unlock();
}

void thread_safe_2()
{
  int j = 0;
  j++;
  lock_guard guard(m_gi);
  gi -= 100;
}

void thread_safe_test()
{
  FUNC_HEAD();

  cout << "start with gi=:\t" << gi << endl;
  thread t1(thread_safe_2);
  thread t2(thread_safe_1);
  thread t3(thread_safe_1);
  thread t4(thread_safe_2);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  cout << "end with gi=:\t" << gi << endl;
}

//可重入函数：可重入函数是线程安全函数的一种，其特点在于它们被多个线程调用时，不会引用任何共享数据。
//可重入函数通常要比不可重入的线程安全函数效率高一些，因为它们不需要同步操作。
void add_r(int &balance, int change)
{
  balance += change;
}

void thread_reentrant_1()
{
  int i = 100;
  add_r(gi, i);
}

void thread_reentrant_2()
{
  int i = 100;
  add_r(gi, -i);
}

void thread_reentrant_test()
{
  FUNC_HEAD();
  cout << "start with gi=" << gi << endl;
  thread t1(thread_reentrant_2);
  thread t2(thread_reentrant_1);
  thread t3(thread_reentrant_1);
  thread t4(thread_reentrant_2);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  cout << "end with gi=" << gi << endl;
}

int main()
{
  mutex_test();
  bypass_mutex_test();

  thread_local_test();
  thread_safe_test();
  thread_reentrant_test();
  return 0;
}
