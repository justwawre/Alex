# chp14 FILE SYSTEMS

不像MS-DOS/Windows, Linux 的文件系统与kernel之间是de-coupling的，方法就是通过vfs定义接口，支持相关接口的文件系统就可以mount上去。
![vfs](images/fig_14_3.png)
列出OS已经加载的driver.
```
$ cat /proc/filesystems
nodev	sysfs
nodev	tmpfs
nodev	bdev
```
![Layout of disk partitions and a file system](images/fig_14_1.png)

##  i-node
是文件系统的核心数据结构，There is a i-node table, 每一个entry 中的 datablock pointer指向物理文件(data block).与ms dos的一维FAT表不同，unix 的i-node表可以是多维的。

![ext2](images/fig_14_2.png)

# chp15 FILE ATTRIBUTES

# chp16 EXTENDED ATTRIBUTES

# chp17 ACCESS CONTROL LISTS
记得上次在CentOS上，ACL还是需要编译一些东西才能支持，现在这Ubuntu 上是直接支持。

```
$  getfacl  .
# file: .
# owner: alex
# group: alex
user::rwx
group::r-x
other::r-x

$ which getfacl
/usr/bin/getfacl
```
不过感觉没多大用处。

# chp18 DIRECTORIES AND LINKS

## A directory
is stored in the file system in a similar way to a regular file. Two things distinguish a directory from a regular file:
* A directory is marked with a different file type in its i-node entry。
* A directory is a file with a special organization. Essentially, it is a table consisting of filenames and i-node numbers (index of i-node table).

The i-node table is numbered starting at 1, rather than 0, because 0 in the i-node field of a directory entry indicates that the entry is unused. I-node 1 is
used to record **bad blocks** in the file system. The **root directory (/)** of a file system is always stored in i-node entry 2 (as shown in Figure 18-1), so that the kernel knows where to start when resolving a pathname.

下图展示如何找到/etc/passwd 对应的datablock 
![Relationship between i-node and directory structures for the file /etc/passwd](images/fig_18_1.png)

## hard link
```
$ touch  abc
$ ln abc xyz
$ echo "hard link" >>xyz
$ cat abc
hard link
$ ls -li abc xyz
7881299347950837 -rwxrwxrwx 2 alex alex 10 Mar 20 21:12 abc
7881299347950837 -rwxrwxrwx 2 alex alex 10 Mar 20 21:12 xyz
$ rm abc
$ ls -li  xyz
7881299347950837 -rwxrwxrwx 1 alex alex 10 Mar 20 21:12 xyz
```
也就是directory 的 table 增加一个entry, 不同的filenames 相同的 i-node numbers.

## symbolic link
* directory,如同regular file, table 增加一个entry,指向一个新i-node 
* 新i-node,类型为 symbolic link:其指向的data block 的内容就是 pathname.

![ Representation of hard and symbolic links](images/fig_18_2.png)


# chp19 MONITORING FILE EVENTS
Starting with kernel 2.6.13, Linux provides the inotify mechanism, which allows an application to monitor file events. 

## inotify (similar to select())
mechanism allows an application to obtain notifications when events (files are opened, closed, created, deleted, modified, renamed, and so on) occur for a set of monitored files and directories.

    $ touch abc

    $ ./demo_inotify abc &
    [1] 399
    Watching abc using wd 1

    $ echo "abcdefg" >>abc
    Read 32 bytes from inotify fd
        wd = 1; mask = IN_MODIFY
    $ mv abc efg
    Read 16 bytes from inotify fd
        wd = 1; mask = IN_MOVE_SELF

# signal
is a notification to a process that an event has occurred. e.g.The abort() function generates a SIGABRT signal for the process,which causes it to dump core and terminate.

we can use the null signal (num 0) to test if a process with a specific process ID exists.(alternative:The /proc/PID interface: For example, if a process with the process ID 12345 exists, then the directory /proc/12345 will exist, and we can check this using a call such as stat().)

![tbd](images/TLPI_signal.png)

sigprocmask()/process;pthread_sigmask()/thread to maintain signal mask(a set of signals whose delivery to the process is currently blocked)

delivered only once even if the signal is generated more than once while blocked or the handler is executing. (Signals Are Not Queued)

    $ ./sig_receiver 60 &
    [2] 73
    [1]   Killed                  ./sig_receiver 600
    $ ./sig_receiver: PID is 73
    ./sig_receiver: sleeping for 60 seconds

    $ ./sig_sender 73 99 10 2
    ./sig_sender: sending signal 10 to process 73 99 times
    ./sig_sender: exiting
    $ ./sig_receiver: pending signals are:
                    2 (Interrupt)
                    10 (User defined signal 1)
    ./sig_receiver: signal 10 caught 1 time

## Reentrant and nonreentrant functions
can safely be simultaneously executed by multiple threads of execution in the same process. A function may be nonreentrant if it updates global or static data structures. (A function that employs only local variables is guaranteed to be reentrant.)

