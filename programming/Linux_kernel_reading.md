
# typeof 
是GNU C 标准中的一个扩展特性.自动推导后面 ( ) 里的数据类型.

a simple example
```C
int var = 666;
typeof(&var) pvar = &var;

```

a complicated one container_of
```C
//copy from kernel
struct st{
    int a;
    int b;
} st, *sp;
typedef  unsigned long size_t;  // typedef unsigned int size_t; if 32 bit

#define offsetof(s, m)   (size_t)&(((s *)0)->m) 

//here type, member are name not variable
#define container_of(ptr, type, member) ({          \
        const typeof( ((type *)0)->member ) *__mptr = (const typeof( ((type *)0)->member ) *)(ptr); \
        (type *)( (char *)__mptr - offsetof(type,member) );\
        })

int main()  //my test code
{
    int var = 666;
    typeof(&var) pvar = &var;  //pvar equal to &var,not only value but type
    int a=({1;2;4;})+10;       //a==14
    int bias = offsetof(struct st,b);

    st.a =3;
    st.b =4;
    typeof(&st.a) ptr = &st.a;
    sp  = container_of(ptr,struct st,a);
    return 0;
}

```
实现根据一个成员指针ptr去找它的container地址的功能是非常简单的,就 ptr - bias; 难点在于需要声明ptr, 和它container的类型,这样就不够通用了。

但linux kernel中 linked list是一种类似STL iterator 一样的设计, 适用于任何container, 所以必须要用macro 来解决.( 哈哈, STL本质也是一种macro!!)



# 红黑树（Red-Black Tree，RBT）

## 二叉查找树（BST）具备什么特性呢？
* 左子树上所有结点的值均小于或等于它的根结点的值。
* 右子树上所有结点的值均大于或等于它的根结点的值。
* 左、右子树也分别为二叉排序树。

## 红黑树是一种平衡的二叉查找树.
1. 节点是红色或黑色。
2. 根节点是黑色。
3. 每个叶子节点都是黑色的空节点（NIL节点）。
4. 每个红色节点的两个子节点都是黑色。(从每个叶子到根的所有路径上不能有两个连续的红色节点)
5. 从任一节点到其每个叶子的所有路径都包含相同数目的黑色节点。

我理解，根据规则2，3，4， 任何路径上，红色节点肯定比黑色的少。 而路径最短的情况是一路全黑为n个， 最长的情况是红色节点比黑色少一个为n-1.根据规则5， 最长路径为2n-1,最短的为n.
整个红黑树的查找，插入和删除都是O(logN)的，原因就是整个红黑树的高度是logN，查找从根到叶，走过的路径是树的高度，删除和插入操作是从叶到根的，所以经过的路径都是logN。

## data structure & operation

```C
struct rb_node
{
	unsigned long  rb_parent_color;
#define	RB_RED		0
#define	RB_BLACK	1
	struct rb_node *rb_right;
	struct rb_node *rb_left;
} __attribute__((aligned(sizeof(long))));

struct rb_root
{
	struct rb_node *rb_node;
};

//其上配套的操作

#define rb_parent(r)   ((struct rb_node *)((r)->rb_parent_color & ~3)) //低两位清0
#define rb_color(r)   ((r)->rb_parent_color & 1)                       //取最后一位
#define rb_is_red(r)   (!rb_color(r))                                  //最后一位为0？
#define rb_is_black(r) rb_color(r)                                     //最后一位为1？
#define rb_set_red(r)  do { (r)->rb_parent_color &= ~1; } while (0)    //最后一位置0
#define rb_set_black(r)  do { (r)->rb_parent_color |= 1; } while (0)   //最后一位置1

static inline void rb_set_parent(struct rb_node *rb, struct rb_node *p) //设置父亲
{
	rb->rb_parent_color = (rb->rb_parent_color & 3) | (unsigned long)p;
}
static inline void rb_set_color(struct rb_node *rb, int color)          //设置颜色
{
	rb->rb_parent_color = (rb->rb_parent_color & ~1) | color;
}

```
其中的一点骚操作是：

rb_parent_color这个域其实同时包含了颜色信息以及父亲节点的指针，因为该域是一个long的类型，而struct 是sizeof(long)的对齐，即使32位机器上，其后两位的数值永远是0，于是可以拿其中的一位来表示颜色，这里使用了最低位来表示颜色信息。

## rbt调整
但插入或删除node时，规则会被破坏，所以需要调整，调整手段不外乎
* node 变色
* 子树左旋
* 子树右旋

## usage example

```C
struct mytype *my_search(struct rb_root *root, char *string)
{
	struct rb_node *node = root->rb_node;
	while (node)
	{
		struct mytype *data = container_of(node, struct mytype, node);
		int result = strcmp(string, data->keystring);
		if (result < 0)
			node = node->rb_left;
		else if (result > 0)
			node = node->rb_right;
		else
			return data;
	}
	return NULL;
}

```
根据 container_of(ptr, type, member) 的规则，可以推出 mytype 的定义应该类似

```C
struct mytype
{
    struct rb_node *node;
    char *keystring;
};
```
与rbt库中的数据结构类似

```C
struct rb_root
{
	struct rb_node *rb_node;
};
```
也就是说牺牲一个 指针的空间，就可以使用rbt的所有功能了。

# book:Linux Kernel Development 3e
the book is based on kernel 2.6.

## the process have 3 states

the Linux specific concept, the process have 3 states:

