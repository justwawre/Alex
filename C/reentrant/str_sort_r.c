/* 
the reentrant usage of qsort_r()  
gcc -D_GNU_SOURCE   str_sort_r.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxNWords 100
#define MaxWordLength 20
char Word[MaxNWords][MaxWordLength]; /* array of words to be sorted */

int MyOwnStrcmp(const void *p, const void *q, void *unsed)
{
    return strcmp(p, q);
}

int main()
{
    int I, NWords;
    printf("enter words, with ctrl-d to end\n");
    for (NWords = 0; NWords < MaxNWords; NWords++)
    {
        if (scanf("%s", Word[NWords]) == -1)
            break;
    }
    int arg;
    qsort_r(Word, NWords, MaxWordLength, MyOwnStrcmp, &arg);
    printf("sorted array:\n");
    for (I = 0; I < NWords; I++)
        printf("%s\n", Word[I]);
}