## async-signal-safe functions
is one that the implementation guarantees to be safe when called from a signal handler. A function is async-signal-safe either because it is reentrant or because it is not interruptible by a signal handler.

When a signal handler interrupts a blocked system call, the system call fails with the error EINTR. We can take advantage of this behavior to, for example, set a timer on a blocking system call.
```c

    alarm((argc > 1) ? getInt(argv[1], GN_NONNEG, "num-secs") : 10);
    numRead = read(STDIN_FILENO, buf, BUF_SIZE);
    savedErrno = errno;                 /* In case alarm() changes it */
    alarm(0);                           /* Ensure timer is turned off */
    errno = savedErrno;
    /* Determine result of read() */
    if (numRead == -1) {
        if (errno == EINTR)
            printf("Read timed out\n");
        else
            errMsg("read");
    } else {
        printf("Successful read (%ld bytes): %.*s",
                (long) numRead, (int) numRead, buf);
    }
```

above code show how signal interrupt the read ( the blocking IO), when run

    $ ./timed_read  5    
    `12345678Caught signal  //没有回车,所以read 没有读到任何东西,timers停止了无尽的等待
    Read timed out

## Synchronous and Asynchronous Signal Generation
synchronously generated signals are delivered immediately. For example, a hardware exception triggers an immediate signal, and when a process sends itself a signal using raise(), the signal is delivered before the raise() call returns.

When a signal is generated asynchronously, there may be a (small) delay.The reason for this is that the kernel delivers a pending signal to a process only at the next switch from kernel mode to user mode while executing that process.e.g.rescheduled or completion of a system call.

![tbd](images/TLPI_signal_unblocked.png)

## Realtime signals
are a POSIX addition to the original signal model, and differ from standard signals in that they are queued, have a specified delivery order, and can be sent with an accompanying piece of data.

## timer/sleep
```c
#include <sys/time.h>
int setitimer(int which, const struct itimerval *new_value,struct itimerval *old_value);
```
When I developing the Statistics framework, use the timer frequently, in SDL you need set timer again when it expired (like alarm(unsigned int seconds) in unix), in unix, you only need specify the interval.

    $ ./ptmr_sigev_signal  2:5 3:5 4:5
    Timer ID: 140737243296384 (2:5)
    Timer ID: 140737243300528 (3:5)
    Timer ID: 140737243300560 (4:5)
    [10:07:12] Got signal 64
        *sival_ptr         = 140737243296384
        timer_getoverrun() = 0
    [10:07:13] Got signal 64
        *sival_ptr         = 140737243300528
        timer_getoverrun() = 0
    [10:07:14] Got signal 64
        *sival_ptr         = 140737243300560
        timer_getoverrun() = 0
    [10:07:17] Got signal 64
        *sival_ptr         = 140737243296384
        timer_getoverrun() = 0
    [10:07:18] Got signal 64
        *sival_ptr         = 140737243300528
        timer_getoverrun() = 0
    ^C

Linux 2.6 can: create multiple timers; choose the signal that is delivered on timer expiration; retrieve the timer overrun count in order to determine if a timer has expired multiple times since the last expiration notification;and choose to receive timer notifications via execution of a thread function instead of delivery of a signal.

# process
## lifecycle
![tbd](images/TLPI_process.png)

## file descriptors during fork()
![tbd](images/TLPI_fork_fd.png)

## Memory Semantics of fork()
![tbd](images/TLPI_fork_memory.png)

# pthread
## Overview
![tbd](images/TLPI_pthread.png)

# THREAD SYNCHRONIZATION

## static mutex
```c
static volatile int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void *   threadFunc(void *arg)
{
    int loops = *((int *) arg);
    for (j = 0; j < loops; j++) {
        s = pthread_mutex_lock(&mtx);
        glob++;
        s = pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;
    loops = 10000000;
    s = pthread_create(&t1, NULL, threadFunc, &loops);
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    s = pthread_join(t1, NULL);
    s = pthread_join(t2, NULL);
    printf("glob = %d\n", glob);
    exit(EXIT_SUCCESS);
}
```
## dynamic mutex
```c
void foo()
{
    pthread_mutex_t mtx;
    pthread_mutexattr_t mtxAttr;
    int s, type;
    s = pthread_mutexattr_init(&mtxAttr);
    s = pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_ERRORCHECK);
    s = pthread_mutex_init(mtx, &mtxAttr);
    s = pthread_mutexattr_destroy(&mtxAttr);
}
```
## condition variable
is always used in conjunction with a mutex. The mutex provides mutual exclusion for accessing the shared variable, while the condition variable is used to signal changes in the variable's state.

example:Statically Allocated Condition Variables in producer-consumer
```c
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int avail = 0; //the number of produced units awaiting consumption

//producer thread
    s = pthread_mutex_lock(&mtx);
    avail++;        /* Let consumer know another unit is available */
    s = pthread_mutex_unlock(&mtx);
    s = pthread_cond_signal(&cond);         /* Wake sleeping consumer */

