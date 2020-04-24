# static linking

## build & link

[foo5](foo5.c) [bar4](bar4.c) [bar5](bar5.c)
```
$ gcc -c bar4.c bar5.c
$ ar rcs libbar.a bar4.o bar5.o
$ gcc foo5.c ./libbar.a 

$ objdump -s a.out

Contents of section .plt:
 04d0 ff35f20a 2000ff25 f40a2000 0f1f4000  .5.. ..%.. ...@.
Contents of section .plt.got:
 04e0 ff25120b 20006690                    .%.. .f.        
Contents of section .text:
 04f0 31ed4989 d15e4889 e24883e4 f050544c  1.I..^H..H...PTL

Contents of section .got:
 200fc0 000e2000 00000000 00000000 00000000  .. .............
 200fd0 00000000 00000000 00000000 00000000  ................
 200fe0 00000000 00000000 00000000 00000000  ................
 200ff0 00000000 00000000 00000000 00000000  ................
Contents of section .data:
 201000 00000000 00000000 08102000 00000000  .......... .....


$ objdump -d a.out

Disassembly of section .plt:

00000000000004d0 <.plt>:
 4d0:	ff 35 f2 0a 20 00    	pushq  0x200af2(%rip)        # 200fc8 <_GLOBAL_OFFSET_TABLE_+0x8>
 4d6:	ff 25 f4 0a 20 00    	jmpq   *0x200af4(%rip)        # 200fd0 <_GLOBAL_OFFSET_TABLE_+0x10>
 4dc:	0f 1f 40 00          	nopl   0x0(%rax)

Disassembly of section .plt.got:

00000000000004e0 <__cxa_finalize@plt>:

00000000000005fa <main>:
 5fa:	55                   	push   %rbp
 5fb:	48 89 e5             	mov    %rsp,%rbp
 5fe:	c7 05 0c 0a 20 00 01 	movl   $0x1,0x200a0c(%rip)        # 201014 <i>
 605:	00 00 00 
 608:	e8 08 00 00 00       	callq  615 <bar>
 60d:	8b 05 01 0a 20 00    	mov    0x200a01(%rip),%eax        # 201014 <i>
 613:	5d                   	pop    %rbp
 614:	c3                   	retq   

0000000000000615 <bar>:
 615:	55                   	push   %rbp
 616:	48 89 e5             	mov    %rsp,%rbp
 619:	c7 05 f1 09 20 00 03 	movl   $0x3,0x2009f1(%rip)        # 201014 <i>
 620:	00 00 00 
 623:	90                   	nop
 624:	5d                   	pop    %rbp
 625:	c3                   	retq   
 626:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 62d:	00 00 00 

```
ar 命令已经跟 tar 命令类似，只是打包(archive)而已。


## How Linkers Use Static Libraries to Resolve References

During this scan, the linker maintains a set E of relocatable object files that will be merged to form the
executable, a set U of unresolved symbols (i.e., symbols referred to, but not yet defined), and a set D of symbols that have been defined in previous input files. Initially, E, U, and D are empty

* For each input file f on the command line, the linker determines if f is an object file or an archive. If f is an object file, the linker adds f to E, updates U and D to reflect the symbol definitions and references in f , and proceeds to the next input file.

* If f is an archive, the linker attempts to match the unresolved symbols in U against the symbols defined by the members of the archive. If some archive
member, m, defines a symbol that resolves a reference in U, then m is added to E, and the linker updates U and D to reflect the symbol definitions and
references in m. This process iterates over the member object files in the archive until a fixed point is reached where U and D no longer change. At
this point, any member object files not contained in E are simply discarded and the linker proceeds to the next input file.

* If U is nonempty when the linker finishes scanning the input files on the command line, it prints an error and terminates. Otherwise, it merges and
relocates the object files in E to build the output executable file.

"then m is added to E", "the linker adds f to E,“，也就是说加到.out 文件中的，是整个.o文件，无论是否在archive( static lib)中。

## 对应命令
ld


