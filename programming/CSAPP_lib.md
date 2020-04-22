# static lib

## build & link

[foo5](foo5.c) [bar4](bar4.c) [bar5](bar5.c)
```
$ gcc -c bar4.c bar5.c
$ ar rcs libbar.a bar4.o bar5.o
$ gcc foo5.c ./libbar.a 

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


# shared lib
Shared libraries are modern innovations that address the disadvantages of static libraries. A shared library is an object module that, at run time, can be
loaded at an arbitrary memory address and linked with a program in memory. This process is known as dynamic linking and is performed by a program called a
dynamic linker.

也就是把 Resolve References 这一步在runtime 才执行。

[foo5](foo5.c) [bar4](bar4.c) [bar5](bar5.c)

```
$ gcc -shared -fPIC -o libbar.so bar4.c bar5.c
$ gcc -g foo5.c  ./libbar.so

```
The -fPIC flag directs the compiler to generate position-independent code. The -shared flag directs the linker to create a shared object file.


Shared libraries are “shared” in two different ways. 
* First, in any given file system, there is exactly one .so file for a particular library. The code and data in this .so file are shared by all of the executable object files that reference the library, as opposed to the contents of static libraries, which are copied and embedded in the executables that reference them. 
* Second, a single copy of the .text section of a shared library in memory can be shared by different running processes. 


none of the code or data sections from libbar.so are actually copied into the executable a.out when linking. Instead, the linker copies some relocation and symbol table information that will allow references to code and data in libbar.so to be resolved at run time. 感觉这在Nokia的DMX/SDL 系统中，就是共享module 的Start有一张跳转表，每一个entry 是 一 jmp 语句， jmp 到module 中的某个个procedure。 这样其他process 要调用module 中某个procedure, 只需要 call  start+offset 即可。

```
$ objdump -s a.out

a.out:     file format elf64-x86-64

Contents of section .interp:
 0238 2f6c6962 36342f6c 642d6c69 6e75782d  /lib64/ld-linux-
 0248 7838362d 36342e73 6f2e3200           x86-64.so.2.    
```
.interp section, which contains the path name of the dynamic linker

## 对应命令
```
$ gcc -shared -fPIC -o libbar.so bar4.c bar5.c
$ gcc -g foo5.c  ./libbar.so
$ ldd a.out
	linux-vdso.so.1 (0x00007ffd537d6000)
	./libbar.so (0x00007fdd9a2ea000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fdd99ef9000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fdd9a6ee000)

$ objdump -s a.out

a.out:     file format elf64-x86-64

Contents of section .plt:
 05f0 ff35ca09 2000ff25 cc092000 0f1f4000  .5.. ..%.. ...@.
 0600 ff25ca09 20006800 000000e9 e0ffffff  .%.. .h.........
Contents of section .plt.got:
 0610 ff25e209 20006690                    .%.. .f.        
Contents of section .text:


Contents of section .got:
 200fb8 b80d2000 00000000 00000000 00000000  .. .............
 200fc8 00000000 00000000 06060000 00000000  ................
 200fd8 00000000 00000000 00000000 00000000  ................
 200fe8 00000000 00000000 00000000 00000000  ................
 200ff8 00000000 00000000                    ........        
Contents of section .data:


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


## Position-Independent Code (PIC)
原理

the compiler creates a table called the global offset table (GOT) at the beginning of the data segment. The GOT contains an entry for each global data object that is referenced by the object module. The compiler also generates a relocation record for each entry in the GOT. At load time, the dynamic linker relocates each entry in the GOT so that it contains the appropriate absolute address. Each object module that references global data has its own
GOT.

At run time, each global variable is referenced indirectly through the GOT。

Lazy binding is implemented with a compact yet somewhat complex interaction between two data structures: the GOT and the procedure linkage table (PLT).
If an object module calls any functions that are defined in shared libraries, then it has its own GOT and PLT. The GOT is part of the .data section. The PLT is part of the .text section.


[foo6](foo6.c) [bar4](bar4.c) [bar5](bar5.c)

```
$  gcc -shared -fPIC -o libbar.so bar4.c bar5.c
$  gcc -g  -rdynamic foo6.c -ldl
$ objdump -s a.out

a.out:     file format elf64-x86-64

Contents of section .interp:
 0238 2f6c6962 36342f6c 642d6c69 6e75782d  /lib64/ld-linux-
 0248 7838362d 36342e73 6f2e3200           x86-64.so.2.    

Contents of section .init:
 07d0 4883ec08 488b050d 08200048 85c07402  H...H.... .H..t.
 07e0 ffd04883 c408c3                      ..H....         
Contents of section .plt:
 07f0 ff35b207 2000ff25 b4072000 0f1f4000  .5.. ..%.. ...@.
 0800 ff25b207 20006800 000000e9 e0ffffff  .%.. .h.........
 0810 ff25aa07 20006801 000000e9 d0ffffff  .%.. .h.........
 0820 ff25a207 20006802 000000e9 c0ffffff  .%.. .h.........
 0830 ff259a07 20006803 000000e9 b0ffffff  .%.. .h.........
Contents of section .plt.got:
 0840 ff25b207 20006690                    .%.. .f.        
Contents of section .text:


Contents of section .got:
 200fa0 a00d2000 00000000 00000000 00000000  .. .............
 200fb0 00000000 00000000 06080000 00000000  ................
 200fc0 16080000 00000000 26080000 00000000  ........&.......
 200fd0 36080000 00000000 00000000 00000000  6...............
 200fe0 00000000 00000000 00000000 00000000  ................
 200ff0 00000000 00000000 00000000 00000000  ................
Contents of section .data:

```
Each procedure that is defined in a shared object and called by [foo6](foo6.c)  gets an entry in the GOT, starting with entry GOT[3].