* In user-space, executing user code in a process
* In kernel-space, in process context, executing on behalf of a specific process
* In kernel-space, in interrupt context, not associated with a process, handling an interrupt,not associated with any process.This special context exists solely to let an interrupt handler quickly respond to an interrupt, and then exit.

This list is inclusive. Even corner cases fit into one of these three activities: For example, when idle, it turns out that the kernel is executing an idle process in process context in the kernel.

## differences between the Linux kernel and Unix's
* Linux supports the dynamic loading of kernel modules
* The Linux kernel is preemptive, can preempt a task even as it executes in the kernel
* Linux provides an object-oriented device model with device classes, hot-pluggable events, and a user-space device filesystem (sysfs).

## kernel differ to normal program
* The kernel has access to neither the C library nor the standard C headers.
* The kernel is coded in GNU C.
* The kernel lacks the memory protection afforded to user-space.
* The kernel cannot easily execute floating-point operations.
* The kernel has a small per-process fixed-size stack.
* Because the kernel has asynchronous interrupts, is preemptive, and supports SMP, synchronization and concurrency are major concerns within the kernel.
* Portability is important.

总体感觉,kernel 的编程一方面类似普通的嵌入式开发,资源有限,另外一方面由于os的特点,需要考虑的地方,支持的功能都比较多.

## Process Descriptor and the Task Structure
The kernel stores the list of processes in a circular doubly linked list called the task list. Each element in the task list is a process descriptor of the type struct task_struct, which is defined in <linux/sched.h>.The process descriptor contains all the information about a specific process.

The task_struct is a relatively large data structure, at around 1.7 kilobytes on a 32-bit machine.This size, however, is quite small considering that the structure contains all the information that the kernel has and needs about a process.

## Multitasking
operating systems come in two flavors: cooperative multitasking and preemptive multitasking. In preemptive multitasking, the scheduler decides when a process is to cease running and a new process is to begin running.The act of involuntarily suspending a running process is called preemption.Conversely, in cooperative multitasking, a process does not stop running until it voluntary decides to do so.The act of a process voluntarily suspending itself is called yielding.

## Policy
is the behavior of the scheduler that determines what runs when.

I/O-Bound Versus Processor-Bound Processes: The former is characterized as a process that spends much of its time submitting and waiting on I/O requests.Conversely, processor-bound processes spend much of their time executing code. The scheduling policy in a system must attempt to satisfy two conflicting goals: fast process response time (low latency) and maximal system utilization (high throughput).


## System call
	long syscall(long number, ...);
The mechanism to signal the kernel is a software interrupt: The defined software interrupt on x86 is interrupt number 128, which is incurred via the int $0x80 instruction. It triggers a switch to kernel mode and the execution of exception vector 128, which is the system call handler. On x86, the syscall number is fed to the kernel via the eax register. On x86-32, the registers ebx, ecx, edx, esi, and edi contain, in order, the first five arguments。The return value is sent to user-space also via register. On x86, it is written into the eax register.

In process context, the kernel is capable of sleeping (for example, if the system call blocks on a call or explicitly calls schedule()) and is fully preemptible. These two points are important. First, the capability to sleep means that system calls can make use of the majority of the kernel's functionality. the capability to sleep greatly simplifies kernel programming.

The fact that process context is preemptible implies that, like user-space, the current task may be preempted by another task. Because the new task may then execute the same system call, care must be exercised to ensure that system calls are reentrant.

# Interrupt handler
印象中是为了缩短disable interrupt的时间，enable interrupt后就会产生中断嵌套的执行方式。

* the top half,
* the bottom half,

以下摘自《Linux设备驱动开发详解》

    设备的中断会打断内核中进程的正常调度和运行，系统对更高吞吐率的追求势必要求中断服务程序尽可能的短小精悍。但是这个良好的愿望往往与现实并不吻合。在大多数真实的系统中，当中断到来时，要完成的工作往往并不会是短小的，它可能进行较大量的耗时处理。
为了在中断执行时间尽可能短和中断处理需完成大量工作之间找到一个平衡点，Linux将中断处理程序分解为两个部分：顶半部和底半部（top half和bottom half）。

    顶半部完成尽可能少的比较紧急的功能，它往往只是简单的读取寄存器中中断状态并清除中断标志后就进行“登记中断”的工作。“登记中断”意味着将底半部处理程序挂到该设备的底半部执行队列中去。这样，顶半部执行的速度就会很快，可以服务更多的中断请求。
    现在，中断处理工作的中心就落在了底半部的头上，它来完成中断事件的绝大多数认为。底半部几乎做了中断处理程序所有的事情，而其可以被新的中断打断，这也是底半部和顶半部最大的不同，因为顶半部往往被设计成不可中断。底半部则相对来说并不是非常紧急的，而且相对比较耗时，不在硬件中断服务程序中执行。
    尽管顶半部、底半部的结合能够改善系统的相应能力，但是，僵化地认为Linux设备驱动中的中断处理一定要分为两个半部则是不对的。如果中断要处理的工作本身很少，则完全可以直接在顶半部全部完成。

## Building the Kernel
	$ git clone git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux-2.6.git

	#kernel source code: /usr/src/linux-5.x
	#build directory:    ~


	$sudo apt-get install libncurses5-dev 
	$sudo apt install flex bison

	$ cd /usr/src/linux-5.0.4/
	$ make O=~ menuconfig
	$ make O=~


