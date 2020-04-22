# general saying
Only affect the varialbe/function's visibility.
so a static varible just the same as gloabal variable except it can't be reference in other moudle

# behind the compiler/linker
Each relocatable object module, m, has a symbol table that contains information about the symbols that are defined and referenced by m. In the context of a linker,
there are three different kinds of symbols:
*  Global symbols that are defined by module m and that can be referenced by other modules. Global linker symbols correspond to nonstatic C functions and
global variables that are defined without the C static attribute.
*  Global symbols that are referenced by module m but defined by some other module. Such symbols are called externals and correspond to C functions and
variables that are defined in other modules.
* Local symbolsthat are defined and referenced exclusively by module m. Some local linker symbols correspond to C functions and global variables that are
defined with the static attribute. These symbols are visible anywhere within module m, but cannot be referenced by other modules. The sections in an
object file and the name of the source file that corresponds to module m also get local symbols.
* no entry for the local variable, which was allocated in stack

* [static variable with initial value](static.c)

```
$ gcc -c static.c
$ objdump --syms static.o

0000000000000000 l     O .data	0000000000000004 i.1794
0000000000000004 l     O .data	0000000000000004 i.1797

```
可以看到代码中的两个i, 在 symbol table(s) 中为:local, an object (O),在.data section.


* [static variable without initial value](static_2.c)

```
$ gcc -c static_2.c
$ objdump --syms static_2.o
0000000000000000 l     O .bss	0000000000000004 i.1794
0000000000000004 l     O .bss	0000000000000004 i.1797

```
可以看到代码中的两个i, 在 symbol table(s) 中为:local, an object (O),在.bss section.