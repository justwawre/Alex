#include "Vector_container.h" // get the interface
#include <algorithm>
#include <iostream>
#include <exception>

using namespace std;

Vector_container::Vector_container() : sz{0} {}

Vector_container::Vector_container(int s)
    : elem{new double[s]},
      sz{s} // initialize members
{
  for (auto i = 0; i < sz; i++)
    elem[i] = 0;
}

Vector_container::Vector_container(std::initializer_list<double> l)
    : elem{new double[l.size()]}, sz{static_cast<int>(l.size())}
{
  copy(l.begin(), l.end(), elem);
}

Vector_container::Vector_container(const Vector_container &a)
{
  sz = a.sz;
  elem = new double[sz];
  for (auto i = 0; i < sz; i++)
    elem[i] = a.elem[i];
}
Vector_container::Vector_container(Vector_container &&a)
    : elem{a.elem}, sz(a.sz)
{
  a.sz = 0;
  a.elem = nullptr;
}

Vector_container &Vector_container::operator=(const Vector_container &a) //copy
{
  if (sz > 0)
  {
    delete[] elem;
  }
  sz = a.sz;
  elem = new double[a.sz];
  for (auto i = 0; i < sz; i++)
    elem[i] = a.elem[i];
  return *this; //*this
}

Vector_container &Vector_container::operator=(Vector_container &&a) //move
{
  cout << "move construction called" << endl;
  if (sz > 0)
    delete[] elem;
  sz = a.sz;
  elem = a.elem;
  a.sz = 0;
  a.elem = nullptr;
  return *this;
}

Vector_container::~Vector_container()
{
  if (sz > 0)
  {
    delete[] elem;
    sz = 0;
  }
}

double &Vector_container::operator[](int i)
{

  if (i >= 0 && i < sz)
    return elem[i];
  else
    throw out_of_range("wrong idx");
}
int Vector_container::size() const { return sz; }

void Vector_container::push_back(double d)
{
  double *p = new double[sz + 1];

  for (auto i = 0; i < sz; i++)
    p[i] = elem[i];
  p[sz] = d;
  if (sz > 0)
    delete[] elem;
  elem = p;
  sz++;
}
