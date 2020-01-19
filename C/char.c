#include <stdio.h>

int main()
{
    char c = -1;
    /*char 编译器可以实现为带符号的，也可以实现为不带符号的 */
    if (c < 200)
    {
        printf("defaut char type is:signed\n");
    }
    else
    {
        printf("defaut char type is:unsigned\n");
    }

    for (unsigned char i = 254; i < 255; ++i) //if 256, loop become endless
    {
        printf("%d\n", i);
    }
    for (char i = 126; i < 127; ++i) //if 128, loop become endless
    {
        printf("%d\n", i);
    }

    char *p; //char *:Null-character (‘\0’) terminated character arrays
    unsigned char *q = "abc"; /* in modern c it  work same as char */
    printf("%s\n", q);
    return 0;
}