# dynamic linking
## Shared libraries 
are modern innovations that address the disadvantages of static libraries. A shared library is an object module that, at run time, can be loaded at an arbitrary memory address and linked with a program in memory. This process is known as dynamic linking and is performed by a program called a dynamic linker.

```
$ gcc -shared -fPIC -o libbar.so bar4.c bar5.c

```
## PIC object file

The -fPIC flag directs the compiler to generate position-independent code. The -shared flag directs the linker to create a shared object file. 感觉这套路与MS-DOS中的com 文件类型类似，在一个段内，不涉及段寄存器； 不同的是com 文件因此加载后不能超过64k,因为16位cpu，offset最大也就64k. 所以.so实际也有这限制，不过32bit/64bit cpu时代而已。

note: COM文件中没有附带任何支持性数据，仅包含可执行代码。文件头即为第一句执行指令。没有重定位的信息，这样代码中不能有跨内存段(segment)操作数据的指令，因此代码与数据只能限制在同一个64KB的内存段中。

如果不加-fPIC,则加载.so文件的代码段时,代码段引用的数据对象需要重定位, 重定位会修改代码段的内容,这就造成每个使用这个.so文件代码段的进程在内核里都会生成这个.so文件代码段的copy。

none of the code or data sections from libbar.so are actually copied into the executable a.out when linking. Instead, the linker copies some relocation and symbol table information that will allow references to code and data in libbar.so to be resolved at run time. 

alex: 静态链接是把.out 文件的 symbole reference 全部 resolve 了。 而动态链接由于 .so的位置是不定的，所以只能在通过
* 创建 .got .plt 表， 
* 链接时 .out 文件中对.so文件的引用就在这两个表中增加一项，让.out 中 的调用resolve 为对 .got .plt 表的引用
* 运行时， loader 根据 .so 的加载情况，修改 .got .plt 表。

印象中，这在Nokia的DMX/SDL 系统中，也是使用共享module。它的方式是
* 共享module 的起始位置有一张跳转表，每一个entry 是 一 jmp 语句， 需要程序员手动填写. near jmp 到module 中的某个个procedure。
* 这样其他process 要调用module 中某个procedure, 只需要 far call  module 段地址 +offset 即可。
* 这样也可以实现 共享module 独立与调用process的独立开发，减少依赖。


the compiler creates a table called the global offset table (GOT) at the beginning of the data segment. The GOT contains an entry for each global data object that is referenced by the object module. The compiler also generates a relocation record for each entry in the GOT. At load time, the dynamic linker relocates each entry in the GOT so that it contains the appropriate absolute address. Each object module that references global data has its own GOT.

* Each procedure that is defined in a shared object and called by [foo5.c](foo5.c)  gets an entry in the GOT, starting with entry GOT[3].
* The PLT is an array of 16-byte entries. The first entry, PLT[0], is a special entry that jumps into the dynamic linker. Each called procedure has an entry in the PLT, starting at PLT[1]
* At run time, each global variable is referenced indirectly through the GOT。

Lazy binding is implemented with a compact yet somewhat complex interaction between two data structures: the GOT and the procedure linkage table (PLT).
If an object module calls any functions that are defined in shared libraries, then it has its own GOT and PLT. The GOT is part of the .data section. The PLT is part of the .text section.

## check with the same files

[foo5](foo5.c) [bar4](bar4.c) [bar5](bar5.c)

