
/*
here is some macros used in linux kernel
*/

struct st{
    int a;
    int b;
} st, *sp;
typedef  unsigned long size_t;  // typedef unsigned int size_t; if 32 bit

//here 
typedef struct  st * p2st;


#define offsetof(s, m)   (size_t)&(((s *)0)->m) 

//here type, member are name not variable
#define container_of(ptr, type, member) ({          \
        const typeof( ((type *)0)->member ) *__mptr = (const typeof( ((type *)0)->member ) *)(ptr); \
        (type *)( (char *)__mptr - offsetof(type,member) );\
        })

int main()
{
    int var = 666;
    typeof(&var) pvar = &var;  //pvar equal to &var,not only value but type
    int a=({1;2;4;})+10;       //a==14
    int bias = offsetof(struct st,b);

    st.a =3;
    st.b =4;
    typeof(&st.a) ptr = &st.a;
    sp  = container_of(ptr,struct st,a);

    p2st p;
    p = &st;
    return 0;


}