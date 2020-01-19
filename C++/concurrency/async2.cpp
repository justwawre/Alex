/*
$ g++ -std=c++14 async2.cpp -lpthread
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <future>
#include "../toolkit.h"
using namespace std;

template <typename Iterator, typename T>
T async_sum(Iterator first, Iterator last, T init)
{
  FUNC_HEAD();

  int const length = distance(first, last);
  if (!length)
    return init;

  int const min_per_thread = 1000;
  int const max_threads =
      (length + min_per_thread - 1) / min_per_thread;

  int const hardware_threads = thread::hardware_concurrency();

  cout << " hardware_threads: " << hardware_threads << endl;
  int const num_threads = min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  cout << " num_threads: " << num_threads << endl;
  int const block_size = length / num_threads;

  vector<future<int>> threads(num_threads);

  auto iter = first;
  for (auto i = 0; i < num_threads; ++i)
  {
    auto iter_end = iter + block_size;
    if (i == num_threads - 1)
    {
      iter_end = last;
    }
    /*
The template function async runs the function f asynchronously
 (potentially in a separate thread which may be part of a thread pool) 
 and returns a future that will eventually hold the result of that function call.

 limitation: no rsource lock needed
*/
    threads[i] = async(accumulate<Iterator, T>, iter, iter_end, 0);
    iter = iter_end;
  }
  T sum = 0;
  for (auto &t : threads)
  {
    sum += t.get();
  }
  return sum;
}

int main()
{
  struct {
    int a;
    int b;
  } ccc;
  ccc.a = 1;
  int reqtbs = 200;
  int  tb = 25;
  reqtbs = (reqtbs << 13) +tb;
  
  tb = reqtbs & 0xffff;
  reqtbs = reqtbs >> 13;

  vector<int> v(1000000, 1);
  int init = 0;
  auto sum = async_sum(v.begin(), v.end(), init);
  cout << "The sum =" << sum << endl;
}