#include <stdio.h>

int array[] = {23, 34, 12, 17, 204, 99, 16};
#define TOTAL_ELEMENTS (sizeof(array) / sizeof(array[0]))

int main()
{

  // because here is unsigned char,can promoted to int type ,
  if (-1 < (unsigned char)1)
    printf("-1 is less than (unsigned char) 1: ANSI semantics\n ");
  else
    printf("-1 NOT less than (unsigned char) 1: K&R semantics \n");

  int d = -1, x;

  // TOTAL_ELEMENTS has type unsigned int because sizeof is "unsigned"
  // comparing a signed int with an unsigned int quantity. So d is promoted to unsigned int.

  if (d <= TOTAL_ELEMENTS - 2)
    x = array[d + 1];
  else
    x = 0;

  printf("x=%d\n", x);

  return 0;
}