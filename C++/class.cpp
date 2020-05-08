#include <iostream>
#include "toolkit.h"

using namespace std;

struct human
{
    string name;

private:
    int age;
};

class man : public human
{
public:
    bool married;
};
void struct_class_test()
{
    FUNC_HEAD();
    human *h = new man();
    h->name = "John";
    man *m = (man *)h;
    m->married = false;
    cout << "name: " << m->name << " married: " << m->married << endl;
}

class Account
{
private:
    static double m_rate;

public:
    static void set_rate(const double &x)
    {
        cout << "old rate = " << m_rate << " new rate = " << x << endl;
        m_rate = x;
    }
};
double Account::m_rate = 8.0;

void static_test()
{
    FUNC_HEAD();
    Account a;
    Account::set_rate(5.0);
    a.set_rate(7.0);
}

/*
 class a --> class b --> class c

*/

class a
{
public:
    a() { cout << "a" << endl; }
    virtual void disp() { cout << "a disp" << endl; }
    virtual ~a() { cout << "~a" << endl; }
};

class b : public a
{
public:
    b() { cout << "b" << endl; }
    ~b() { cout << "~b" << endl; }
};

class c : public b
{
public:
    c() { cout << "c" << endl; }
    void disp() { cout << "c:disp" << endl; }
    ~c() { cout << "~c" << endl; }
};

/* 
check the sequence of construction/deconstruction
and virtual function
*/
void virtual_test()
{
    FUNC_HEAD();
    a *p = new c();
    cout << "call virtual function via object pointer" << endl;
    p->disp();
    delete p; //must free explicitly

    a a_object;
    cout << "call virtual function via object" << endl;
    a_object.disp();
}

class StackIter;

class Stack
{
private:
    int items[10];
    int sp;

public:
    friend class StackIter;
    Stack()
    {
        sp = -1;
    }
    void push(int in)
    {
        items[++sp] = in;
    }
    int pop()
    {
        return items[sp--];
    }
    bool isEmpty()
    {
        return (sp == -1);
    }
    StackIter *createIterator() const;
};

class StackIter
{
    const Stack *stk;
    int index;

public:
    StackIter(const Stack *s)
    {
        stk = s;
    }
    void first()
    {
        index = 0;
    }
    void next()
    {
        index++;
    }
    bool isDone()
    {
        return index == stk->sp + 1;
    }
    int currentItem()
    {
        return stk->items[index];
    }
};

StackIter *Stack::createIterator() const
{
    return new StackIter(this);
}

bool operator==(const Stack &l, const Stack &r)
{

    StackIter *itl = l.createIterator();
    StackIter *itr = r.createIterator();

    for (itl->first(), itr->first(); !itl->isDone(); itl->next(), itr->next())
        if (itl->currentItem() != itr->currentItem())
            break;
    bool ans = itl->isDone() && itr->isDone();
    delete itl;
    delete itr;
    return ans;
}

/* 
the example of friend class
 */
void friend_test()
{
    FUNC_HEAD();
    Stack s1;
    for (int i = 1; i < 5; i++)
        s1.push(i);
    Stack s2(s1), s3(s1); //no copy construction defined, using default one
    s3.pop();
    cout << "s1==s2?: " << (s1 == s2) << endl;
    /*
    if not equal, it mean the default copy constuction deep copy the
       int items[10];
    */
    cout << "s1==s3?: " << (s1 == s3) << endl;
}

struct USCurrency
{
    int dollars;
    int cents;
    USCurrency operator+(const USCurrency c)
    {
        this->cents += c.cents;
        this->dollars += c.dollars;
        if (this->cents >= 100)
        {
            this->cents -= 100;
            this->dollars++;
        }
        return *this;
    }
};

ostream &operator<<(ostream &out, const USCurrency &c)
{
    out << "$" << c.dollars << "." << c.cents;
    return out;
}

/*
override the operator  +， <<
 */
int operator_test()
{
    FUNC_HEAD();
    USCurrency a = {2, 50};
    USCurrency b = {1, 75};
    USCurrency c = a + b;
    cout << c << endl;
    return 0;
}

class Empty
{
};

void f()
{
    Empty a, b;
    if (&a == &b)
        cout << "impossible: report error to compiler supplier";

    Empty *p1 = new Empty;
    Empty *p2 = new Empty;
    if (p1 == p2)
        cout << "impossible: report error to compiler supplier";
}

struct X : Empty
{
    int a;
    // ...
};

void f(X *p)
{
    void *p1 = p;
    void *p2 = &p->a;
    if (p1 == p2)
        cout << "nice: good optimizer\n";
}

class B
{
public:
    int f(int i)
    {
        cout << "f(int): ";
        return i;
    }
    // ...
};

class D : public B
{
public:
    using B::f; // make every f from B available
    double f(double d)
    {
        cout << "f(double): ";
        return d;
    }
    // ...
};

/******
 * 
http://www.stroustrup.com/bstechfaq.htm
*/

void empty_class_test()
{
    FUNC_HEAD();
    f();
    struct X b;
    f(&b);

    D *pd = new D;
    cout << pd->f(2) << '\n';
    cout << pd->f(2.3) << '\n';
}

int main()
{
    struct_class_test();
    static_test();
    virtual_test();
    friend_test();
    operator_test();
    empty_class_test();
    return 0;
}
