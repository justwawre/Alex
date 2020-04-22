# static lib

## build & link

[foo4](foo5.c) [bar4](bar4.c) [bar5](bar5.c)
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

```
$ gcc -shared -fPIC -o libbar.so bar4.c bar5.c
$ gcc -g foo5.c  ./libbar.so

```


## 对应命令
ldd