//consumer thread
    for (;;) {
        s = pthread_mutex_lock(&mtx);
        while (avail == 0) { //cond的作用就是让程序不进入后一个while,而是等调度的通知
            s = pthread_cond_wait(&cond, &mtx);
        }
        while (avail > 0) { /* Consume all available units */
            avail--;
        }
        s = pthread_mutex_unlock(&mtx);
    }

```
# Thread Safety
There are various methods of rendering a function thread-safe. One way is to associate a mutex with the function (or perhaps with all of the functions in a library, if they all share the same global variables). Here introducing the concept: critical section.

A reentrant function achieves thread safety without the use of mutexes. It does this by avoiding the use of global and static variables. Any information that must be returned to the caller, or maintained between calls to the function, is stored in buffers allocated by the caller.

## One-Time Initialization
```c
int pthread_once(pthread_once_t *once_control, void (*init)(void));
```
## Thread-Specific Data
Thread-specific data is a technique for making an existing function thread-safe without changing its interface. A function that uses thread-specific data may be slightly less efficient than a reentrant function, but allows us to leave the programs that call the function unchanged.

![tbd](images/TLPI_pthread_tsd.png)

```c
static pthread_once_t once = PTHREAD_ONCE_INIT;
static pthread_key_t strerrorKey;

#define MAX_ERROR_LEN 256  
static void destructor(void *buf)
{
    free(buf);
}

static void createKey(void)
{
    int s;
    s = pthread_key_create(&strerrorKey, destructor);
}

char * strerror(int err)
{
    int s;
    char *buf;
    /* Make first caller allocate key for thread-specific data */
    s = pthread_once(&once, createKey);
    buf = pthread_getspecific(strerrorKey);
    if (buf == NULL) {          /* If first call from this thread, allocate
                                   buffer for thread, and save its location */
        buf = malloc(MAX_ERROR_LEN);
        s = pthread_setspecific(strerrorKey, buf);//通过set/get 进行关联
    }
    strncpy(buf, _sys_errlist[err], MAX_ERROR_LEN - 1);
    buf[MAX_ERROR_LEN - 1] = '\0';          /* Ensure null termination */
    return buf;
}
```
用TSD 将strerror() 改造成 thread safe.

## Thread-Local Storage (provided since Linux 2.6)
The main advantage of thread-local storage is that it is much simpler to use than thread-specific data. To create a thread-local variable, we simply include the __thread specifier in the declaration of a global or static variable:
```c
static __thread buf[MAX_ERROR_LEN];
```
TLD 比 TSD 简化太多了。

## summary
所以归纳一下实现thread safe的方法有 mutex/reentrant /tsd/tls 四种.

# Cancel a Thread
self termination: pthread_exit() or returning

cancel a thread; that is, to send it a request asking it to terminate now. 有点类似发signal,主动权在接收方, 运行到cancellation point 时才能响应.

asynchronously cancelable (cancelability type PTHREAD_CANCEL_ASYNCHRONOUS), it may be canceled at any time (i.e., at any machinelanguage instruction); delivery of a cancellation is not held off until the thread next reaches a cancellation point.

# thread: further detail
尽量不要用signal. 
The UNIX signal model was designed with the UNIX process model in mind, and predated the arrival of Pthreads by a couple of decades. The differences between the signal and thread models mean that combining signals and threads is complex, and should be avoided whenever possible. (使用mutex/condition variable)

Alex: signal 是kernel-->user process的通知方式，如果用的话就需要建立process ->thread的消息分发机制。

# Since kernel 2.6.since version 2.4, glibc no longer provides the deprecated LinuxThreads.
    $ getconf GNU_LIBPTHREAD_VERSION
    NPTL 2.27

# Daemon
* [source code](daemon.c)

## Using SIGHUP to Reinitialize a Daemon
to have the daemon establish a handler for SIGHUP, and perform the required steps upon receipt of this signal.

# Shared libraries
    $ gcc -g -fPIC -Wall mod1.c mod2.c mod3.c -shared -o libfoo.so

    $ objdump --all-headers libfoo.so | grep TEXTREL  //检查动态库中是否有不用-fPIC 编译的模块
    //The string TEXTREL indicates the presence of an object module whose text segment contains 
    //a reference that requires run-time relocation.

    $ LD_LIBRARY_PATH=. ./prog    // 就执行 prog的时候替换一下该环境变量

![tbd](images/TLPI_sharedlib_link.png)

## soname, alias of so
If a shared library has a soname, then this name, rather than the library’s real name, is recorded in the resulting executable.

    $ gcc -g -shared -Wl,-soname,libbar.so -o libfoo.so mod1.o mod2.o mod3.o
    $ objdump -p libfoo.so | grep SONAME
    SONAME libbar.so

    $ ln -s libfoo.so libbar.so Create soname symbolic link in current directory
    $ LD_LIBRARY_PATH=. ./prog

* [my another doc about lib](static_dynamic_lib.md)

![tbd](images/TLPI_sharedlib_run.png)


# IPC
![tbd](images/TLPI_IPC.png)


# book & source code
