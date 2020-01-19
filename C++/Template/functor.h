
/* 
function object (sometimes called a functor), which
is used to define objects that can be called like functions.

The function called operator() implements the ‘‘function call,’’ ‘‘call,’’ or ‘‘application’’ operator ().

 */
template <typename T>
class Less_than
{
    const T val; // value to compare against

public:
    Less_than(const T &v) : val(v) {}
    bool operator()(const T &x) const // call operator
    {
        return x < val;
    }
};

/*
count the occurrences of values for which a predicate(断言) returns true
*/
template <typename C, typename P>
int count(const C &c, P pred)
{
    int cnt = 0;
    for (const auto &x : c)
        if (pred(x))
            ++cnt;
    return cnt;
}