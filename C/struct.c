#include <stdio.h>
#include <string.h>
#include "toolkit.h"

/* 
C treats structures as if they were primitive data types
Passing a structure as an argument or Assignments do a deep copy of the entire structure
 */
void deepcopy_test()
{
    FUNC_HEAD();
    struct employee
    {
        int id;
        char name[20];
    };

    struct employee lee, john;
    lee.id = 1;
    strncpy(lee.name, "yes", sizeof(lee.name));
    john = lee;
    printf("deep copy ? %s", john.name);
}

struct bits_unsigned // int is 32 bit even in 64 bit CPU/OS
{
    unsigned int low : 2;
    unsigned int high : 30;
    unsigned int i;
};

void unsigned_struct_test()
{
    FUNC_HEAD();
    struct bits_unsigned b = {-1};
    unsigned int xxx;
    int xx;
    xxx = b.low;
    xx = b.low;
    printf(" orignal value -1, now %d or %d\n", xxx, xx);
}

struct bits_signed
{
    signed int low : 2;     //range: -2~1 ,
    signed int middle : 20; //
    signed int high : 10;   //
    signed int i;
};

void signed_struct_test()
{
    FUNC_HEAD();
    struct bits_signed a = {-1}; //the other field was initialized as 0
    int x;
    unsigned xx;

    x = a.low;
    xx = a.low;
    printf(" orignal value -1, now %d or %d\n", x, xx);

    a.low = 0;
    x = a.low;
    xx = a.low;
    printf(" orignal value 2, now %d or %d\n", x, xx);

    a.low = 1;
    x = a.low;
    xx = a.low;
    printf(" orignal value 1, now %d or %d\n", x, xx);

    a.low = 2;
    x = a.low;
    xx = a.low;
    printf(" orignal value 2, now %d or %d\n", x, xx);

    a.low = 3;
    x = a.low;
    xx = a.low;
    printf(" orignal value 3, now %d or %d\n", x, xx);

    /*
     warning: overflow in implicit constant conversion [-Woverflow]
     a.low = 4;
    */
}

struct bits_mix // int is 32 bit even in 64 bit CPU/OS
{
    unsigned int low : 2;
    signed int mid : 2;
    unsigned int high : 28;
    unsigned int i;
};

void mix_struct_test()
{
    FUNC_HEAD();
    struct bits_mix b = {-1, -1};
    unsigned int xxx;
    int xx;
    xxx = b.low;
    xx = b.low;
    printf(" orignal value -1, now %d or %d\n", xxx, xx);

    xxx = b.mid;
    xx = b.mid;
    printf(" orignal value -1, now %d or %d\n", xxx, xx);
}

struct array_t
{
    size_t length;
    char data[0];
};
void Zero_Length_Array_test()
{
    FUNC_HEAD();
    struct array_t array;
    printf(" struct size %lu, array size %lu\n", sizeof(array), sizeof(array) - sizeof(size_t));
}

/*
tests show: when you define the bits field as signed or unsigned, the value retrived from it was 
fixed as signed or unsigned
*/
int main()
{
    deepcopy_test();
    unsigned_struct_test();
    signed_struct_test();
    mix_struct_test();
    Zero_Length_Array_test();
    return 0;
}
