/* demo of qsort */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxNWords 100
#define MaxWordLength 20
char Word[MaxNWords][MaxWordLength]; /* array of words to be sorted */

int MyOwnStrcmp(const void *p, const void *q)
{
    return strcmp(p, q);
}

int main()
{
    int I, NWords;
    printf("enter words, with ctrl-d to end\n");
    for (NWords = 0;NWords < MaxNWords; NWords++)
    {
        if (scanf("%s", Word[NWords]) == -1)
            break;
    }
    qsort(Word, NWords, MaxWordLength, MyOwnStrcmp);
    printf("sorted array:\n");
    for (I = 0; I < NWords; I++)
        printf("%s\n", Word[I]);
}
