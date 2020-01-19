/*
In addition to type arguments, a template can take value arguments.
*/

template <typename T, int N>
struct Buffer
{
    using value_type = T; //many container provide "value_type"
    int size() { return N; }
    T v[N];
};