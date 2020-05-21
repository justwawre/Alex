# some cmd use frequently

```
    #the simple one
    find . -name "*.c" |xargs grep "xxxx"

    # to tailor the ps output
    ps -o pid,ppid,pgid,sid,tpgid,comm

    #删除代码的行号
    sed -e '/^[0-9]*[\t]*[ ]*:/s///' inf.c

    #disable the default optimization
    gcc -g  -O0 scope.c -o scope.exe

```
# change fileformat via VI
```
:set ff
:set ff=unix
```
# script sample
```bash
$ ./hello.sh xu
Hello, alex xu 
How to address you? Mr./Ms.
Mr.
Thanks, Mr. xu! 
```
