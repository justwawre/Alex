/*
g++ -g -std=c++11 main.cpp
or 
clang++ -g -std=c++11 -stdlib=libc++ -lc++abi *.cpp
*/
#include <iostream>
#include <string>

#include <list>

#include "Vector.h"
#include "value_arg.h"
#include "func_template.h"
#include "functor.h"
#include "varidic_template.h"
#include "alias.h"

#include "../toolkit.h"

void parameterized_types()
{
  FUNC_HEAD();
  Vector<int> vd{1, 2, 3};
  cout << " sum of Vector<int> vd{1, 2, 3} :" << sum(vd) << endl;
}

void value_argument()
{
  FUNC_HEAD();
  Buffer<int, 4> buf;
  for (auto i = 0; i < buf.size(); i++)
  {
    buf.v[i] = i;
  }
}

void function_template()
{
  FUNC_HEAD();
  Vector<int> vi{1, 2, 3, 4, 5};
  int v;
  cout << "user defiend sum return:" << (v = sum(vi, 0)) << endl;
  cout << "user defiend sum return:" << (v = sum(vi, v)) << endl;
}

void f1(const Vector<int> &vec, const list<string> &lst, int x, const string &s)
{
  cout << "number of values less than " << x
       << ": " << count(vec, Less_than<int>{x})
       << '\n';
  cout << "number of values less than " << s
       << ": " << count(lst, Less_than<string>{s})
       << '\n';
}

void f2(const Vector<int> &vec, const list<string> &lst, int x, const string &s)
{
  /*
The notation [&](int a){ return a<x; } is called a lambda expression. It generates a function object
exactly like Less_than<int>{x}. The [&] is a capture list specifying that local names used (such as x)
will be accessed through references. Had we wanted to ‘‘capture’’ only x, we could have said so:
[&x]. Had we wanted to give the generated object a copy of x, we could have said so: [=x]. Capture
nothing is [ ],capture all local names used by reference is [&], and capture all local names used by
value is [=].

Using lambdas can be convenient and terse, but also obscure. For nontrivial actions (say, more
than a simple expression), I prefer to name the operation so as to more clearly state its purpose and
to make it available for use in several places in a program.

Using lambdas can be convenient and terse(简要的; 简短生硬的), but also obscure(adj.无名的; 鲜为人知的; 费解的; 难以理解的).
 For nontrivial (adj.	不容易的；非平凡; 非零的) actions (say, more
than a simple expression), I prefer to name the operation so as to more clearly state its purpose and
to make it available for use in several places in a program.

trivial	英[ˈtrɪviəl] 美[ˈtrɪviəl] adj.	不重要的; 琐碎的; 微不足道的

*/
  cout << "number of values less than " << x
       << ": " << count(vec, [&](int a) { return a < x; })
       << '\n';
  cout << "number of values less than " << s
       << ": " << count(lst, [&](const string &a) { return a < s; })
       << '\n';
}

void function_object()
{
  FUNC_HEAD();
  Less_than<int> lti{33};
  Less_than<string> lts{"abc"};
  cout << "22 less than 33:" << boolalpha << lti(22) << endl;
  cout << "def less than abc:" << boolalpha << lts("def") << endl;

  f1(Vector<int>{1, 2, 3}, list<string>{"abc", "def", "ghi"}, 3, "fgh");
  f2(Vector<int>{1, 2, 3}, list<string>{"abc", "def", "ghi"}, 3, "fgh");
}

void varidic_template()
{
  FUNC_HEAD();
  f(1, 2, 3, "hello");
  cout << endl;
  f("one", "two", "three", "end");
  cout << endl;
}

void test_alias()
{
  FUNC_HEAD();  
  u_int  i=333;
  cout << i << endl;

}

/****
 * 
 */

template <typename T = int, int n = 5>
class container
{
private:
  T arr[n];

public:
  void set(int i, T val) { arr[i] = val; }
  T get(int i) { return arr[i]; }
};

void class_template_test()
{
  FUNC_HEAD();
  container<float, 10> cc;
  cc.set(0, 1.1);
  cc.set(1, 2.2);
  cc.set(2, 3.3);
  cout << cc.get(0) << "\t" << cc.get(1) << "\t" << cc.get(2) << endl;
}

/*
What are templates for? In other words, what programming techniques are effective 
when you use templates?
 Templates offer:
• The ability to pass types (as well as values and templates) as arguments 
without loss of information. This implies excellent opportunities for inlining,
 of which current implementations take great advantage.
• Delayed type checking (done at instantiation time). This implies opportunities to
 weave together information from different contexts.
• The ability to pass constant values as arguments. This implies the ability to do 
compile-time computation. 

In other words, templates provide a powerful mechanism for compile-time computation and
 type manipulation that can lead to very compact and efficient code. Remember that 
 types (classes) can contain both code and values.

The first and most common use of templates is to support generic programming, that is, 
programming focused on the design, implementation, and use of general algorithms. 
Here, ‘‘general’’ means that an algorithm can be designed to accept a wide variety of
 types as long as they meet the algorithm’s requirements on its arguments. The template
  is C++’s main support for generic programming. Templates provide (compile-time) 
  parametric polymorphism.(所以语法问题ide没法发现,只有In instantiation of xxxx的时候才会发现)
*/

int main()
{
  parameterized_types();
  value_argument();
  function_template();

  function_object();
  varidic_template();

  test_alias();
  class_template_test();

  return 0;
}