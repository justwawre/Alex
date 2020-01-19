#include <stdio.h>

int a[] = {1, 2, 3};
extern int i, j;
char * str = "abcdefghijkl\n";
int main()
{
    i = a[1] + a[2];
    j = i;
    return puts(str);
}
