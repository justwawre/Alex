**DSP mem optimization**

*Xu YangChun Aug/21/2019*

# Problem
The DSP/thread run out of memory due to new feature. 

note:
* The thread deployed on DSPs via configuration
* several threads share the DSP in 1 TTI.

# Analysis
The probllem is caused by that an new U16 field added to the strcuture,  so more space is needed for the array. As illustrated below.

```c
/* global variables */
typedef struct _SeDataS
{
	U16 abc;
	U16 def; //added in the project
} _SeDataS;

_SeDataS _SchedData[MAX_];


void _start()//entry point of the thread
{
  _init();
  func1();
  func2();
  _main();
  funcn();
}
```  
note:
* above code just showing the overview of real code

Just like Linux, the DSP's memory layout can be classified as:
* data/bss
* stack
* heap

but the heap is not supported in this DSP role( GSP can allocate but can't release it) , so the memory optimization is limited to  
* stack:  where the local variable reside 
* data/bss: where global variable reside

<!-- pagebreak -->
# reduce global variables' space via bits field
The usual way is:changing the normal field in struct to bits field, shown as below example 

* [bits.c](intel/bits.c)
* [its asm code](intel/bits.s)

It is easy to understand, but 
* involve several files using the data structure, and
* may need to resolve "address of bits fields" error. and
* it has performance penalty. as below asm code show that it will intro extra instructions.

as 
```c
struct bits
{
	unsigned int low : 2;
	unsigned int mid : 10;
	unsigned int high : 20;
};
b.mid  = 33;
```
was compiled to
```asm
movzx	eax, WORD PTR -8[rbp]
and	ax, -4093  //0XF003   clear bit 2~11
or	al, -124   //256-124 = 132 = 33<<2
mov	WORD PTR -8[rbp], ax
```

* the biggest problem is, the structure _SeDataS and other were compacted many rounds, so no space left.


# reduce local variables' space via stack space reuse
![stack_layout](stack_layout.png)

## via splitting function
As illustrated above,the local variables are allocated inside 1 stack frame. When the stack frame pop out, its space will be reused by the next stack frame pushed. So **dividing 1 function & it local variables into 2**  cause stack reuse and save space. But this way will cause lots code change, not as elegant as I desired.

## via adding code bock
According C language:
> Memory for automatic variables is allocated when the code block is entered and freed upon exit. The scope of these variables is local to the block in which > they are declared, as well as any nested blocks.

So moving a variable in outer block into a inner block, will lead its space to **be released earlier** and be reused by next blocak at the same level.

## test

The test was under flacc compiler used by the product env.

* [orginal](flacc/stack_not_reuse.c) 
* [new one: add a code block, and move the varible into it](flacc/stack_reuse.c)

Those 2 files is the same in functional, but the new one can save some space, as checking the [asm file](flacc/stack_reuse.s)

after stack reuse, Stack allocation: 16 ;if not, Stack allocation shall be 6 * 2 * 2 = 24 words;so 8 words were saved.

## solution

Since the legacy code not written according to C99 style, so the local variables are declared at the begining of the function e.g. _main(), but its lifetime  is usually as log as the function. So we can add code block, move the varialbe into the new code block, then direct the compiler to reuse its stack space.

***original code***
```c
void _main()
{
  _traceS trace;
  while(expr)
  {
    Succeeded =
        _assignSpectrumToSe(
            &trace
        );
    if (Succeeded) //var trace not used by this block 
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
    {/adding 1 stack framed via the {}
    _traceS trace;
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

result reported by build system: memory usage reduced by **26** words

## The difficulty of this solution is:
* either ***splitting function*** or ***adding code block*** is only meaningful in the ***CriticalPath***
* how many space can be save is difficult to calculate
* no tool to find the CriticalPath

note:
Here I use the CriticalPath to describe the deepest call stack.Last sprint, I used git reflog/reset several rounds to find out the CriticalPath : _main().

# Anonymous union ?
Many fields actually are not used at the same time,e.g. at the firt half time ***abc*** is used, the later ***def*** is used. so they can share space via union. but if using named union, it will require lots code changes, the anonymous union is a kind of elegant solution.

```c
typedef struct _SeDataS//abc,def was organized to a union
{
	union
	{
		U16 abc;
		U16 def;
	};
} _SeDataS;	

_SchedData[i].abc = xxx;//code needn no change
```
The ONLY problem is that the current compiler don't support anonymous union.

# Supplements
Here only list some tricks I use in last sprint,the topic about algorithm change is not covered, an example of removing the big auxiliary Space in the merge sort functionwill discuss next time .



