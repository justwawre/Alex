//g++  -g -std=c++14

#include <algorithm>
#include <chrono>
#include <cmath>
#include <forward_list>
#include <iostream>
#include <memory>
#include <vector>
#include "../toolkit.h"

using namespace std;

/*************
 * equal_range_test()
 * https://en.cppreference.com/w/cpp/algorithm/equal_range
 */

struct S
{
  int number;
  char name;
  // note: name is ignored by this comparison operator
  bool operator<(const S &s) const { return number < s.number; }
};

ostream &operator<<(ostream &os, const S &s)
{
  os << "{" << s.number << "," << s.name << "}";
  return os;
}

int equal_range_test()
{
  FUNC_HEAD();
  // note: not ordered, only partitioned w.r.t. S defined below
  std::vector<S> vec = {{1, 'A'}, {2, 'B'}, {2, 'C'}, {2, 'D'}, {4, 'G'}, {3, 'F'}};

  S value = {2, '?'};

  //Returns a range containing all elements equivalent to value in the range [first, last).
  //The range [first, last) must be at least partially ordered with respect to value,
  auto p = std::equal_range(vec.begin(), vec.end(), value);
  cout << "in the vec,  the elements matched with " << value << "are:" << endl;
  for (auto i = p.first; i != p.second; ++i)
    std::cout << i->name << ' ';
  std::cout << std::endl;

  // heterogeneous comparison:
  struct Comp
  {
    bool operator()(const S &s, int i) const { return s.number < i; }
    bool operator()(int i, const S &s) const { return i < s.number; }
  };

  int num = 2;
  cout << "in the vec, the elements matched with " << num << " are:" << endl;
  p = std::equal_range(vec.begin(), vec.end(), num, Comp{});
  for (auto i = p.first; i != p.second; ++i)
    std::cout << i->name << ' ';
  std::cout << std::endl;

  num = 3;
  cout << "in the vec, the elements matched with " << num << " are:" << endl;
  p = std::equal_range(vec.begin(), vec.end(), num, Comp{});
  for (auto i = p.first; i != p.second; ++i)
    std::cout << *i << ' ';
  std::cout << std::endl;

  sort(vec.begin(), vec.end(), [](const S &s1, const S &s2) { return s1.number < s2.number; });
  cout << "vec after sort are:" << endl;
  for (auto &v : vec)
    std::cout << v << ' ';
  std::cout << std::endl;

  num = 3;
  cout << "in the vec, the elements matched with " << num << " are:" << endl;
  p = std::equal_range(vec.begin(), vec.end(), num, Comp{});
  for (auto i = p.first; i != p.second; ++i)
    std::cout << *i<< ' ';
  std::cout << std::endl;
}

/*************************
 * for limit_test()
 * 
 */

void limit_test()
{
  FUNC_HEAD();
  constexpr float min = numeric_limits<float>::min();
  constexpr int szi = sizeof(int);
  cout << min << endl;
  cout << szi << endl;
}

/*
sort_test()

 */
template <typename C>
using Iterator_type = typename C::iterator; // C’s iterator type
template <typename Iter>
using Iterator_category =
    typename std::iterator_traits<Iter>::iterator_category; // Iter’s categor y

template <typename Ran> // for random-access iterators
void sort_helper(Ran beg, Ran end,
                 random_access_iterator_tag) // we can subscript into [beg:end)
{
  sort(beg, end); // just sort it
}

template <typename C>
using Value_type = typename C::value_type; // C’s value type

template <typename For> // for forward iterators
void sort_helper(For beg, For end,
                 forward_iterator_tag) // we can traverse [beg:end)
{
  vector<Value_type<For>> v{beg, end}; // initialize a vector from [beg:end)
  sort(v.begin(), v.end());
  copy(v.begin(), v.end(), beg); // copy the elements back
}

template <typename C>
void sort(C &c)
{
  using Iter = Iterator_type<C>;
  sort_helper(c.begin(), c.end(), Iterator_category<Iter>{});
}

template <typename T>
constexpr bool Is_arithmetic()
{
  return std::is_arithmetic<T>::value;
}

void new_sort(vector<string> &v, forward_list<int> &lst)
{
  sort(v);   // sor t the vector
  sort(lst); // sor t the singly-linked list
}

void sort_test()
{
  FUNC_HEAD();

  vector<string> v{"abc", "kkk", "jjj"};
  forward_list<int> lst{7, 8, 1};
  new_sort(v, lst);
}

/*
 predict_test()
 */
void predict_test()
{
  FUNC_HEAD();

  bool b1 = Is_arithmetic<int>();
  bool b2 = Is_arithmetic<string>();
  cout << b1 << endl
       << b2 << endl;
}

int main()
{
  equal_range_test();
  limit_test();
  sort_test();
  predict_test();
  return 0;
}