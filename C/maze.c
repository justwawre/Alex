/*
some puzzling side of c language
tested via: gcc -std=c11 
*/
#include <stdio.h>
#include <unistd.h>
#include "toolkit.h"

/*
    difference between stdout & stderr
    stdout need "\n" or flush() explicitly.

    and return will flush the buffer implicitly
*/
inline void test_stdout_stderr();
void test_stdout_stderr()
{
    FUNC_HEAD();
    for (int i = 0; i < 3; i++)
    {
        fprintf(stdout, "hello-std-out");
        fprintf(stderr, "hello-std-err");
    }
}

/*
comma expression when init 
*/
void test_comma()
{
    FUNC_HEAD();
    int a = (1, 2); //int a = 1, 2; not allowed
    printf("a : %d\n", a);
}

void test_rtn_printf()
{
    FUNC_HEAD();
    int i = 43;
    printf("%d\n", printf("%d", printf("%d", i)));
}

void test_float_printf()
{
    FUNC_HEAD();
    float a = 12.5;
    printf("%d\n", a);
    printf("%d\n", (int)a);
    printf("%d\n", *(int *)&a);
}

/*
the expression of sizeof() was decided during compilation
*/
void test_sizeof()
{
    FUNC_HEAD();
    int i;
    i = 10;
    printf("i : %d\n", i);
    printf("sizeof(i++) is: %d\n", sizeof(i++));
    printf("i : %d\n", i);
}

void test_oct()
{
    FUNC_HEAD();
#define SIZEOF(arr) (sizeof(arr) / sizeof(arr[0]))
#define PrintInt(expr) printf("%s:%d\n", #expr, (expr))
    /* The powers of 10 */
    int pot[] = {
        0001,
        0010,
        0100,
        1000};

    int i;
    for (i = 0; i < SIZEOF(pot); i++)
        PrintInt(pot[i]);
}

/*
“hello”[2] == 2[“hello”]
*/
void test_idx_str()
{
    FUNC_HEAD();

    int a = 3, b = 5;

    printf(&a["Ya!Hello! how is this? %s\n"], &b["junk/super"]);

    printf(&a["WHAT%c%c%c  %c%c  %c !\n"], 1 ["this"],
           2 ["beauty"], 0 ["tool"], 0 ["is"], 3 ["sensitive"], 4 ["CCCCCC"]);
}

int main()
{
    test_stdout_stderr();
    test_comma();
    test_rtn_printf();
    test_float_printf();
    test_sizeof();
    test_oct();
    test_idx_str();

    return 0;
}