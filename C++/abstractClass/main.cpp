/*
g++ -g *.cpp
or 
clang++ -g -std=c++11 -stdlib=libc++ -lc++abi *.cpp
*/

#include <iostream>
// #include <algorithm>
// #include <string>
#include <stdexcept>
#include "Vector_container.h"
#include "List_container.h"

#include "../toolkit.h"

using namespace std;

void call_non_virtual(Container &c)
{
    cout << "the Class " << c.ss() << "'s method was called  " << endl;
}

void call_virtual(Container &c)
{
    cout << "the Class " << c.name() << "'s method was called  " << endl;
}

/*
show difference of  virtual function  vs non virtual function
*/
void call_method()
{
    FUNC_HEAD();
    //non virtual function
    Vector_container v{10};
    call_non_virtual(v);
    cout << "the Class " << v.ss() << "'s method was called  " << endl;
    //virtual function
    Container *p = new List_container{0};
    cout << "the Class " << p->name() << "'s method was called  " << endl;
    call_virtual(*p);
    delete p;
}

/*
exception handling
*/
void try_catch()
{
    FUNC_HEAD();

    //If an error can be found at compile time
    //static_asser t mechanism can be used for anything that can be expressed 
    //in terms of constant expressions
    static_assert(4<=sizeof(int), "integers are too small"); // check integer size

    List_container ll{1, 2, 3};
    try
    {
        cout << ll[ll.size()] << endl;
    }
    catch (range_error e)
    {
        cout << e.what() << "\t" << ll.size() << endl;
        throw;
    }
    catch (std::bad_alloc)
    {
        // Ouch! test() is not designed to handle memory exhaustion
        std::terminate(); // terminate the program
    }
}

void construction_types()
{
    FUNC_HEAD();
    Vector_container a(1);
    Vector_container b(2);
    Vector_container c({1, 2, 3, 4});
    Vector_container d(c);
    Vector_container e(move(d)); //effective, but move constructor seem not called
    b = c;
    a = std::move(c); // move constructor was called

    try_catch();
}

int main()
{
    call_method();
    construction_types();
    return 0;
}