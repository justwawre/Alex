#include "List_container.h"
#include <iostream>
#include <initializer_list>
#include <stdexcept>

using namespace std;

List_container::List_container() {}

List_container::List_container(initializer_list<double> ll) : ld{ll} {}

double &List_container::operator[](int i)
{
    for (auto &x : ld)
    {
        if (i == 0)
        {
            return x;
        }
        else
        {
            i--;
        }
    }
    throw range_error("List container met wrong index");
}

int List_container::size() const
{
    return ld.size();
}

List_container::~List_container()
{
}