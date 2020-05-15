# pull/run Redis image
默认情况下，Docker从[Docker Hub](https://hub.docker.com/)中提取这些镜像

```bash
$ sudo docker search redis
$ sudo docker pull redis:6.0.1
1:M 15 May 2020 00:17:51.519 * Ready to accept connections

$ sudo docker images
[sudo] password for alex: 
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
redis               6.0.1               f9b990972689        12 days ago         104MB


$ sudo docker run -it redis
Unable to find image 'redis:latest' locally
latest: Pulling from library/redis
^[Digest: sha256:584db7c588cd6d1e0a97bcf67c49016d4f19320b614e07049404bea1d681965e
Status: Downloaded newer image for redis:latest
^[1:C 15 May 2020 00:17:51.515 # oO0OoO0OoO0Oo Redis is starting oO0OoO0OoO0Oo
1:C 15 May 2020 00:17:51.515 # Redis version=6.0.1, bits=64, commit=00000000, modified=0, pid=1, just started
1:C 15 May 2020 00:17:51.515 # Warning: no config file specified, using the default config. In order to specify a config file use redis-server /path/to/redis.conf
                _._                                                  
           _.-``__ ''-._                                             
      _.-``    `.  `_.  ''-._           Redis 6.0.1 (00000000/0) 64 bit
  .-`` .-```.  ```\/    _.,_ ''-._                                   
 (    '      ,       .-`  | `,    )     Running in standalone mode
 |`-._`-...-` __...-.``-._|'` _.-'|     Port: 6379
 |    `-._   `._    /     _.-'    |     PID: 1
  `-._    `-._  `-./  _.-'    _.-'                                   
 |`-._`-._    `-.__.-'    _.-'_.-'|                                  
 |    `-._`-._        _.-'_.-'    |           http://redis.io        
  `-._    `-._`-.__.-'_.-'    _.-'                                   
 |`-._`-._    `-.__.-'    _.-'_.-'|                                  
 |    `-._`-._        _.-'_.-'    |                                  
  `-._    `-._`-.__.-'_.-'    _.-'                                   
      `-._    `-.__.-'    _.-'                                       
          `-._        _.-'                                           
              `-.__.-'                                               

1:M 15 May 2020 00:17:51.518 # WARNING: The TCP backlog setting of 511 cannot be enforced because /proc/sys/net/core/somaxconn is set to the lower value of 128.
1:M 15 May 2020 00:17:51.518 # Server initialized
1:M 15 May 2020 00:17:51.518 # WARNING overcommit_memory is set to 0! Background save may fail under low memory condition. To fix this issue add 'vm.overcommit_memory = 1' to /etc/sysctl.conf and then reboot or run the command 'sysctl vm.overcommit_memory=1' for this to take effect.
1:M 15 May 2020 00:17:51.518 # WARNING you have Transparent Huge Pages (THP) support enabled in your kernel. This will create latency and memory usage issues with Redis. To fix this issue run the command 'echo never > /sys/kernel/mm/transparent_hugepage/enabled' as root, and add it to your /etc/rc.local in order to retain the setting after a reboot. Redis must be restarted after THP is disabled.
1:M 15 May 2020 00:17:51.519 * Ready to accept connections


$ sudo docker images
[sudo] password for alex: 
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
redis               6.0.1               f9b990972689        12 days ago         104MB
redis               latest              f9b990972689        12 days ago         104MB
```
看来TAG很重要，即使同一内容，TAG不同，也要两个image.


# check redis container's ip

```bash
$ sudo docker network inspect bridge 
        "Containers": {
            "36e5bd9e02763a784e32fd75f70336e11b43aa028008cec569325ce937766d08": {
                "Name": "thirsty_hugle",
                "EndpointID": "829ebcec9bd6dbbfc4c9d48aa02c4a243f215858d887b316458485e077dcd74d",
                "MacAddress": "02:42:ac:11:00:02",
                "IPv4Address": "172.17.0.2/16",
                "IPv6Address": ""
            }
        },
```

# client connection

```bash
$ src/redis-cli -h 172.17.0.2
172.17.0.2:6379> set name john
OK
172.17.0.2:6379> get name
"john"
172.17.0.2:6379> 

```

# check process
```bash
$ ps -ef |grep redis
root     20224  2425  0 08:17 pts/1    00:00:00 sudo docker run -it redis
root     20225 20224  0 08:17 pts/1    00:00:00 docker run -it redis
999      20304 20277  0 08:17 pts/0    00:00:07 redis-server *:6379
alex     21830 12055  0 09:28 pts/2    00:00:00 grep --color=auto redis

$ ps -ef |grep 20277
root     20277 16646  0 08:17 ?        00:00:00 containerd-shim -namespace moby -workdir /var/lib/containerd/io.containerd.runtime.v1.linux/moby/36e5bd9e02763a784e32fd75f70336e11b43aa028008cec569325ce937766d08 -address /run/containerd/containerd.sock -containerd-binary /usr/bin/containerd -runtime-root /var/run/docker/runtime-runc
999      20304 20277  0 08:17 pts/0    00:00:09 redis-server *:6379
alex     22028 12055  0 09:39 pts/2    00:00:00 grep --color=auto 20277

$ pstree
systemd─┬─ModemManager───2*[{ModemManager}]
        ├─NetworkManager─┬─dhclient
        │                └─2*[{NetworkManager}]
        ├─accounts-daemon───2*[{accounts-daemon}]
        ├─acpid
        ├─avahi-daemon───avahi-daemon
        ├─bluetoothd
        ├─boltd───2*[{boltd}]
        ├─colord───2*[{colord}]
        ├─containerd─┬─containerd-shim─┬─redis-server───4*[{redis-server}]
        │            │                 └─9*[{containerd-shim}]
        │            └─14*[{containerd}]

```
id 999 应该是比较特殊。

# stop redis container
```bash
$ sudo docker ps
[sudo] password for alex: 
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS              PORTS               NAMES
36e5bd9e0276        redis               "docker-entrypoint.s…"   2 hours ago         Up 2 hours          6379/tcp            thirsty_hugle
$ sudo docker stop 36e5bd9e0276
36e5bd9e0276
$ sudo docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
$ sudo docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
redis               6.0.1               f9b990972689        13 days ago         104MB
redis               latest              f9b990972689        13 days ago         104MB

```
