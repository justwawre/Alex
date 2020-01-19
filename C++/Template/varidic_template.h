/* 
variadic template
 */

template <typename T>
void g(T x)
{
    cout << x << " ";
}

void f() {} // termination version
template <typename T, typename... tail>
void f(T head, tail... rest)
{
    g(head);
    f(rest...);
}

