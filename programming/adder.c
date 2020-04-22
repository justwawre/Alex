#include <stdio.h>
static int x;
int add(int y)
{
    return x + y;
}
int main()
{
    x = 5;
    printf("%d", add(3));
}