using u_int = unsigned int;

/*
In fact, every standard-library container provides value_type as the name of its value type (Chapter
9). This allows us to write code that will work for every container that follows this convention. For
example:
template<typename C>
using Element_type = typename C::value_type; // the type of C’s elements
template<typename Container>
void algo(Container& c)
{
Vector<Element_type<Container>> vec; // keep results here
// ...
}

*/