
At compile time, the compiler exports each global symbol to the assembler as either strong or weak, and the assembler encodes this information implicitly in
the symbol table of the relocatable object file. Functions and initialized global variables get strong symbols. Uninitialized global variables get weak symbols.


Given this notion of strong and weak symbols, Unix linkers use the following rules for dealing with multiply defined symbols:

* Rule 1: Multiple strong symbols are not allowed.

[foo3.c](foo3.c) [bar1.c](bar1.c)

```
$ gcc -g foo3.c bar1.c

/tmp/ccr8Q0wL.o:(.data+0x0): multiple definition of `i'
/tmp/ccE6qJe9.o:(.data+0x0): first defined here
collect2: error: ld returned 1 exit status

```

* Rule 2: Given a strong symbol and multiple weak symbols, choose the strong symbol.

example:  uninitialized in one module, then the linker will quietly choose the strong symbol defined in the other.

[foo3.c](foo3.c) [bar3.c](bar3.c)

```
$ gcc -g foo3.c bar3.c
$ gdb a.out

(gdb) l
1	int i = 1;
2	void bar(void);
3	int main()
4	{
5	    bar();
6	    return i;
7	}(gdb) break 6
Breakpoint 1 at 0x603: file foo3.c, line 6.
(gdb) r
Starting program: /home/alex/base/Alex/blog/programming/a.out 

Breakpoint 1, main () at foo3.c:6
6	    return i;
(gdb) print i
$1 = 3
(gdb) 

```
bar() 中使用的i 是strong symbol (在foo3.c中定义)


* Rule 3: Given multiple weak symbols, choose any of the weak symbols

[foo4.c](foo4.c) [bar4.c](bar4.c)

```
$ gcc -g foo4.c bar4.c
$ gdb a.out
(gdb) l
1	int i;
2	void bar(void);
3	int main()
4	{
5	    i = 1;
6	    bar();
7	    return i;
8	}(gdb) br 7
Breakpoint 1 at 0x60d: file foo4.c, line 7.
(gdb) r
Starting program: /home/alex/base/Alex/blog/programming/a.out 

Breakpoint 1, main () at foo4.c:7
7	    return i;
(gdb) print i
$1 = 3
(gdb) 
```

bar() 中使用的i 是 weak symbol (在foo4.c中定义),这个选取，按规则是随即的。

