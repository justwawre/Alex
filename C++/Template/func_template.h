/* 
function template
Templates have many more uses than simply parameterizing a container with 
an element type. In particular, they are extensively used for parameterization 
of both types and algorithms in the standard library


This sum() is a simplified version of the standard-library accumulate()
Note how the types of the template arguments for sum<T,V> are deduced from the function
arguments. Fortunately, we do not need to explicitly specify those types.

 */
template <typename Container, typename Value>

/*
It can be invoked for any data structure that supports begin() and
end() so that the range-for will work. Such structures include the standard-library vector, list, and
map. Furthermore, the element type of the data structure is limited only by its use: it must be a type
that we can add to the Value argument. Examples are ints, doubles, and Matrixes (for any reasonable
definition of Matrix). We could say that the sum() algorithm is generic in two dimensions: the type
of the data structure used to store elements (‘‘the container’’) and the type of elements.

So, sum() requires that its first template argument is some kind of container and its second template
argument is some kind of number. We call such requirements concepts. Unfortunately, concepts
cannot be expressed directly in C++11.


alex:
https://en.cppreference.com/w/cpp/header/concepts
it is in c++20

*/
Value sum(Container &c, Value v)
{
    for (auto x : c)
    {
        v += x;
    }
    return v;
}
