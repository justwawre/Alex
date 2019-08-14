#include <stdlib.h>
int s;
int main()
{
	{
	 int xxx = rand();
	 int yyy = rand();
	 int xxx_2 = rand();
	 int yyy_2 = rand();
	 int xxx_3 = rand();
	 int yyy_3 = rand();
	 
	 if (xxx>100)
		 s +=(xxx+yyy + xxx_2+yyy_2+xxx_3+yyy_3);
	}
	{
	 int xxx = rand();
	 int yyy = rand();
	 int xxx_2 = rand();
	 int yyy_2 = rand();
	 int xxx_3 = rand();
	 int yyy_3 = rand();
	 if (yyy>300)
		 s -=(xxx+yyy + xxx_2+yyy_2+xxx_3+yyy_3);
	}
	return s;
}

/*
flacc -O3 -S 

*/