The PLT is an array of 16-byte entries. The first entry, PLT[0], is a special entry that jumps into the dynamic linker. Each called procedure has an entry in the PLT, starting at PLT[1]

```
$ objdump -d a.out

a.out:     file format elf64-x86-64


Disassembly of section .plt:

00000000000007f0 <.plt>:
 7f0:	ff 35 b2 07 20 00    	pushq  0x2007b2(%rip)        # 200fa8 <_GLOBAL_OFFSET_TABLE_+0x8>
 7f6:	ff 25 b4 07 20 00    	jmpq   *0x2007b4(%rip)        # 200fb0 <_GLOBAL_OFFSET_TABLE_+0x10>
 7fc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000000800 <dlopen@plt>:
 800:	ff 25 b2 07 20 00    	jmpq   *0x2007b2(%rip)        # 200fb8 <dlopen@GLIBC_2.2.5>
 806:	68 00 00 00 00       	pushq  $0x0
 80b:	e9 e0 ff ff ff       	jmpq   7f0 <.plt>

0000000000000810 <dlclose@plt>:
 810:	ff 25 aa 07 20 00    	jmpq   *0x2007aa(%rip)        # 200fc0 <dlclose@GLIBC_2.2.5>
 816:	68 01 00 00 00       	pushq  $0x1
 81b:	e9 d0 ff ff ff       	jmpq   7f0 <.plt>

0000000000000820 <dlsym@plt>:
 820:	ff 25 a2 07 20 00    	jmpq   *0x2007a2(%rip)        # 200fc8 <dlsym@GLIBC_2.2.5>
 826:	68 02 00 00 00       	pushq  $0x2
 82b:	e9 c0 ff ff ff       	jmpq   7f0 <.plt>

0000000000000830 <dlerror@plt>:
 830:	ff 25 9a 07 20 00    	jmpq   *0x20079a(%rip)        # 200fd0 <dlerror@GLIBC_2.2.5>
 836:	68 03 00 00 00       	pushq  $0x3
 83b:	e9 b0 ff ff ff       	jmpq   7f0 <.plt>






000000000000095a <main>:
 95a:	55                   	push   %rbp
 95b:	48 89 e5             	mov    %rsp,%rbp
 95e:	48 83 ec 10          	sub    $0x10,%rsp
 962:	c7 05 b4 06 20 00 01 	movl   $0x1,0x2006b4(%rip)        # 201020 <i>
 969:	00 00 00 
 96c:	be 01 00 00 00       	mov    $0x1,%esi
 971:	48 8d 3d fc 00 00 00 	lea    0xfc(%rip),%rdi        # a74 <_IO_stdin_used+0x4>
 978:	e8 83 fe ff ff       	callq  800 <dlopen@plt>


```
看来现在的汇编还是非常清晰的， callq  800 <dlopen@plt>  已经表到了，一种call <跳转表某项> 的做法。

```

$ ldd a.out
	linux-vdso.so.1 (0x00007ffd1b322000)
	libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f5953515000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f5953124000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f595391b000)
```


## Loading and Linking Shared Libraries from Applications
不需要在compiliation 过程解决r symbol resolution，load 过程也是app 自己调用了。

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
令人惊讶的是，
[strong & weak symbol during linking](strong_weak.md)
在手动动态加载的情况下还成立。



# choice

Linking can be performed at compile time by static linkers, and at load time and run time by dynamic linkers. Linkers manipulate binary files called object
files, which come in three different forms: relocatable, executable, and shared. Relocatable object files are combined by static linkers into an executable object file that can be loaded into memory and executed. Shared object files (shared libraries) are linked and loaded by dynamic linkers at run time, either implicitly when the calling program is loaded and begins executing, or on demand, when the program calls functions from the dlopen library.
The two main tasks of linkers are symbol resolution, where each global symbol in an object file is bound to a unique definition, and relocation, where the ultimate memory address for each symbol is determined and where references to those objects are modified


理论上用shared lib 比 shared lib 好， 实际上shared lib 容易带来 lib 版本不兼容问题。记得最早碰到这问题是，一台开发Sun E450 上通过的程序，在部署的Sun E450 就是出问题，root cause只是 shared lib 小版本不兼容。
