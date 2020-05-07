#include <iostream>
#include "toolkit.h"

using namespace std;

void test_1()
{
    FUNC_HEAD();
    int i = 1;
    //与参数传值类似，值捕获的前提是变量可以拷贝，不同之处则在于，被捕获的变量在lambda 表达
    //式被创建时拷贝，而非调用时才拷贝：
    auto copy_value = [i] {
        return i;
    };
    i = 100;
    auto j = copy_value();
    cout << "i=" << i << "\t"
         << "j=" << j << endl;
}

void test_2()
{
    FUNC_HEAD();
    int i = 1;
    auto copy_value = [&i] {
        return i;
    };
    i = 100;
    auto j = copy_value();
    cout << "i=" << i << "\t"
         << "j=" << j << endl;
}

/*
手动书写捕获列表有时候是非常复杂的，这种机械性的工作可以交给编译器来处理，这时候可以在
捕获列表中写一个& 或= 向编译器声明采用引用捕获或者值捕获.
 */
void test_3()
{
    FUNC_HEAD();
    int i = 1;
    auto copy_value = [&] {
        return i;
    };
    i = 100;
    auto j = copy_value();
    cout << "i=" << i << "\t"
         << "j=" << j << endl;
}

//泛型Lambda
auto add = [](auto x, auto y) {
    return x + y;
};

void test_4()
{
    FUNC_HEAD();
    auto i = add(1, 2);
    auto j = add(3.3, 4.4);
    cout << "i=" << i << "\t"
         << "j=" << j << endl;
}

// Lambda 表达式的本质是一个和函数对象类型相似的类类型（称为闭包类型）的对象（称为闭包对
// 象），当Lambda 表达式的捕获列表为空时，闭包对象还能够转换为函数指针值进行传递
using foo = void(int);
void functional(foo f) // 定义在参数列表中的函数类型foo 被视为退化后的函数指针类型foo *
{
    f(1); // 通过函数指针调用函数
}

void test_5()
{
    FUNC_HEAD();
    auto f = [](int value) {
        cout << "param list:" << value << endl;
    };
    functional(f); // 传递闭包对象， 隐式转换为foo * 类型的函数指针值
}

int main()
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
}