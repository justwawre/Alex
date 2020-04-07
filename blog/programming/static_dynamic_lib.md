**static/dynamic lib**
### test env:
* Centos 7: kernel 4.17.2-1. x86_64 GNU/Linux
* gcc 4.85

### static lib
* build lib
```   
gcc -ansi -I../include -Wall -DLINUX -D_GNU_SOURCE  -c err.c 
ar rcs ../libapue/libapue.a err.o
```
* List symbols in [file(s)] (a.out by default).
```   
nm -s libapue.a 
Archive index:
err_ret in err.o
err_sys in err.o   
```   
* link with static lib  
-L specify the search path,   
-lapue  mean linking libapue.a
e.g.
```    
gcc -ansi -I../include -Wall -DLINUX -D_GNU_SOURCE  ls1.c -o ls1  -L../libapue -lapue 
```

### dynamuic lib , wo version 
* build
```
gcc -shared -fPIC -o libapue.so err.c
```
* link:
```
gcc -I../include -o ls1 -L../libapue ls1.c -lapue
```
* run
```
./ls1 .
error while loading shared libraries: libapue.so: cannot open shared object file: No such file or directory
set the right env to fix path issue
export LD_LIBRARY_PATH="$HOME/base/clang/apue/libapue"
```
* checking the exe's dependency
```
ldd ls1
```

### dynamic lib, with version 
some terms
* filename: file generated, e.g. gcc -O <xxx>
* soname: （ Short for shared object name）， with major version,
           specified in gcc cmd's option:  -Wl,-soname  
* link filename:  used in gcc -l <yyy>

* build lib with soname and filename
```
gcc -shared -fPIC -Wl,-soname=libapue.so.0 -o libapue.so.0.1 err.o
```
* check via soname
```
readelf -d libapue.so.0

Dynamic section at offset 0x1df8 contains 25 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 0x000000000000000e (SONAME)             Library soname: [libapue.so.0]
```
* create link to soname
```
ldconfig -n .
ln -sf libapue.so.0 libapue.so
ls -l
lrwxrwxrwx. 1 alex alex    12 8月   1 14:14 libapue.so -> libapue.so.0
lrwxrwxrwx. 1 alex alex    14 8月   1 14:15 libapue.so.0 -> libapue.so.0.1
-rwxrwxr-x. 1 alex alex 12928 8月   1 14:10 libapue.so.0.1
```
* linking with link's name
```
gcc -Wall -I../include -L../libapue  ls1.c -lapue -o ls1
```

### load lib by program itself
```
 dlclose, dlopen, dlmopen - open and close a shared object
```