```
$ gcc -shared -fPIC -o libbar.so bar4.c bar5.c
$ gcc -g foo5.c  ./libbar.so
$ ldd a.out
	linux-vdso.so.1 (0x00007ffc575ff000)
	./libbar.so (0x00007f4c2e5c5000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f4c2e1d4000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f4c2e9c9000)

$objdump -s a.out

a.out:     file format elf64-x86-64

Contents of section .interp:
 0238 2f6c6962 36342f6c 642d6c69 6e75782d  /lib64/ld-linux-
 0248 7838362d 36342e73 6f2e3200           x86-64.so.2.    

Contents of section .plt:
 05f0 ff35ca09 2000ff25 cc092000 0f1f4000  .5.. ..%.. ...@.
 0600 ff25ca09 20006800 000000e9 e0ffffff  .%.. .h.........
Contents of section .plt.got:
 0610 ff25e209 20006690                    .%.. .f.        
Contents of section .text:
 0620 31ed4989 d15e4889 e24883e4 f050544c  1.I..^H..H...PTL

Contents of section .got:
 200fb8 b80d2000 00000000 00000000 00000000  .. .............
 200fc8 00000000 00000000 06060000 00000000  ................
 200fd8 00000000 00000000 00000000 00000000  ................
 200fe8 00000000 00000000 00000000 00000000  ................
 200ff8 00000000 00000000                    ........        
Contents of section .data:
 201000 00000000 00000000 08102000 00000000  .......... .....

$ objdump -d a.out

Disassembly of section .plt:

00000000000005f0 <.plt>:
 5f0:	ff 35 ca 09 20 00    	pushq  0x2009ca(%rip)        # 200fc0 <_GLOBAL_OFFSET_TABLE_+0x8>
 5f6:	ff 25 cc 09 20 00    	jmpq   *0x2009cc(%rip)        # 200fc8 <_GLOBAL_OFFSET_TABLE_+0x10>
 5fc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000000600 <bar@plt>:
 600:	ff 25 ca 09 20 00    	jmpq   *0x2009ca(%rip)        # 200fd0 <bar>
 606:	68 00 00 00 00       	pushq  $0x0
 60b:	e9 e0 ff ff ff       	jmpq   5f0 <.plt>

Disassembly of section .plt.got:

0000000000000610 <__cxa_finalize@plt>:
 610:	ff 25 e2 09 20 00    	jmpq   *0x2009e2(%rip)        # 200ff8 <__cxa_finalize@GLIBC_2.2.5>
 616:	66 90                	xchg   %ax,%ax

000000000000072a <main>:
 72a:	55                   	push   %rbp
 72b:	48 89 e5             	mov    %rsp,%rbp
 72e:	c7 05 dc 08 20 00 01 	movl   $0x1,0x2008dc(%rip)        # 201014 <i>
 735:	00 00 00 
 738:	e8 c3 fe ff ff       	callq  600 <bar@plt>


```
其中
* .interp section  which contains the path name of the dynamic linker
* .plt section 包含 <bar@plt>
* section .plt.got 
* section .got
* 代码中，函数调用link 后是 callq  600 <bar@plt>。

.so 文件

```
$ gcc -shared -fPIC -o libbar.so bar4.c bar5.c
$ objdump -d libbar.so 
libbar.so:     file format elf64-x86-64


Disassembly of section .init:

00000000000004b8 <_init>:
 4b8:	48 83 ec 08          	sub    $0x8,%rsp
 4bc:	48 8b 05 35 0b 20 00 	mov    0x200b35(%rip),%rax        # 200ff8 <__gmon_start__>
 4c3:	48 85 c0             	test   %rax,%rax
 4c6:	74 02                	je     4ca <_init+0x12>
 4c8:	ff d0                	callq  *%rax
 4ca:	48 83 c4 08          	add    $0x8,%rsp
 4ce:	c3                   	retq   

Disassembly of section .plt:

00000000000004d0 <.plt>:
 4d0:	ff 35 32 0b 20 00    	pushq  0x200b32(%rip)        # 201008 <_GLOBAL_OFFSET_TABLE_+0x8>
 4d6:	ff 25 34 0b 20 00    	jmpq   *0x200b34(%rip)        # 201010 <_GLOBAL_OFFSET_TABLE_+0x10>
 4dc:	0f 1f 40 00          	nopl   0x0(%rax)

Disassembly of section .plt.got:

00000000000004e0 <__cxa_finalize@plt>:
 4e0:	ff 25 f2 0a 20 00    	jmpq   *0x200af2(%rip)        # 200fd8 <__cxa_finalize>
 4e6:	66 90                	xchg   %ax,%ax


$ objdump -s libbar.so 

Contents of section .got:
 200fd8 00000000 00000000 00000000 00000000  ................
 200fe8 00000000 00000000 00000000 00000000  ................
 200ff8 00000000 00000000                    ........        
Contents of section .got.plt:
 201000 880e2000 00000000 00000000 00000000  .. .............
 201010 00000000 00000000    
```
可以看到.so文件与可执行文件非常类似，有 .init .got .plt。 但是 .got内容是空的。


