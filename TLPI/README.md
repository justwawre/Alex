Last time, the booking reading & practise was under the CentOS, this time is under Ubuntu.

总体读后感，这本书虽然被称为linux开发圣经，但是如果用它来学linux os本身并不合适，它虽然尽可能按讲os的方式来叙述，但总体还是仿APUE，把syscall/lib function 分类作为一个个章节来讲。

# Preparation
## env check
```
$ uname -a
Linux minipc 5.3.0-46-generic #38~18.04.1-Ubuntu SMP Tue Mar 31 04:17:56 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux

$ find /lib/ -name "libc*"
$ getconf GNU_LIBC_VERSION


//用来检查file systems which kernel supports
$ cat /proc/filesystems
$ mount      //To list the currently mounted file systems
```
## install lib
```
sudo apt-get install libacl1-dev  libcap-dev libselinux-dev
```
## download source code

http://www.man7.org/tlpi/


## build
* 修改一下 Makefile.inc 的 CFLAGS / LDLIBS macros.
* 进入lib 目录，make
* 需要编译某某目录时，再调用 make, 退出时 make clean
* 不调用根目录的make

这样 git status 看改动比较清晰。


* [chp13 I/O](IO.md)
* [chp14-19 FILE SYSTEMS](filesystem.md)
* [chp20-22 signal](signal.md)
* [chp3,7,9 24-28 process](process.md)
* [chp29-33 thread](thread.md)
* [chp37  daemon](daemon.md)
* [chp43-48 IPC](IPC.md)
* [chp56-61 socket](socket.md)
* [static & dynamic lib under Linux](../programming/static_dynamic_lib.md)