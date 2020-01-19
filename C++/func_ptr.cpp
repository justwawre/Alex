/*
  
clang 6.0 :
clang++ -std=c++14  func_ptr.cpp

C++11 std::function 是一种通用、多态的函数封装，它的实例可以对任何可以调用的目标实体进
行存储、复制和调用操作，它也是对C++ 中现有的可调用实体的一种类型安全的包裹（相对来说，函
数指针的调用不是类型安全的），换句话说，就是函数的容器。当我们有了函数的容器之后便能够更加方
便的将函数、函数指针作为对象进行处理。
*/

#include <functional>

#include <iostream>
#include "../toolkit.h"
using namespace std;

int foo()
{
    return 5;
}

int goo()
{
    return 6;
}

void func_ptr_test()
{
    FUNC_HEAD();
    int (*fcnPtr)() = foo;
    fcnPtr = goo;
    cout << fcnPtr() << endl;
}

/*
 Introduced in C++11, an alternative method of defining and storing function pointers
 */
void function_2011_test()
{
    FUNC_HEAD();
    std::function<int()> fcnPtr = foo; // declare function pointer that returns an int and takes no parameters
    fcnPtr = goo;                      // fcnPtr now points to function goo
    std::cout << fcnPtr();             // call the function just like normal
    cout << endl;
}

void function_auto_test()
{
    FUNC_HEAD();
    auto fcnPtr = foo;
    fcnPtr = goo;
    cout << fcnPtr() << endl;
}

int foo2(int para)
{
    return para;
}

int foo3(int a, int b, int c)
{
    return a + b + c;
}

void function_para_test()
{
    FUNC_HEAD();
    //  function 包装了一个返回值为int , 参数为int 的函数
    function<int(int)> func = foo2;

    int important = 10;
    function<int(int)> func_lambda = [&](int value) -> int {
        return 1 + value + important;
    };
    auto r1 = func(10);
    auto r2 = func_lambda(10);

    // 将参数1 ,2 绑定到函数foo 上， 但是使用std :: placeholders :: _1 来对第一个参数进行占位
    auto bindFoo = bind(foo3, std ::placeholders ::_1, 2, 3);
    // 这时调用bindFoo 时， 只需要提供第一个参数即可
    auto r3 = bindFoo(1);
}

int main()
{
    func_ptr_test();
    function_2011_test();
    function_auto_test();
    function_para_test();
    return 0;
}