#include <stdio.h>
#include "toolkit.h"
void print_array(char *str, int a[], int n)
{
    printf("%s:\n", str);
    for (int i = 0; i < n; i++)
    {
        printf("%4d", a[i]);
    }
    printf("\n");
}

void bubble_test(int a[], int n)
{
    FUNC_HEAD();
    print_array("before sort:", a, n);

    int i, j, t;
    for (i = n-1; i >0; i--)
        for (j = 0; j < i; j++)
            if (a[j] > a[j + 1])
            {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }

    print_array("after sort:", a, n);
}

int main()
{
    int a[10] = {12, 45, 7, 8, 96, 4, 10, 48, 2, 46};
    bubble_test(a, 10);

    return 0;
}
