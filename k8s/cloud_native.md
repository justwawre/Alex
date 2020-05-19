# cloud native vs openstack
cloud native or openstack are all solution to provide a reliable/scable/ distributed framework.
the openstack aim to provide a framework based on VM, developer deploy their program in 1 or many VM.
Althoug the openstack is welcomed by the cloud provided, because they can sell VM in terms like memory, cpu power, bandwidth. but from developer's view, the VM is costly and too slow. so the Kubernetes was made .

# docker vs VM
个人理解docker 是介于 virtual env 与 virtual machine 之间的概念.

virtualenv就是用来为一个应用创建一套“隔离”的Python运行环境。virtualenv为应用提供了隔离的Python运行环境，解决了不同应用间多版本的冲突问题。

virtual machine 是由hypervisor模拟一台电脑的完整启动环境

Some virtual machines, such as QEMU, are designed to also emulate different architectures and allow execution of software applications and operating systems written for another CPUor architecture. Operating-system-level virtualizationallows the resources of a computer to be partitioned via the kernel's support for multiple isolated user spaceinstances, which are usually called containersand may look and feel like real machines to the end users.

docker :

只是记录一个执行环境,如python所需要的所有库文件, 不记录状态,如需要则关联到数据卷（Volumes）和挂载主机目录（Bind mount）. Docker 使用 Google 公司推出的 Go 语言进行开发实现，基于 Linux 内核的 cgroup，namespace，以及 AUFS类的 Union FS等技术，对进程进行封装隔离，属于 操作系统层面的虚拟化技术。

docker 里面只有rootfs, 没有 kernel, 它当然不需要跟虚拟机里的guest os 一样 boot 一遍.


# Kubernetes
Kubernetes is based on docker, but it encapsulate many logic terms:
## node:
a physical or virtual machine

## pod:
the unit of deployment, here you can configure memory, cpu power, bandwidth requirement.

它由⼀个或者多个容器组成（ 例如Docker容器） ， 它们共享容器存储、 ⽹络和容器运⾏配置项。 Pod中的容器总是被同时调度， 有共同的运⾏环境。Pod中的容器共享IP地址和端⼝号， 它们之间可以通过 localhost 互相发现。 它们之间可以通过进程间通信， 例如SystemV信号或者POSIX共享内存。 不同Pod之间的容器具有不同的IP地址， 不能直接通过IPC通信。Pod中的容器也有访问共享volume的权限， 这些volume会被定义成pod的⼀部分并挂载到应⽤容器的⽂件系统中。pod被创建后， 被分配⼀个唯⼀的ID（ UID） ， 调度到节点上， 并⼀致维持期望的状态直到被终结（ 根据重启策略） 或者被删除。Volume跟pod有相同的⽣命周期（ 当其UID存在的时候） 。 当Pod因为某种原因被删除或者被新创建的相同的Pod取代， 它相关的东⻄（ 例如volume） 也会被销毁和再创建⼀个新的volume。

## deployment:
here you ask the k8s for reliable/scable. the Yaml file is just a contract, via the contract, the k8s monitor the, recovery the failed pod, scale up/down.

Deployment 为 Pod 和 ReplicaSet 提供了⼀个声明式定义(declarative)⽅法(不需要写第一步第二步....)， ⽤来替代以前的ReplicationController 来⽅便的管理应⽤。 典型的应⽤场景包括：
* 定义Deployment来创建Pod和ReplicaSet
* 滚动升级和回滚应⽤
* 扩容和缩容
* 暂停和继续Deployment

## service:
the service which developer aim to provide

Kubernetes Service 定义了这样⼀种抽象： ⼀个 Pod 的逻辑分组， ⼀种可以访问它们的策略 —— 通常称为微服务。 这⼀组 Pod 能够被Service 访问到， 通常是通过 Label Selector （ 查看下⾯了解， 为什么可能需要没有 selector 的 Service ） 实现的。

举个例⼦， 考虑⼀个图⽚处理 backend， 它运⾏了3个副本。 这些副本是可互换的 —— frontend 不需要关⼼它们调⽤了哪个 backend 副本。 然⽽组成这⼀组 backend 程序的 Pod 实际上可能会发⽣变化， frontend 客户端不应该也没必要知道， ⽽且也不需要跟踪这⼀组 backend 的状态。Service 定义的抽象能够解耦这种关联。

Pod在设计支持就不是作为持久化实体的。在调度失败、节点故障、缺少资源或者节点维护的状态下都会死掉会被驱逐。通常，用户不需要手动直接创建Pod，而是应该使用controller（例如Deployments），即使是在创建单个Pod的情况下。Controller可以提供集群级别的自愈功能、复制和升级管理。

## label selector
客户端／用户可以指定一个object集合，通过label selector对object的集合进行操作。

Kubernetes中为了实现服务实例间的负载均衡和不同服务间的服务发现，创造了Serivce对象，同时又为从集群外部访问集群创建了Ingress对象。

在 Kubernetes 集群中，每个 Node 运行一个kube-proxy进程。kube-proxy负责为Service实现了一种 VIP（虚拟 IP）的形式，从 Kubernetes v1.2 起，默认就是 iptables 代理。

