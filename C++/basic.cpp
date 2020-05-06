#include <complex>
#include <iostream>
#include <exception>
#include "toolkit.h"

using namespace std;

void type_arithmetic_test() // function that doesn’t return a value
{
  FUNC_HEAD();

  double d1 = 2.3;
  double d2{2.3};
  complex<double> z = 1;
  complex<double> z2{d1, d2};
  complex<double> z3 = {1, 2};
  cout << "the complex z,z2,z3:" << z << " " << z2 << " " << z3 << endl;

  auto b = true;           // a bool
  auto ch = 'x';           // a char
  auto i = 123;            // an int
  auto d = 1.2;            // a double
  auto sqr_root = sqrt(d); // z has the type of whatever sqr t(y) retur ns
  cout << "auto variable:" << b << " " << ch << " " << i << " " << d << " " << sqr_root << " " << z << endl;

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

void data_size_test()
{
  FUNC_HEAD();
  cout << "size of datatype undder current cpu" << endl;
  cout << sizeof(short) << endl;
  cout << sizeof(int) << endl; //still 4 bytes as 32bit machine
  cout << sizeof(long) << endl;
  cout << sizeof(long long) << endl;
  cout << sizeof(float) << endl;
  cout << sizeof(double) << endl;

  string b;
  cout << sizeof(&b) << ":" << sizeof(b) << endl;
}

void ds_bias_test()
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

void exception_test()
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
  type_arithmetic_test();
  data_size_test();
  ds_bias_test();
  exception_test();
  return 0;
}
