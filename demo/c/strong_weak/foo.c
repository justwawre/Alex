/* gcc *.c */
#include <stdio.h>
void f(void);
char * str = "foo"; 
int  x = 1;
int main()  
{ 
    f(); 
    printf("x=%d str=%s\n", x,str); 
    return 0;
} 