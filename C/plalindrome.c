/* geneate plalindrome in one setence. 
$ ./a.out
3
4
5
6
7
6
5
4
3
 */

#include <stdio.h>
int p(int i, int N)   //in web
{
    return printf("%d \n", i) && (N > i) && (p(i + 1, N) || p(i, i));
}
int p2(int i, int N)  //by alex
{
    return (i < N) && printf("%d \n", i) && (p(i + 1, N), printf("%d\n", i));
}

int main()
{
    p2(2, 8);
    return 0;
}