#include <iostream>
#include <memory>
#include "toolkit.h"
using namespace std;

void foo(shared_ptr<int> i)
{
    (*i)++;
}
void shared_ptr_test()
{
    FUNC_HEAD();
    // auto pointer = new int (10) ; // 非法, 不允许直接赋值
    // 构造了一个 shared_ptr
    auto pointer = make_shared<int>(10);
    foo(pointer);
    cout << *pointer << endl; // 11
    // 离开作用域前， shared_ptr 会被析构， 从而释放内存
}

void shared_ptr_reset_test()
{
    FUNC_HEAD();
    auto pointer = make_shared<int>(10);
    auto pointer2 = pointer; // 引用计数+1
    auto pointer3 = pointer; // 引用计数+1
    int *p = pointer.get();

    pointer.reset();                                                       // 这样不会增加引用计数
    cout << " pointer . use_count () = " << pointer.use_count() << endl;   // 3
    cout << " pointer2 . use_count () = " << pointer2.use_count() << endl; //

    cout << " pointer3 . use_count () = " << pointer3.use_count() << endl; //

    pointer2.reset();
    cout << " reset pointer2 :" << endl;
    cout << " pointer . use_count () = " << pointer.use_count() << endl;   // 2
    cout << " pointer2 . use_count () = " << pointer2.use_count() << endl; // pointer2 已reset
    cout
        << " pointer3 . use_count () = " << pointer3.use_count() << endl; //

    pointer3.reset();
    cout << " reset pointer3 :" << endl;
    cout << " pointer.use_count () = " << pointer.use_count() << endl;   // 1
    cout << " pointer2.use_count () = " << pointer2.use_count() << endl; //
    cout << " pointer3.use_count () = " << pointer3.use_count() << endl; //
}

struct A;
struct B;

struct A
{
    shared_ptr<B> pointer;
    ~A()
    {
        cout << "A destroyed" << endl;
    }
};

struct B
{
    shared_ptr<A> pointer;
    ~B()
    {
        cout << "B destroyed" << endl;
    }
};

int shared_ptr2_test()
{
    FUNC_HEAD();
    auto a = make_shared<A>();
    auto b = make_shared<B>();
    a->pointer = b;
    b->pointer = a;

    /* 如果不设置nullptr，A, B 都不会被销毁，这是因为a,b 内部的pointer 同时又引用了b,a，这使得a,b 的引
用计数均变为了2，而离开作用域时，a,b 智能指针被析构，却只能造成这块区域的引用计数减一， */

    a->pointer = nullptr;
    b->pointer = nullptr;
}

struct Foo
{
    Foo() { cout << " Foo :: Foo " << endl; }
    ~Foo() { cout << "Foo ::~ Foo " << endl; }
    void foo() { cout << "not null" << endl; }
};

void f(const Foo &)
{
    cout << "f(const Foo &)" << endl;
}

//unique_ptr 可以移动，但不能拷贝
int unique_ptr_test()
{
    FUNC_HEAD();
    unique_ptr<Foo> p1 = make_unique<Foo>();
    if (p1)
    {
        p1->foo();
    }

    {
        unique_ptr<Foo> p2(move(p1));
        // p2 不空, 输出
        f(*p2);
        // p2 不空, 输出
        if (p2)
            p2->foo();
        // p1 为空, 无输出
        if (p1)
            p1->foo();
        p1 = move(p2);
        // p2 为空, 无输出
        if (p2)
            p2->foo();
    }
    // p1 不空, 输出
    if (p1)
        p1->foo();
    // Foo 的实例会在离开作用域时被销毁
}

template <typename T>
void check_weakptr(weak_ptr<T> &weak_ptr)
{
    cout << "use_count == " << weak_ptr.use_count() << ": ";
    if (auto spt = weak_ptr.lock()) //must copy to a shared_ptr before usage
    {
        cout << "the value is " << *spt << "\n";
    }
    else
    {
        cout << "the weak ptr is expired already\n";
    }
}

/*
weak_ptr 允许你共享但不拥有某对象，一旦最末一个拥有该对象的智能指针失去了所有权，任何 weak_ptr 都会自动成空（empty）
因此，在 default 和 copy 构造函数之外，weak_ptr 只提供 “接受一个 shared_ptr” 的构造函数。
*/

void weak_ptr_test()
{
    weak_ptr<int> wp;

    FUNC_HEAD();
    {
        auto sp = std::make_shared<int>(99);
        wp = sp;
        cout << "when assigned a shared ptr inside the code block:" << endl;
        check_weakptr(wp);
    }
    cout << "when exit the code block:" << endl;
    check_weakptr(wp);
}

struct C;
struct D;

struct C
{
    weak_ptr<D> pointer;
    ~C()
    {
        cout << "C destroyed" << endl;
    }
};

struct D
{
    weak_ptr<C> pointer;
    ~D()
    {
        cout << "D destroyed" << endl;
    }
};

/*
打破环状引用（cycles of references，两个其实已经没有被使用的对象彼此互指，使之看似还在 “被使用” 的状态）的问题
In contrast to shared_ptr2_test()
*/
int weak_ptr2_test()
{
    FUNC_HEAD();
    auto a = make_shared<C>();
    auto b = make_shared<D>();
    a->pointer = b;
    b->pointer = a;
}

int main()
{
    shared_ptr_test();
    shared_ptr_reset_test();
    shared_ptr2_test();

    unique_ptr_test();

    weak_ptr_test();
    weak_ptr2_test();

    return 0;
}