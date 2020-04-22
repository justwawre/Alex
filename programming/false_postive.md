a false postive issue and its resolution


## a false warning generated as below

> error: Value stored to 'txModeGroup' during its initialization is never read 

but actaully this variable is used about 200 lines of code later.

## known issue?  
checking from  http://clang-analyzer.llvm.org/, 

it is not known false postive, maybe configuration prbolem?

## resultion
the warning program was written in old old style C, so where the variable declared is far away from where it is used.

changing the old style C code to c99 style, declare the variable near where it was used. Then the warnining disappear.

## further optimization 
Actaully the array is of constant values, since the DSP is short of RAM, so declared it as:
```c
const U16 txModeGroup[] ={....};
```
to move it to 
* .rodata section if running on PC or 
* code section if running on DSP
