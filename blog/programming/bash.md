
# some usual bash command 

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
# simple sample

 [hello](hello.sh)