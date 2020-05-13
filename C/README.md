# env
Now tested under (Window WSL) Ubuntu

```
$ uname -a
Linux minipc 5.3.0-46-generic #38~18.04.1-Ubuntu SMP Tue Mar 31 04:17:56 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux

$ gcc -v

gcc version 7.5.0 (Ubuntu 7.5.0-3ubuntu1~18.04) 

```
## std
Mainly using C11 standard

##  zombie issue
It don't work under WSL,the child process's pcb seem be released by WSL. 

Under Ubuntu it work.
```
$ gcc zombie.c 
$ ./a.out &
[1] 8714
$ ps -e -opid,stat,pid,cmd

$ ps -e -opid,stat,pid,cmd
  PID STAT   PID CMD

 8577 S+    8577 ./a.out
 8578 Z+    8578 [a.out] <defunct>

```

