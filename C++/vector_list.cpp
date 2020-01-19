#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include "../toolkit.h"
using namespace std;

void test_vec_list()
{
  FUNC_HEAD();
  vector<int> v;
  list<int> l;
  for (int i = 0; i < 8; i++)
  {
    v.push_back(i);
    l.push_back(i);
  }

  cout << "vector:";
  for (auto i : v)
    cout << i << " ";
  cout << endl;
  cout << "first itertor point to:" << *(v.begin()) << endl;
  cout << "last iterator point to:" << *(v.end() - 1) << endl;
  cout << "3rd itertor point to:" << *(v.begin() + 2) << endl;

  list<int>::iterator itl = l.begin();
  // list::iterator中重载了++，只能使用++进行迭代访问。
  cout << "list:\n";
  for (; itl != l.end(); itl++)
    cout << *itl << endl;
}

template <typename T>
T sum(const vector<T> &v) //will not modify its argument
{
  T sum = 0;
  for (auto i : v)
    sum += i;
  return sum;
}

void test_vec_sum()
{
  FUNC_HEAD();
  vector<double> v{1.2, 3.4, 4.5}; // v is not a constant
  const double s1 = sum(v);        // OK: evaluated at run time
  cout << s1 << endl;
  // constexpr double s3 = sum(v); // error : sum(v) not constant expression
}

int main()
{
  test_vec_list();
  test_vec_sum();

  return 0;
}