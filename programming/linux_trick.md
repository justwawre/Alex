# macro typeof 
是GNU C 标准中的一个扩展特性.自动推导后面 ( ) 里的数据类型.

a simple example
```C
int var = 666;
typeof(&var) pvar = &var;

```
# macro container_of
a complicated one container_of
```C
//copy from kernel
struct st{
    int a;
    int b;
} st, *sp;
typedef  unsigned long size_t;  // typedef unsigned int size_t; if 32 bit

#define offsetof(s, m)   (size_t)&(((s *)0)->m) 

//here type, member are name not variable
#define container_of(ptr, type, member) ({          \
        const typeof( ((type *)0)->member ) *__mptr = (const typeof( ((type *)0)->member ) *)(ptr); \
        (type *)( (char *)__mptr - offsetof(type,member) );\
        })

int main()  //my test code
{
    int var = 666;
    typeof(&var) pvar = &var;  //pvar equal to &var,not only value but type
    int a=({1;2;4;})+10;       //a==14
    int bias = offsetof(struct st,b);

    st.a =3;
    st.b =4;
    typeof(&st.a) ptr = &st.a;
    sp  = container_of(ptr,struct st,a);
    return 0;
}

```
实现根据一个成员指针ptr去找它的container地址的功能是非常简单的,就 ptr - bias; 难点在于需要声明ptr, 和它container的类型,这样就不够通用了。

但linux kernel中 linked list是一种类似STL iterator 一样的设计, 适用于任何container, 所以必须要用macro 来解决.( 哈哈, STL本质也是一种macro!!)

