/*
C++对于左值和右值没有标准定义，但是有一个被广泛认同的说法：可以取地址的，有名字的，非临时的就是左值；不能取地址的，没有名字的，临时的就是右值；
可见立即数，函数返回的值等都是右值；而非匿名对象(包括变量)，函数返回的引用，const对象等都是左值。从本质上理解，创建和销毁由编译器幕后控制，
程序员只能确保在本行代码有效的，就是右值(包括立即数)；而用户创建的，通过作用域规则可知其生存期的，就是左值(包括函数返回的局部变量的引用以及const对象)。
定义右值引用的格式如下：类型 && 引用名 = 右值表达式;
右值引用的存在并不是为了取代左值引用，而是充分利用右值(特别是临时对象)的构造来减少对象构造和析构操作以达到提高效率的目的。

而C++11 中为了引入强大的右值引用，将右值的概念进行了进一步的划分，
分为：纯右值、将亡值。
    纯右值(prvalue, pure rvalue)
    将亡值(xvalue, expiring value)，
*/

#include <iostream>
#include <string>
#include <utility> //  move
#include <vector>
using namespace std;

void reference(string &str)
{
    cout << "type lvalue" << endl;
}
void reference(string &&str)
{
    cout << "type rvalue" << endl;
}

void reference(int &v)
{
    cout << " 左值" << endl;
}
void reference(int &&v)
{
    cout << " 右值" << endl;
}

template <typename T>
void pass(T &&v)
{
    cout << " 普通传参:";
    reference(v); // 始终调用reference ( int & )
}

template <typename T>
void pass2(T &&v)
{
    cout << " 普通传参:";
    reference(v);
    cout << "  move 传参:";
    reference(move(v));
    cout << "  forward 传参:";
    reference(forward<T>(v));
}

class A
{
public:
    int *pointer;
    A() : pointer(new int(1)) { cout << " 构造" << pointer << endl; }
    A(A &a) : pointer(new int(*a.pointer)) { cout << " 拷贝" << pointer << endl; } // 无意义的对象拷贝
    A(A &&a) : pointer(a.pointer)
    {
        a.pointer = nullptr;
        cout << " 移动" << pointer << endl;
    }
    ~A()
    {
        cout << " 析构" << pointer << endl;
        delete pointer;
    }
};

// 防止编译器优化
A return_rvalue(bool test)
{
    A a, b;
    if (test)
        return a;
    else
        return b;
}

int main()
{
    cout << "<--------------------------右值引用和左值引用" << endl;
    string lv1 = "rvalue test 1"; // lv1 是一个左值
    //  string && r1 = lv1 ; // 非法, 右值引用不能引用左值
    string &&rv1 = move(lv1); // 合法,  move 可以将左值转移为右值
    cout << rv1 << endl;

    const string &lv2 = lv1 + lv1; // 合法, 常量左值引用能够延长临时变量的生命周期
    // lv2 += " Test "; // 非法, 常量引用无法被修改
    cout << lv2 << endl;

    string &&rv2 = lv1 + lv2; // 合法, 右值引用延长临时对象生命周期
    rv2 += " Test ";                // 合法, 非常量引用能够修改临时变量
    cout << rv2 << endl;
    reference(rv2); // 输出左值

    cout << "<--------------------------移动语义" << endl;
    A obj = return_rvalue(false); //A(A &&a) 被调用
    cout << " obj :" << endl;
    cout << obj.pointer << endl;
    cout << *obj.pointer << endl;

    cout << "<--------------------------避免了无意义的拷贝构造" << endl;
    string str = " Hello world .";
    vector<string> v;

    // 将使用push_back ( const T&) , 即产生拷贝行为
    v.push_back(str);
    // 将输出"str : Hello world ."
    cout << " str : " << str << endl;

    // 将使用push_back ( const T&&) , 不会出现拷贝行为
    // 而整个字符串会被移动到vector 中， 所以有时候 move 会用来减少拷贝出现的开销
    // 这步操作后, str 中的值会变为空
    v.push_back(move(str));
    // 将输出"str : "
    cout << "empty string expected after move:" << str << endl;

    cout << "<--------------------------非完美转发" << endl;
    cout << " 传递右值:" << endl;
    pass(1); // 1 是右值, 但输出左值
    cout << " 传递左值:" << endl;
    auto i1 = 1;
    pass(i1); // i1 是左引用, 输出左值

    cout << "<--------------------------完美转发" << endl;
    //std::forward 即没有造成任何多余的拷贝，同时完美转发(传递) 了函数的实参给了内部调用的其他函数
    cout << " 传递右值:" << endl;
    pass2(1);
    cout << " 传递左值:" << endl;
    pass2(i1);

    return 0;
}
