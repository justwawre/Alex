
由于UNIX被Linux取代，当初看的，写的code，现在已经不太重要，就记录一下当初用的一些工具吧。

# the bash command 
    #the simple one
    find . -name "*.c" |xargs grep "xxxx"

    # to tailor the ps output
    ps -o pid,ppid,pgid,sid,tpgid,comm

    #删除代码的行号
    sed -e '/^[0-9]*[\t]*[ ]*:/s///' inf.c

    #disable the default optimization
    gcc -g  -O0 scope.c -o scope.exe

 # nice()  don't work in multi cpu arch
before, in my own CentOS pc, the nice don't work, in WSL, the same situation.
* the child process nice valued modified, but the scheduling was not affected
* using top -H 看，nice 
* lscpu to check
   
 Alex:应该是多核cpu下，由于两个process运行在不同的core上，nice() 已经没有什么意义。

 # grpof:
    $gcc -pg loop_sleep.c 
    $./a.out
    $ls
    a.out  gmon.out  loop_sleep.c
    $gprof ./a.out 
    Flat profile:
    Each sample counts as 0.01 seconds.
    no time accumulated

# using clang-format to format source file
    apt-get install clang-format
在代码当前目录新建.clang-format文件（注意文件名开头的.），内容为：
```
BasedOnStyle: LLVM
IndentWidth: 8
UseTab: Always
BreakBeforeBraces: Linux
AllowShortIfStatementsOnASingleLine: false 
IndentCaseLabels: false
```

#  disable the " division by zero" warning
    gcc -g -Wno-div-by-zero to