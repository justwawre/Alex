/*
mock of STL veector, to demo  typen as parameter
Templates are a compile-time mechanism, so their use incurs no run-time overhead 
compared to hand-crafted code.
*/
#ifndef VECTOR_H
#define VECTOR_H
#include <initializer_list>
using namespace std;

template <typename T>
class Vector
{
public:
  typedef T value_type; //note
  Vector();
  explicit Vector(int);

  Vector(std::initializer_list<T>);
  void push_back(const T &); //copy into Vector
  void push_back(T &&);      //move into Vector

  //use const as possible,otherwise the func begin()... will report error
  T &operator[](int) const;
  int size() const;
  int capacity() const;
  void reserve(int); //increase capacity
  ~Vector();

private:
  T *elem;  // elem points to an array of sz doubles
  T *space; // first unused slot
  int sz;
};

template <typename T>
Vector<T>::Vector() : sz{0} {}

template <typename T>
Vector<T>::Vector(int s)
{
  if (s < 0)
    throw invalid_argument("negative size");
  elem = new T[s];
  sz = s;
  space = elem;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> l)
    : elem{new T[l.size()]}, sz{static_cast<int>(l.size())}
{
  copy(l.begin(), l.end(), elem);
  space = elem + sz;
}

template <typename T>
Vector<T>::~Vector()
{
  if (sz > 0)
  {
    delete[] elem;
    sz = 0;
  }
}

template <typename T>
T &Vector<T>::operator[](const int i) const
{
  if (i >= 0 && i < size())
    return elem[i];
  else
    throw out_of_range("operator[] wrong idx");
}

template <typename T>
int Vector<T>::size() const
{
  return space - elem;
}

template <typename T>
//const修饰的成员函数不能修改任何的成员变量(mutable修饰的变量除外)
//const成员函数不能调用非onst成员函数，因为非const成员函数可以会修改成员变量
int Vector<T>::capacity() const
{
  return sz;
}

template <typename T>
void Vector<T>::reserve(const int newsz)
{
  T *p = new T[newsz];

  for (int i = 0; i < sz; i++)
  {
    p[i] = elem[i];
  }
  delete[] elem;
  elem = p;
  space = elem + sz;
  sz = newsz;
}

template <typename T>
void Vector<T>::push_back(const T &d)
{
  if (capacity() < size() + 1)
    reserve(size() == 0 ? 8 : 2 * size());
  *space = d; // initialize the space *

  ++space;
}

template <typename T>
void Vector<T>::push_back(T &&d)
{
  if (capacity() < size() + 1)
    reserve(size() == 0 ? 8 : 2 * size());
  *space = d; // initialize the space *
  ++space;
}

template <typename T>
T *begin(const Vector<T> &x)
{
  return x.size() ? &x[0] : nullptr;
}

template <typename T>
T *end(const Vector<T> &x)
{
  return begin(x) + x.size();
}

template <typename T>
T sum(const Vector<T> &v)
{
  T sum = 0;
  for (auto &x : v)
    sum += x;
  return sum;
}

template <typename T>
Vector<T> &read(Vector<T> &v, istream &is)
{
  cout << "please input the   list " << endl;
  //in WSL, end the input via Ctrl-d
  typename Vector<T>::value_type d;
  for (; is >> d; v.push_back(d))
    ;
  cin.clear();
  cin.ignore(100, '\n');
  return v;
}

#endif