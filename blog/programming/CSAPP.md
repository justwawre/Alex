从第一版看到第三版，他这本书是非常全，对应国内多门课，如计算机原理/计算机组成。但真正讲的好的没有几章。

# chp 7: linking

Linux下ELF文件类型分为以下几种：

* 可重定位文件，例如SimpleSection.o；
* 可执行文件，例如/bin/bash；
* 共享目标文件，例如/lib/libc.so。
* Core dump文件

ELF文件中典型的section如下：
* .text: 已编译程序的二进制代码
* .rodata: 只读数据段，比如常量
* .data: 已初始化的全局变量和静态变量
* .bss: 未初始化的全局变量和静态变量，所有被初始化成0的全局变量和静态变量
* .sysmtab: 符号表，它存放了程序中定义和引用的函数和全局变量的信息
* .debug: 调试符号表，它需要以'-g'选项编译才能得到，里面保存了程序中定义的局部变量和类型定义，程序中定义和引用的全局变量，以及原始的C文件
* .line: 原始的C文件行号和.text节中机器指令之间的映射
* .strtab: 字符串表，内容包括.symtab和.debug节中的符号表

特殊的，
1）对于可重定位的文件，由于在编译时，并不能确定它引用的外部函数和变量的地址信息，因此，编译器在生成目标文件时，增加了两个section：
* .rel.text 保存了程序中引用的外部函数的重定位信息，这些信息用于在链接时重定位其对应的符号。
* .rel.data 保存了被模块引用或定义的所有全局变量的重定位信息，这些信息用于在链接时重定位其对应的全局变量。

e.g.

当g.o调用一个外部的函数puts()时，那么编译器会生成一条call指令，指令的操作数是一个占位符，而与此同时生成一条重定位条目（relocation entry）放在.rel.text section中，类似的，当模块调用一个外部变量时，编译器会生成一条重定位条目放在.rel.data section中。


2）对于可执行文件，由于它已经全部完成了重定位工作，可以直接加载到内存中执行，所以它不存在.rel.text和.rel.data这两个section。但是，它增加了一个section：
* .init: 这个section里面保存了程序运行前的初始化代码

用来检查的命令
* Display the relocation entries in the file
```
objdump -r g.o
```
* Display the dynamic relocation entries in the file
```
objdump -R a.out

```
3) .rela.eh_frame：

这个section同.rel.text一样属于重定位信息的section，只不过它包含的是eh_frame的重定位信息 (When using languages that support exceptions, such as C++, additional information must be provided to the runtime environment that describes the call frames that much be unwound during the processing of an exception. This information is contained in the special sections.eh_frameand.eh_framehdr.)

4) .dynsym: 这个section保存与动态链接相关的导入导出符号，不包括模块内部的符号。而.symtab则保存所有符号，包括.dynsym中的符号。

5) .init和.init_array: 这个section中保存了该可执行程序main函数执行之前的初始化代码， 比如设置环境变量，给main函数传递参数等

6) .fini和.fini_array: 这个section中保存了该可执行程序main函数正常退出之后执行的代码。

7) .dynamic: 这个section里保存了动态链接器所需要的基本信息，比如依赖哪些共享对象、动态链接符号表的位置、动态链接重定位表的位置、共享对象初始化代码的地址等。它是由是由Elfxx_Dyn（Elf32_Dyn或者Elf64_Dyn）组成的数组。Elfxx_Dyn结构由一个类型值加上一个附加的数值或指针，对于不同的类型，后面附加的数值或者指针有着不同的含义。

# chp 8 virtual memory
## VA与virtual address
With virtual addressing, the CPU accesses main memory by generating a virtual address (VA), which is converted to the appropriate physical address before being sent to main memory. The task of converting a virtual address to a physical one is known as address translation. Like exception handling, address translation requires close cooperation between the CPU hardware and the operating system. Dedicated hardware on the CPU chip called the memory management unit(MMU)translates virtual addresses on the fly, using a lookup table (TLB????) stored in main memory whose contents are managed by the operating system.

## virtual memory
Conceptually, a virtual memory is organized as an array of N contiguous byte-sized cells stored on disk. Each byte has a unique virtual address that serves as an index into the array. The contents of the array on disk are cached in main memory. As with any other cache in the memory hierarchy, the data on disk (the lower level) is partitioned into blocks that serve as the transfer units between the disk and the main memory (the upper level). VM systems handle this by partitioning the virtual page is P = 2^p bytes in size. Similarly, physical memory is partitioned into physical pages (PPs), also P bytes in size. (Physical pages are also referred to as page frames.)

## handle of page fault
![tbd](CSAPP_pagefault.png)

## allocate a virtual page
![tbd](CSAPP_newpage.png)

## address translation

![tbd](CSAPP_pagetable.png)


### Speeding Up Address Translation with a TLB
As we have seen, every time the CPU generates a virtual address, the MMU must refer to a PTE in order to translate the virtual address into a physical address. In the worst case, this requires an additional fetch from memory, at a cost of tens to hundreds of cycles. If the PTE happens to be cached in L1, then the cost goes down to a handful of cycles. However, many systems try to eliminate even this cost by including a small cache of PTEs in the MMU called a translation lookaside buffer(TLB).

A TLB is a small, virtually addressed cache where each line holds a block consisting of a single PTE.





