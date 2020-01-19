#include <iostream>
#include <memory>
#include "../toolkit.h"
using namespace std;

/*
test_shared_ptr()
 */
void foo(shared_ptr<int> i)
{
    (*i)++;
}
void test_shared_ptr()
{
    FUNC_HEAD();
    // auto pointer = new int (10) ; // 非法, 不允许直接赋值
    // 构造了一个 shared_ptr
    auto pointer = make_shared<int>(10);
    foo(pointer);
    cout << *pointer << endl; // 11
    // 离开作用域前， shared_ptr 会被析构， 从而释放内存
}

/*
test_shared_ptr2()
 */

//reset() 来减少一个引用计数???   use_count()来查看一个对象的引用计数。
void test_shared_ptr2()
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

/*
test_shared_ptr3()
 */
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

/* 运行结果是A, B 都不会被销毁，这是因为a,b 内部的pointer 同时又引用了a,b，这使得a,b 的引
用计数均变为了2，而离开作用域时，a,b 智能指针被析构，却只能造成这块区域的引用计数减一， */
int test_shared_ptr3()
{
    FUNC_HEAD();
    auto a = make_shared<A>();
    auto b = make_shared<B>();
    // a->pointer = b;
    // b->pointer = a;
}

/*
test_unique_ptr()
 */

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
int test_unique_ptr()
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

/*

test_weak_ptr()
 */
std::weak_ptr<int> gw;

void observe()
{
    std::cout << "use_count == " << gw.use_count() << ": ";
    if (auto spt = gw.lock())
    { // Has to be copied into a shared_ptr before usage
        std::cout << *spt << "\n";
    }
    else
    {
        std::cout << "gw is expired\n";
    }
}

void test_weak_ptr()
{
    FUNC_HEAD();
    {
        auto sp = std::make_shared<int>(42);
        gw = sp;

        observe();
    }

    observe();
}

/*
test_weak_ptr2()
 */
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

int test_weak_ptr2()
{
    FUNC_HEAD();
    auto a = make_shared<C>();
    auto b = make_shared<D>();
    a->pointer = b;
    b->pointer = a;
}

int main()
{
    test_shared_ptr();
    test_shared_ptr2();

    test_shared_ptr3();

    test_unique_ptr();

    test_weak_ptr();
    test_weak_ptr2();

    return 0;
}