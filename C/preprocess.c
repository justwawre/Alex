#include <stdio.h>
#include <stdlib.h>

#define NDEBUG     /* disable the assert in release sw */
#include <assert.h>

#define printDBF( exp ) printf( #exp " = %f ", exp )


int main()
{
    printDBF(2*3*4.0);
    return 0;
}