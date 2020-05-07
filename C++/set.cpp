#include <iostream>
#include <set>
#include <bitset>
#include <algorithm>
#include "toolkit.h"

using namespace std;

/*
首先set，不像map那样是key-value对，它的key与value是相同的。
STL中的set，用的是红黑树；hash_set，底层用得是hash table。
红黑树与hash table最大的不同是，红黑树是有序结构，而hash table不是。
set应该更加被强调理解为“集合”，而集合所涉及的操作并、交、差等，
即STL提供的如交集set_intersection()、并集set_union()、差集set_difference()和对称差集set_symmetric_difference()，
都需要进行大量的比较工作，那么使用底层是有序结构的红黑树就十分恰当了，这也是其相对hash结构的优势所在。
*/

int set_test()
{
    FUNC_HEAD();
    set<int> iset;
    iset.insert(11);
    iset.insert(55);
    iset.insert(33);
    iset.insert(44);
    iset.insert(22);
    iset.insert(11);
    iset.insert(55);

    set<int>::iterator it;
    cout << "items of the set： ";
    for (it = iset.begin(); it != iset.end(); it++)
    {
        cout << *it << "\t";
    }
    cout << endl;

    int i = 33;
    cout << i;
    if (binary_search(iset.begin(), iset.end(), i))
        cout << " found in the set " << endl;
    else
        cout << " not found int the set " << endl;
}

void print_binary(int i)
{
    bitset<sizeof(int) * 8> b = i;
    cout << i << "=" << b.to_string() << '\n';
}

void bitset_test()
{
    FUNC_HEAD();

    bitset<9> bs1{"110001111"}; // 399
    bitset<9> bs2{399};

    bitset<9> bs3 = ~bs1;      // complement: bs3=="001110000"   512-bs1-1
    bitset<9> bs4 = bs1 & bs3; // all zeros
    bitset<9> bs5 = bs1 << 2;  // shift left: bs5 = "111000000"
    cout << "bs5=" << bs5 << endl;

    print_binary(0xfe);
}

int main()
{
    set_test();
    bitset_test();

    return 0;
}
