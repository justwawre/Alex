***dsp mem optimization*** 

CONTENTS             
[TOC]
*Xu YangChun Aug/14/2019*

<!-- pagebreak -->
## Introduction
The leessons learned when try to free some DSP memory in last sprint.
## background
* related DSP/its thread
```c
/* Add global variables that do NOT require initialisation within the following
 * # pragma */
#pragma nostdinit on
var1;
var2;
....
varn;
#pragma nostdinit off
/* >> JOB Entrypoint: ULMACCE_SCHED_start
******************************************************************************/
void ULMACCE_SCHEDFO_start()
{
  SESCHEDFO_init();
  func1();
  func2();
  SESCHEDFO_main();
  ....
  funcn();
}

```  
* issue 
the the thread's heap+stack usage is over its limit 98%

## analysis
* the direct cause 
is data struct change, a U16 field was added to struct A.
and it is used in several func();
* althogh warning is "heap+stack", dynmaic memory not allowed in this dsp role 
* so to reduce memory usage in func()
* or outside: the global variable's space?

<!-- pagebreak -->
## global variables
* usual ways is:use bits field  to save space
* direct, easy to understand
* performance penalty
* few left to optimize,becuase this trick was used long ago

### explained in asm 
```c
struct bits
{
	unsigned short low : 2;
	unsigned short mid: 10;
	signed short : 4;
};
unsigned short i = 0x12;
int main()
{
	struct bits b = {-1};//line 10
	unsigned short xxx;
	xxx = i;
	b.mid = 33;
	xxx = b.mid;
	return 0;
}
/*
	mv         *dp(-2), a0h 	// 10 bits.c
	or         49152, a0h   	// 10
	mv         a0h, *dp(-2) 	// 10
	mv         *dp(-2), a0h 	// 10
	and        49167, a0h   	// 10
	mv         a0h, *dp(-2) 	// 10
	mv         #i, r0       	// 12
	mv         *r0, a0h     	// 12
	mv         a0h, *dp(-3) 	// 12
	mv         *dp(-2), a0h 	// 13
	and        49167, a0h   	// 13
	addh       528, a0      	// 13
	mv         a0h, *dp(-2) 	// 13
	mv         *dp(-2), a0h 	// 14
	exz        a0, 20, 9, a0h	// 14
	mv         a0h, *dp(-3) 	// 14
 
*/
```

<!-- pagebreak -->
## stack resue to reduce local variable space
* local variable allocate/release with stack frame
![stack_layout](/pics/stack_layout.PNG)

* only meaningful in critical function(deepest in stack)
* no tool to find to which func is critical
* but git reflog/reset  is helpful
* try & try again
find out that SESCHEDFO_main() is critical func in thread level, but to optimize,
mabye still need to find the critical path inside it.

### explained in asm
```c
#include <stdlib.h>
int s;
int main()
{
	{
	 int xxx = rand();//line 6
	 int yyy = rand();
	 int xxx_2 = rand();
	 int yyy_2 = rand();
	 int xxx_3 = rand();
	 int yyy_3 = rand();
	 
	 if (xxx>100)
		 s +=(xxx+yyy + xxx_2+yyy_2+xxx_3+yyy_3);
	}
	{
	 int xxx = rand();//line 17
	 int yyy = rand();
	 int xxx_2 = rand();
	 int yyy_2 = rand();
	 int xxx_3 = rand();
	 int yyy_3 = rand();
	 if (yyy>300)
		 s -=(xxx+yyy + xxx_2+yyy_2+xxx_3+yyy_3); //line 24
	}
	return s;
}

/*
	callr      #rand        	// 6 a.c (*), CurrBundle: 4, CriticalPath: 4
	mv         a0h, *dp(-1) 	// 6 (*), CurrBundle: 1, CriticalPath: 1, 1-byte Folded Spill
|	callr      #rand        	// 7 (*)
	.rule_off               	// 7
	copy       a0, a5       	// 7 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 8 (*)
	copy       a0, a6       	// 8 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 9 (*)
	copy       a0, a7       	// 9 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 10 (*)
	copy       a0, a4       	// 10 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 11 (*)
	.rule_on
	mv         *dp(-1), a1h 	// (*), 1-byte Folded Reload
	cmp        101, a1h     	// 13 (*), CurrBundle: 2, CriticalPath: 2
	if         .a1:ge       	// 14
|	addh       a1h, a5      	// 14 (*)
|	mv         #s, r0       	// 14
	if         .a1:ge       	// 14
|	addh       a5h, a6      	// 14 (*)
|	mv         *r0, a1h     	// 14
	addh       a6h, a7, .a1:ge	// 14 (*)
	addh       a7h, a4, .a1:ge	// 14 (*)
	addh       a4h, a0, .a1:ge	// 14 (*)
	addh       a1h, a0, .a1:ge	// 14 (*)
	mv         a0h, *r0, .a1:ge	// 14 (*), CurrBundle: 7, CriticalPath: 7
	callr      #rand        	// 17 (*), CurrBundle: 1, CriticalPath: 1
	mv         a0h, *dp(-1) 	// 17 (*), CurrBundle: 1, CriticalPath: 1, 1-byte Folded Spill
|	callr      #rand        	// 18 (*)
	.rule_off               	// 18
	copy       a0, a5       	// 18 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 19 (*)
	copy       a0, a6       	// 19 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 20 (*)
	copy       a0, a7       	// 20 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 21 (*)
	copy       a0, a4       	// 21 (*), CurrBundle: 1, CriticalPath: 1
|	callr      #rand        	// 22 (*)
	.rule_on                	// 23
	cmp        301, a5h     	// 23 (*)
	brr        #.LBB0_2, .a5:lt	// 23 (*), CurrBundle: 2, CriticalPath: 2

// Procedure estimates:
// Code size: 101 words (28 bits/instr)
// Instructions / cycles: 57 / 39
// Loop weighted cycles: 39
// Stack allocation: 16
*/
```

### solution
***original code***
```c
void SESCHEDFO_main()
{
  ULMACCE_LAPCSPLIB_traceS trace;
  ....
  while(expr)
  {
    assignSpectrumSucceeded =
        ULMACCE_SCHEDLIB_assignSpectrumToSe(
            &trace
        );
    //it is found that trace was not used inside this block at all 
    if (assignSpectrumSucceeded)
    {
      ULMACCE_PUSCHTPS_ginrWeighterDataS ginrWeightDataS;
	  ... 
    }    
  }
}
```
***after refactoring***
```c
void SESCHEDFO_main()
{

 while(expr)
  {
    BOOL isNs05seTypeDowngraded = FALSE;
    {
    ULMACCE_LAPCSPLIB_traceS trace;
	...
    assignSpectrumSucceeded =
        ULMACCE_SCHEDLIB_assignSpectrumToSe(
            &trace
        );
    }
    if (assignSpectrumSucceeded)
    {
        ULMACCE_PUSCHTPS_ginrWeighterDataS ginrWeightDataS;
    }    
  }
}
```
result:memory usage reduced by 26 words 
because trace's stack space was release and reused by ginrWeightDataS

### Pros & cons
* indirect & difficult to calculate
* need to find out the var can be reused 
* no tool for it

<!-- pagebreak -->
## summary
When developing new feature, we mainly optimize the memory usage via algorithm selection. but if code was optimized many rounds before, you can try stack reuse.




