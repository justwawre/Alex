#include <stdio.h>
#include <string.h>
#include "toolkit.h"

int count_1_in_bits(unsigned long bitset)
{
    int count = 0;
    while (bitset)
    {
        bitset &= bitset - 1;
        count++;
    }
    return count;
}

void count_test()
{
    FUNC_HEAD();
    unsigned long l = 0;

    printf("count of 1 in 0x%lx = %d\n", l, count_1_in_bits(l));

    l += 1 << 0;
    printf("count of 1 in 0x%lx = %d\n", l, count_1_in_bits(l));

    l += 1 << 1;
    printf("count of 1 in 0x%lx = %d\n", l, count_1_in_bits(l));

    l += 1 << 2;
    printf("count of 1 in 0x%lx = %d\n", l, count_1_in_bits(l));

    l += 1 << 4;
    printf("count of 1 in 0x%lx = %d\n", l, count_1_in_bits(l));

    l += 1 << 9;
    printf("count of 1 in 0x%lx = %d\n", l, count_1_in_bits(l));

    l += 1 << 15;
    printf("count of 1 in 0x%lX = %d\n", l, count_1_in_bits(l));
}

int reversal(int a)
{
    return ~a + 1;
}

void reversal_test()
{
    FUNC_HEAD();
    int i;
    i = 100;
    printf("original %d, after reversal %d \n", i, reversal(i));

    i = -88;
    printf("original %d, after reversal %d \n", i, reversal(i));
}
int main()
{
    count_test();
    reversal_test();
    return 0;
}
