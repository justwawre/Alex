#include <stdio.h>
#include "toolkit.h"

char ga[] = "abcdefghijklm";
void address_of_array_test(void)
{
  FUNC_HEAD();
  printf(" addr of global array = %p \n", &ga);
  printf(" addr (ga[0]) = %p \n", &(ga[0]));
  printf(" addr (ga[1]) = %p \n\n", &(ga[1]));
}

void addres_of_array_param_test(char ca[10])
{
  FUNC_HEAD();
  printf(" addr of array param = %p \n", &ca);
  printf(" addr (ca[0]) = %p \n", &(ca[0]));
  printf(" addr (ca[1]) = %p \n", &(ca[1]));
  printf(" ++ca = %p \n\n", ++ca);
}

void addres_of_pointer_param_test(char *pa)
{
  FUNC_HEAD();
  printf(" addr of ptr param = %p \n", &pa);
  printf(" addr (pa[0]) = %p \n", &(pa[0]));
  printf(" addr (pa[1]) = %p \n", &(pa[1]));
  printf(" ++pa = %p \n", ++pa);
}

void alex_3(char *p, char *q)
{
  int a;
  printf(" addr of 1st local variable = %p \n", &a);
  printf(" addr of param q = %p \n", &q);
}
void alex_2(char *q, char *p)
{
  printf(" addr of param p= %p \n", &p);
  alex_3(p, q);
}
void transform_test(char *p)
{
  FUNC_HEAD();
  char *q = p;
  alex_2(q, p);
}

/*
这个测试，
-fstack-protector
或
-fno-stack-protector
结果是完全不一样的，前者如果缺省打开的话，就无法通过p/p2访问到PP/PP2的内容了

In the standard/stock GCC, stack protector is off by default. 
However, some Linux distributions have patched GCC to turn it on by default. 
12

If you compile with -fstack-protector, then there will be a little more space 
allocated on the stack and a little more overhead on entry to and return from 
a function while the code sets up the checks and then actually checks whether
 you've overwritten the stack while in the function

*/
void pointer_bias_test(void)
{
  FUNC_HEAD();
  //一个数组a,a 与 &a[0]意义完全相同
  //与&a意义完全不同，但是值相同。
  char pp[] = "0123456789abcde";
  char p[8] = "0123";
  printf(" ptr[0]:%s\n ptr[1]:%s\n ptr[2]:%s\n", p, (&p)[1], (&p)[2]);

  char pp2[] = "0123456789abcde";
  char p2[] = "0123";
  char pp3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  printf(" ptr[0]:%s\n ptr[1]:%s\n ptr[2]:%s\n ptr[-1]:%s\n", p2, (&p2)[1], (&p2)[2], (&p2)[-1]);
}

int main()
{
  address_of_array_test();
  addres_of_array_param_test(ga);
  addres_of_pointer_param_test(ga);
  transform_test(ga);
  pointer_bias_test();

  return 0;
}