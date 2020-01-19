#include <complex>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <exception>
#include "../toolkit.h"

using namespace std;

void foo() // function that doesn’t return a value
{
  FUNC_HEAD();
  double d = 2.2; // initialize floating-point number
  int i = 7;      // initialize integer
  d = d + i;      // assign sum to d
  i = d * i;      // assign product to i (truncating the double d*i to an int)

  double d1 = 2.3;
  double d2{2.3};
  complex<double> z = 1; // a complex number with double-precision floating-point scalars
  complex<double> z2{d1, d2};
  complex<double> z3 = {1, 2}; // the = is optional with { ... }

  auto bb = true;    // a bool
  auto chch = 'x';   // a char
  auto ii = 123;     // an int
  auto dd = 1.2;     // a double
  auto zz = sqrt(d); // z has the type of whatever sqr t(y) retur ns

  auto x = 3;
  auto y = 5;
  x += y; // x = x+y
  ++x;    // increment: x = x+1
  x -= y; // x = x-y
  --x;    // decrement: x = x-1
  x *= y; // scaling: x = x*y
  x /= y; // scaling: x = x/y
  x %= y; // x = x%y


}


void sizes()
{
  FUNC_HEAD();
  cout << sizeof(short) << endl;
  cout << sizeof(int) << endl;
  cout << sizeof(long) << endl;
  cout << sizeof(long long) << endl;

  cout << sizeof(float) << endl;
  cout << sizeof(double) << endl;

  int a = 2;
  string b;
  LINE_NO();
  cout << &a << "\t" << sizeof(&a) << endl;
  LINE_NO();
  cout << &b << "\t" << sizeof(&b) << ":" << sizeof(b) << endl;
}


void find_bias()
{
  typedef struct
  {
    int a;
    int b;
  } struc_t;
  FUNC_HEAD();
  struc_t a;
  cout << static_cast<void *>(&(a.b)) << ":" << static_cast<void *>(&a) << endl;
  size_t bias = (char *)&(a.b) - (char *)(&a);
  cout << bias << endl;

  bias = (size_t) & (((struc_t *)0)->b);
  cout << bias << endl;
}


void catch_exception()
{
  int x = 1;
  int y = 0;
  FUNC_HEAD();
  try
  {
    x /= y;
  }
  catch (exception &err)
  {
    cerr << err.what() << endl;
  }
}

int main()
{
  foo();
  sizes();
  find_bias();
  catch_exception(); //must be last one, because it will abort() the execution
  return 0;
}
