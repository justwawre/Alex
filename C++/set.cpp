#include <iostream>
#include <set>
#include <bitset>
#include <algorithm>
#include "../toolkit.h"

using namespace std;

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
