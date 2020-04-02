## dsp mem optimization
*Xu YangChun Aug/21/2019*

### Problem
The DSP/thread run out of memory due to new feature<br>
to be precise, the thread's memory usage is over limit set before.<br>

### analysis
The cause is that an new U16 field was added to the strcuture, <br> 
then more space is needed for the array which allocated statically.<br> 
the code just for illustration <br>

```c
/* global variables */
var1;
var2;
/*
typedef struct _SeDataS
{
	U16 abc;
	U16 def; //added in the project
} _SeDataS;
*/	
_SeDataS _SchedData[MAX_];
....
varm;

void _start()//entry point of the thread
{
  _init();
  func1();
  func2();
  ....  
  _main();
  ....
  funcn();
}
```  

since the dynamic allocated memory (heap ) is not supported in this dsp role, <br>
(can allocate but can't release) <br> 
so the memory optimization limited to satic allocated memory (stack) <br> 
including the local or global variable for this thread/dsp.<br> 

<!-- pagebreak -->
### reduce global variables' space via bits field
The usual way used by developers before: <br>
changing the normal field in struct to bits field. <br>
it is easy to understand, but involve several files, <br>
and need to resolve "address of bits fields" error. <br>
But there is few space left to optimize since the tricks was used many times before,<br>
and it has performance penalty. <br>

shown as an example <br>

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
```
its asm code show that it need extra instructions 
```asm
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
### reduce global variables' space via stack frame change 
![stack_layout](stack_layout.png)
As illustrated above,<br>
the local variables ared allocated/released inside the stack frame,<br>
so when compiler met a function or code block, stack frame added, space increaded <br>
when it met function return or end of code block, stack frome decreased, space decreased <br>
so if we tell can put two variables which are located different level of stack frome <br>
to stack frame of the the same level, <br>
 thne stack space can be reused,<br>

example below, aftr adding two sets of {},memory saved<br>

```c
#include <stdlib.h>
int s;
int main()
{
	{//code block added,stack framed added, then space saved
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
```
its asm code is:
```asm
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

```

### solution
***original code***
```c
void _main()
{
  _traceS trace;
  ....
  while(expr)
  {
    Succeeded =
        _assignSpectrumToSe(
            &trace
        );
    //it is found that trace was not used inside this block at all 
    if (Succeeded)
    {
      _ginrWeighterDataS ginrWeightDataS;
	  ... 
    }    
  }
}
```
***refactoring, just adding 1 set of {}***
```c
void SESCHEDFO_main()
{

 while(expr)
  {
    {/code block added,stack framed added, then space saved
    _traceS trace;
	...
    Succeeded =
        _assignSpectrumToSe(
            &trace
        );
    }
    if (Succeeded)
    {
        _ginrWeighterDataS ginrWeightDataS;
    }    
  }
}
```
result:memory usage reduced by 26 words 

The difficulty of this solution is:
* optimizaiotn is only meaningful in the CriticalPath
* how many space can be save is difficult to calculate
* no tool to find the CriticalPath
Last sprint, I used git reflog/reset several round to find out the CriticalPath <br>
 in thread level function: _main().

### looking forward: Anonymous union
many fieled actually are not used at the same time, <br>
e.g. the firt half time abc is used, the later def is used <br>
they can share space via union in theory<br>

```c
//abc,def was organized to a union
typedef struct _SeDataS
{
	union
	{
		U16 abc;
		U16 def;
	};
    .....
} _SeDataS;	
//code needn no change
_SchedData[i].abc = xxx;
```
If using the named union, it will require lots code changes.<br>
The problem  is that current compler don't support it, <br>
so it need wait for clang migration completion.<br>


### Supplements
Here only list some tricks I use in last sprint,<br>
the topic about algorithm change is not covered, <br>
an example of removing the big auxiliary Space in the merge sort function<br>
will discuss next time <br>



