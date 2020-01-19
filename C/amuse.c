#include <stdio.h>
#include <stdlib.h>
#include "toolkit.h"

const int w = 23;
const int h = 20;
typedef int (*fp_t)(int x, int y);

int f1(int x, int y)
{
    return (x - 10) * (x - 10) + (y - 10) * (y - 10) <= 8 * 8;
}

int f2(int x, int y)
{
    return x <= y;
}

int f3(int x, int y)
{
    return abs(x - 11) <= y;
}

int f4(int x, int y)
{
    return abs(x - 11) <= y;
}

int triangle(int x, int y)
{
    return abs(x) <= y;
}
int f5(int x, int y)
{
    return triangle(x % 6 - 2, y % 3);
}

int f6(int x, int y)
{
    return triangle(x - 11, y) &&
           triangle((x + y / 3 * 3 + 3) % 6 - 2, y % 3);
}

void pause()
{
    puts("press return to continue");
    while (getchar() != '\n')
        ;
}

/* 一个通用的类似如下规律图形的方法/框架

    *           *           *           *
  * * *       * * *       * * *       * * *
* * * * *   * * * * *   * * * * *   * * * * *
*/

void print_pic(fp_t f)
{
    int x, y;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
            printf(f(x, y) ? "* " : "  ");
        puts("");
    }
}
int ascii_pic_test()
{
    FUNC_HEAD();

    print_pic(f1);

    pause();
    print_pic(f2);

    pause();
    print_pic(f3);

    pause();
    print_pic(f4);

    pause();
    print_pic(f5);

    pause();
    print_pic(f6);

    return 0;
}

/****
 * 输出9*9口诀。共9行9列，i控制行，j控制列
 */
void table_9_9_test()
{
    FUNC_HEAD();
    printf("the 9*9 table:\n");
    int i, j;
    for (i = 1; i < 10; i++)
    {
        for (j = 1; j < 10; j++)
        {
            printf("%d*%d=%-3d", i, j, i * j); /*-3d表示左对齐，占3位*/
        }
        printf("\n"); /*每一行后换行*/
    }
}

/*
古典问题：有一对兔子，从出生后第3个月起每个月都生一对兔子，
小兔子长到第三个月后每个月又生一对兔子，假如兔子都不死，问每个月的兔子总数为多少？
兔子的规律为数列1,1,2,3,5,8,13,21....
*/
void rabbit_test()
{
    FUNC_HEAD();
    long f1, f2;
    int i;
    printf("num of rabbit of each month are\n");
    f1 = f2 = 1;
    for (i = 1; i <= 20; i++)
    {
        if (i % 5 == 1)
            printf("month %2d: ", i * 2 - 1);
        printf("%12ld%12ld", f1, f2);
        if (i % 5 == 0)
            printf("\n"); /*控制输出，每行四个*/
        f1 = f1 + f2;     /*because the habbit of first month produce*/
        f2 = f1 + f2;     /*because the habbit of 2nd month produce**/
    }
}

/* 
*一个数如果恰好等于它的因子之和，这个数就称为“完数”。例如6=1＋2＋3.编程
　　　找出1000以内的所有完数
 */
void perfect_number_test()
{
    FUNC_HEAD();
    static int k[10];
    int i, j, n, s;
    for (j = 2; j < 1000; j++)
    {
        int n = 0;
        int s = j;
        for (i = 1; i < j; i++)
        {
            if ((j % i) == 0)
            {
                s = s - i;
                k[n++] = i;
            }
        }
        if (s == 0)
        {
            printf("%d=%d", j, k[0]);
            for (i = 1; i < n; i++)
                printf("+%d", k[i]);
            printf("\n");
        }
    }
}
/*
编程打印直角杨辉三角形
*/
void YH_triangle_test()
{
    FUNC_HEAD();
    int i, j, a[6][6];
    for (i = 0; i <= 5; i++)
    {
        a[i][i] = 1;
        a[i][0] = 1;
    }
    for (i = 2; i <= 5; i++)
        for (j = 1; j <= i - 1; j++)
            a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
    for (i = 0; i <= 5; i++)
    {
        for (j = 0; j <= i; j++)
            printf("%4d", a[i][j]);
        printf("\n");
    }
}

int main()
{
    ascii_pic_test();
    table_9_9_test();
    rabbit_test();
    perfect_number_test();
    YH_triangle_test();

    return 0;
}
