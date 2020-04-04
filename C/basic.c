#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include "toolkit.h"

/* 
assert macro
If the macro NDEBUG is defined (above the statement that includes assert.h!),
 the assert macro does absolutely nothing.
[alex@clang]$gcc -DDEBUG -E test.c  -o a.c     用来传递DEBUG的定义
[alex@clang]$clang -DDEBUG -E test.c  -o a.c
 */
void char_space()
{
  char a;
  int c;
  char b;
  printf("addres of a is %p, of b is %p \n", &a,&b);
}


//handle the overlap issue just like libc
char *strcpy_alex(char *restrict strDest, const char *restrict strSrc)
{
  assert(strDest != NULL && strSrc != NULL && strSrc != strDest);
  char *address = strDest;
  if (strDest < strSrc)
  {
    for (; *strSrc;)
    {
      *strDest = *strSrc;
      strDest++;
      strSrc++;
    }
    *strDest = '\0';
  }
  else
  {
    for (; *strSrc;)
    {
      strDest++;
      strSrc++;
    }
    for (; address <= strDest;)
    {
      *strDest = *strSrc;
      strDest--;
      strSrc--;
    }
  }

  return address;
}
/* 
bad example that  make garbage collection difficult or impossible
char *s = (char *) malloc(1024);
s -= 10000;
restrict是c99标准引入的，它只可以用于限定和约束指针，并表明指针是访问一个数据对象的唯一
且初始的方式.即它告诉编译器，所有修改该指针所指向内存中内容的操作都必须通过该指针来修改
关键字restrict有两个读者。一个是编译器，它告诉编译器可以自由地做一些有关优化的假定。
另一个读者是用户，他告诉用户仅使用满足restrict要求的参数。一般，编译器无法检查您
是否遵循了这一限制，如果您蔑视它也就是在让自己冒险。
 */

//make sure it func same as strlen() in libc
int strlen_alex(const char *restrict pStr)
{

  assert(pStr != NULL);
  const char *addr = pStr;
  for (; *pStr; pStr++)
    ;
  return pStr - addr;
}

void str_func_test()
{
  FUNC_HEAD();

  char_space();

  char str[30];
  char *p = &(str[5]);
  strcpy_alex(p, "123456");
  printf("the src=123456 the dest=%s\n", p);

  char *p1 = &(str[20]);
  strcpy_alex(p1, p);
  printf("the src=123456 the dest=%s\n", p1);

  strcpy_alex(str, p);
  printf("the src=123456 the dest=%s\n", str);

  int len = sizeof(str) / sizeof(str[0]);
  strncpy(str, "123456789012", len - 1);
  str[len - 1] = '\0';
  printf("original str=123456789012 after strncpy %s\n", str);

  assert(strlen_alex(str) == strlen(str));

  int (*func)(const char *) = strlen_alex;
  printf("sizof(func pointer) in 64bit system is :%lu\n", sizeof(func));
}

int swap_int(int *p, int *q)
{
  *p ^= *q;
  *q ^= *p;
  *p ^= *q;
  return 0;
}

void swap_test()
{
  FUNC_HEAD();
  int a = 3, b = 4;
  swap_int(&a, &b);
}

void endian_test()
{
  FUNC_HEAD();
  typedef union {
    int a;
    char c;
  } word_t;
  word_t w;
  w.a = 1;
  if (w.c == '\1')
    printf("little endian\n");
  else
    printf("big endian\n");
}

enum sizes
{
  small = 7,
  medium,
  large = 10,
  humungous
};

void enmum_test()
{
  FUNC_HEAD();
  printf("the enum are:\n %d %d %d %d\n", small, medium, large, humungous);
}

void op_test()
{
  FUNC_HEAD();
  int a = 7, b = 5;
  printf("7/5=%d, 7%%5=%d\n", a / b, a % b);
  int sz = 10;
  for (int i = 0; i < sz; i++)
  {
    printf("%d %d \n", i, (i + sz - 1) % sz);
  }
}

const char *func1() { return "here return a const char * "; }
void const_return_test()
{
  FUNC_HEAD();
  const char *s1 = func1();
  printf("%s\n", s1);
}

char *func2(char *dst)
{
  strcpy(dst, "copy the this sentence to in param: char *\n");
  return dst;
}

void in_param_test()
{
  FUNC_HEAD();
  /* 
内存分配函数,与malloc,calloc,realloc类似.alloca是GNU 函数, 在栈(stack)上申请空间,用完马上就释放.
 */
  char *s2 = malloc(100 * sizeof(char));
  if (s2 != NULL)
  {
    func2(s2);
    printf("return: %s\n", s2);
    free(s2); //
  }
}

#define ISUNSIGNED(a) (a >= 0 && ~a >= 0)
#define ISUNSIGNED_T(type) ((type)0 - 1 > 0)
void sign_test(void)
{
  FUNC_HEAD();
  unsigned int ut = 1;
  printf("%d\n", ISUNSIGNED(ut));
  printf("%d\n", ISUNSIGNED_T(unsigned int));

  signed int st = 1;
  printf("%d\n", ISUNSIGNED(st));
  printf("%d\n", ISUNSIGNED_T(signed int));
}

struct person
{
  char *name;
  char gender;
  int age;
  int weight;
  struct
  {
    int area_code;
    long phone_number;
  };
};

struct person2
{
  char *name;
  union {
    int i;
    char c;
  };
};

void anonymous_union_test(void)
{
  FUNC_HEAD();
  struct person jim = {"jim", 'F', 28, 65, {21, 58545566}};
  struct person2 wang;
  wang.name = "wang";
  wang.c = 'A'; //0x41 A
  printf("%d\n", jim.area_code);
  printf("%x\n", wang.i);
}

unsigned int avg(unsigned int a, unsigned int b)
{
  return (a >> 1) + (b >> 1) + (a & b & 1);
}

unsigned int avg_overflow(unsigned int a, unsigned int b)
{
  return (a + b) / 2;
}

unsigned int avg_upgrade(unsigned int a, unsigned int b)
{
  return ((long)a + (long)b) / 2;
}

void avg_test(void)
{
  FUNC_HEAD();

  printf("avg return: %ud\n", avg(-1, -1));
  printf("avg_overflow return: %ud\n", avg_overflow(-1, -1));
  printf("avg_upgrade return: %ud\n", avg_upgrade(-1, -1));
}

int main()
{
  enmum_test();
  op_test();
  const_return_test();
  in_param_test();
  sign_test();
  str_func_test();
  swap_test();
  endian_test();
  anonymous_union_test();
  avg_test();

  return 0;
}
