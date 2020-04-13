# A Linux cluster 
is a connected array of Linux computers or nodes that work together and can be viewed and managed as a single system. Nodes are usually connected by fast local area networks, with each node running its own instance of Linux. Nodes may be physical or virtual machines, and they may be separated geographically. Each node includes storage capacity, processing power and I/O (input/output) bandwidth. Multiple redundant nodes of Linux servers may be connected as a cluster for high availability (HA) in a network or data center, where each node is capable of failure detection and recovery.

Clusters are usually dedicated to specific functions, such as load balancing, high availability, high performance, storage or large-scale processing.

# SuSe HA
看了一下,SuSe HA的做法与IPA十分类似

* scp 同步corosync.conf, 由于是跨公网的,需要ssl支持,还需要配置文件
* Virtual IP 等同于IPA的logical IP
* node 可以共享存储设备
* more security concern, e.g. ACL/SSH
* open source, so can integrated with existing open source project.
总体来说电信设备的冗余-->cluster---->p2p的一大区别就是信任程度不同,IPA的程序都是自己的,ssh/ACL都不需要用; cluster 用ssh,但是认为所有的node及通信线路都是安全的,没有拜占庭欺骗存在; p2p则没有以上信任,并且由于node 成员没有稳定的时候,也用不了DLM.


# OpenAIS
是基于SA Forum 标准的集群框架的应用程序接口规范。OpenAIS提供一种集群模式，这个模式包括集群框架，集群成员管理，通信方式，集群监测等，能够为集群软件或工具提供满足 AIS标准的集群接口，但是它没有集群资源管理功能，不能独立形成一个集群。OpenAIS组件包括AMF,CLM,CKPT,EVT,LCK,MSG，TMR,CPG,EVS等，因OpenAIS分支不同，组件略有不同。（下面介绍）OpenAIS主要包含三个分支：Picacho，Whitetank，Wilson。

# Corosync
是OpenAIS发展到Wilson版本后衍生出来的开放性集群引擎工程。可以说Corosync是OpenAIS工程的一部分。OpenAIS从openais0.90开始独立成两部分，一个是Corosync；另一个是AIS标准接口Wilson。Corosync包含OpenAIS的核心框架用来对Wilson的标准接口的使用、管理。它为商用的或开源性的集群提供集群执行框架。Corosync执行高可用应用程序的通信组系统.



# Pacemaker
 (直译：心脏起搏器)升级到1.0版本后，从Heartbeat独立出来，Pacemaker achieves maximum availability for your cluster services by detecting and recovering from node and service-level failures. It achieves this by utilizing the messaging and membership capabilities provided by your preferred cluster infrastructure (currently either OpenAIS or Heartbeat)



# Oracle Cluster File System 2 (OCFS2) 
is a general-purpose journaling file system that has been fully integrated since the Linux 2.6 Kernel. OCFS2 allows you to store application binary files, data files, and databases on devices on shared storage. All nodes in a cluster have concurrent read and write access (也就是说支持DLM 功能)to the file system. A user-space control daemon, managed via a clone resource, provides the integration with the HA stack, in particular with OpenAIS/Corosync and the Distributed Lock Manager (DLM).