# static/dynamic linking 的区别
主要在于 access global data, jump label 的不同。

比如一条 access global data 的指令，
* non-PIC 的形式是：
```
ld r3, var1
```
* PIC 的形式则是：
```
ld r3, var1-offset@GOT
``` 
意思是从 GOT 表的 index 为 var1-offset 的地方处，指示的地址处装载一个值,即var1-offset@GOT处的4个 byte。 其实就是 var1 的地址。这个地址只有在运行的时候才知道，是由 dynamic-loader(ld-linux.so) 填进去的。

再比如 jump label 指令
* non-PIC 的形式是： 
```
callq  615 <bar>
```
* PIC 的形式则是：
```
callq  callq  600 <bar@plt>
```
， 通过它二次跳转。



# Loading and Linking Shared Libraries from Applications

[foo6](foo6.c) [bar4](bar4.c) [bar5](bar5.c)

```
$  gcc -shared -fPIC -o libbar.so bar4.c bar5.c
$  gcc -g  -rdynamic foo6.c -ldl
$ gdb a.out
(gdb) l
1	#include <dlfcn.h>
2	int i;
3	void (*bar)(void);
4	int main()
5	{
6	    i = 1;
7	    void *handle = dlopen("./libbar.so", RTLD_LAZY);
8	    if (!handle)
9	    {
10	        return -1;
(gdb) br 7
Breakpoint 1 at 0x96c: file foo6.c, line 7.
(gdb) r

Breakpoint 1, main () at foo6.c:7
7	    void *handle = dlopen("./libbar.so", RTLD_LAZY);
(gdb) n
8	    if (!handle)
(gdb) n
12	    bar = dlsym(handle, "bar");
(gdb) n
13	    if (dlerror())
(gdb) n
18	    bar();
(gdb) n
19	    if (dlclose(handle) < 0)
(gdb) n
23	    return 0;
(gdb) print i
$1 = 3
(gdb) 

```
-rdynamic 并不是必需的
Pass the flag ‘-export-dynamic’ to the ELF linker, on targets that support
it. This instructs the linker to add all symbols, not only used ones, to the
dynamic symbol table. This option is needed for some uses of dlopen or to
allow obtaining backtraces from within a program.

```
$  gcc -shared -fPIC -o libbar.so bar4.c bar5.c
$  gcc -g  foo6.c -ldl
$  gdb a.out

(gdb) br 23
Breakpoint 1 at 0x7ca: file foo6.c, line 23.
(gdb) r
Starting program: /home/alex/base/Alex/CSAPP3/a.out 

Breakpoint 1, main () at foo6.c:23
23	    return 0;
(gdb) print i
$1 = 1
(gdb) 
```
i值的变化，颇有有趣的现象，也许它反映的就是体现了 [strong & weak symbol during linking](strong_weak.md) 的rule 3.

https://stackoverflow.com/questions/36692315/what-exactly-does-rdynamic-do-and-when-exactly-is-it-needed

如果按该文的解释，用上 -rdynamic 是好习惯。


# choice

Linking can be performed at compile time by static linkers, and at load time and run time by dynamic linkers. Linkers manipulate binary files called object
files, which come in three different forms: relocatable, executable, and shared. Relocatable object files are combined by static linkers into an executable object file that can be loaded into memory and executed. Shared object files (shared libraries) are linked and loaded by dynamic linkers at run time, either implicitly when the calling program is loaded and begins executing, or on demand, when the program calls functions from the dlopen library.
The two main tasks of linkers are symbol resolution, where each global symbol in an object file is bound to a unique definition, and relocation, where the ultimate memory address for each symbol is determined and where references to those objects are modified


理论上用shared lib 比 shared lib 好， 实际上shared lib 容易带来 lib 版本不兼容问题。记得最早碰到这问题是，一台开发Sun E450 上通过的程序，在部署的Sun E450 就是出问题，root cause只是 shared lib 小版本不兼容。
