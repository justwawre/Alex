/*  gcc -g  func_pointer.c  -o func_pointer.exe -lm  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Add(double x, double y) { return x + y; }
double Sub(double x, double y) { return x - y; }
double Mul(double x, double y) { return x * y; }
double Div(double x, double y) { return x / y; }

typedef double (*func_t)(double, double);
func_t funcTable[] = {Add, Sub, Mul, Div, pow};
char *msgTable[] = {"Sum", "Difference", "Product", "Quotient", "Power"};

int main()
{
   double x = 0, y = 0;

   printf("Enter two operands for some arithmetic:\n");
   if (scanf("%lf %lf", &x, &y) != 2)
      printf("Invalid input.\n");

   for (int i = 0; i < 5; ++i)
      printf("%10s: %6.2f\n", msgTable[i], funcTable[i](x, y));

   return 0;
}
