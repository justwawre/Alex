/*
compiler shall be above -std=c++1z
 */

#include <iostream>
#include "toolkit.h"
using namespace std;

constexpr int fibonacci(const int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void const_test()
{
    FUNC_HEAD();
    constexpr const int i1 = 5;
    constexpr int i2 = 5;
    static constexpr int i3 = 5;
    const int dmv = 17;
    int var = 17;
    constexpr double max1 = 1.4 * dmv;
    // constexpr double max2 = 1.4 * var; // error : var is not a constant expression
    const double max3 = 1.4 * var; // OK, may be evaluated at run time
    cout << fibonacci(5) << endl;
}

/*
(gdb) l print_type_info
Function "print_type_info" not defined.
*/
template <typename T>
auto print_type_info(const T &t)
{
    if constexpr (std ::is_integral<T>::value) //when gdb, this statement don't existed at all
    {
        return t + 1;
    }
    else
    {
        return t + 0.001;
    }
}

int a = 5.2;
int b(5.2);
auto d = int(5.2);

void type_info_test()
{
    FUNC_HEAD();
    cout << print_type_info(5) << endl;
    cout << print_type_info(3.14) << endl;
}
#include <string.h>
int main()
{
    const_test();
    type_info_test();
    const char *s = "Hello\0Hi";

    cout << strlen(s) << " " << sizeof(s);

    return 0;
}