
# chp13 FILE I/O BUFFERING
chp4/5 FILE I/O 讲的file descriptor, a (usually small) nonnegative integer. File descriptors are used to refer to all types of open files, including pipes, FIFOs, sockets, terminals, devices, and regular files. Each process has its own set of file descriptors. alex: 用fd来访问文件的方式，由于没有buffer,编程时一般不直接用，不过OS内部的数据结构是要搞清楚的。

通过fp访问文件， 是标准的 I/O 操作了，理论上修改buffer大小会影响性能，在[log analyzer in C++](../C++/logAnalyzer.md)尝试过，发现自己增大buffer反而降低性能，可能
* 由于现在的磁盘就是有buffer的，修改kernel I/O 本身就没必要
* kernel 默认的就是比较优化了。
