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

# check image

```bash
$ sudo docker inspect redis

        "Id": "sha256:f9b9909726890b00d2098081642edf32e5211b7ab53563929a47f250bcdc1d7c",
        "RepoTags": [
            "redis:6.0.1",
            "redis:latest"
        ],

        "RootFS": {
            "Type": "layers",
            "Layers": [
                "sha256:c2adabaecedbda0af72b153c6499a0555f3a769d52370469d8f6bd6328af9b13",
                "sha256:744315296a49be711c312dfa1b3a80516116f78c437367ff0bc678da1123e990",
                "sha256:379ef5d5cb402a5538413d7285b21aa58a560882d15f1f553f7868dc4b66afa8",
                "sha256:d00fd460effb7b066760f97447c071492d471c5176d05b8af1751806a1f905f8",
                "sha256:4d0c196331523cfed7bf5bafd616ecb3855256838d850b6f3d5fba911f6c4123",
                "sha256:98b4a6242af2536383425ba2d6de033a510e049d9ca07ff501b95052da76e894"
            ]
        },

```
docker镜像由多个文件系统（只读层）叠加而成，当我们启动一个容器时，docker会加载只读层镜像并在其上（即镜像栈顶部）添加一个读写层。如果已经运行的容器修改了现有的文件，那么会从读写层下面的只读层复制到读写层，改文件只读层依然存在，只是已经被读写层中该文件的复制副本所隐藏。当删除docker容器，或重新启动时，之前的修改将丢失。在docker中，只读层及在顶部的读写层组合被称为Union File System（联合文件系统）


# check container

Get its ip

```bash
$ sudo docker ps
[sudo] password for alex: 
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS              PORTS               NAMES
181f88bd0f2a        redis               "docker-entrypoint.s…"   15 seconds ago      Up 13 seconds       6379/tcp            upbeat_hopper
$ sudo docker inspect 181f88bd0f2a

        "Image": "sha256:f9b9909726890b00d2098081642edf32e5211b7ab53563929a47f250bcdc1d7c",
        "ResolvConfPath": "/var/lib/docker/containers/181f88bd0f2ad5074a3911d1b34b37c267efbf3e351e8b6cccd455055ee8ecab/resolv.conf",
        "HostnamePath": "/var/lib/docker/containers/181f88bd0f2ad5074a3911d1b34b37c267efbf3e351e8b6cccd455055ee8ecab/hostname",
        "HostsPath": "/var/lib/docker/containers/181f88bd0f2ad5074a3911d1b34b37c267efbf3e351e8b6cccd455055ee8ecab/hosts",
        "LogPath": "/var/lib/docker/containers/181f88bd0f2ad5074a3911d1b34b37c267efbf3e351e8b6cccd455055ee8ecab/181f88bd0f2ad5074a3911d1b34b37c267efbf3e351e8b6cccd455055ee8ecab-json.log",
        "Name": "/upbeat_hopper",

        "Mounts": [
            {
                "Type": "volume",
                "Name": "9d3aa4440b7d8cbfa4db7eadf24c4c8409fe094249fe86033d53319789c701ca",
                "Source": "/var/lib/docker/volumes/9d3aa4440b7d8cbfa4db7eadf24c4c8409fe094249fe86033d53319789c701ca/_data",
                "Destination": "/data",
                "Driver": "local",
                "Mode": "",
                "RW": true,
                "Propagation": ""
            }
        ],

        "NetworkSettings": {
            "Bridge": "",
            "SandboxID": "e932c5dca4ad7e6597ddc3e1ef59a33c4c28cfcef42e0d451eda55be0d4233ba",
            "HairpinMode": false,
            "LinkLocalIPv6Address": "",
            "LinkLocalIPv6PrefixLen": 0,
            "Ports": {
                "6379/tcp": null
            },
            "SandboxKey": "/var/run/docker/netns/e932c5dca4ad",
            "SecondaryIPAddresses": null,
            "SecondaryIPv6Addresses": null,
            "EndpointID": "662281a3185431b03cc5f7d3e620621d85f99f63ae9e83e951a70824faf18148",
            "Gateway": "172.17.0.1",
            "GlobalIPv6Address": "",
            "GlobalIPv6PrefixLen": 0,
            "IPAddress": "172.17.0.2",
            "IPPrefixLen": 16,
            "IPv6Gateway": "",
            "MacAddress": "02:42:ac:11:00:02",
            "Networks": {
                "bridge": {
                    "IPAMConfig": null,
                    "Links": null,
                    "Aliases": null,
                    "NetworkID": "4f704f69d88c7310b2ed454a1c18bb1aebbd8e4bed5c95cfb86617d271ed9c60",
                    "EndpointID": "662281a3185431b03cc5f7d3e620621d85f99f63ae9e83e951a70824faf18148",
                    "Gateway": "172.17.0.1",
                    "IPAddress": "172.17.0.2",
                    "IPPrefixLen": 16,
                    "IPv6Gateway": "",
                    "GlobalIPv6Address": "",
                    "GlobalIPv6PrefixLen": 0,
                    "MacAddress": "02:42:ac:11:00:02",
                    "DriverOpts": null
                }
            }
        }

```
按照 Docker 最佳实践的要求，容器不应该向其存储层内写入任何数据，容器存储层要保持无状态化。所有的文件写入操作，都应该使用 数据卷（Volume）、或者绑定宿主目录，在这些位置的读写会跳过容器存储层，直接对宿主（或网络存储）发生读写，其性能和稳定性更高。

数据卷的生存周期独立于容器，容器消亡，数据卷不会消亡。因此，使用数据卷后，容器删除或者重新运行之后，数据却不会丢失.

即使你不配置，系统还是会给每个Redis container配置了name, volume.

## check network docker related
```bash
$ sudo docker network ls
NETWORK ID          NAME                DRIVER              SCOPE
4f704f69d88c        bridge              bridge              local
8f6c4bc4e467        host                host                local
84a819e11e59        none                null                local

$ ifconfig
docker0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 172.17.0.1  netmask 255.255.0.0  broadcast 172.17.255.255
        inet6 fe80::42:dbff:fe21:505d  prefixlen 64  scopeid 0x20<link>
        ether 02:42:db:21:50:5d  txqueuelen 0  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 65  bytes 8979 (8.9 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0


$ route
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
default         _gateway        0.0.0.0         UG    600    0        0 wlp2s0
link-local      0.0.0.0         255.255.0.0     U     1000   0        0 wlp2s0
172.17.0.0      0.0.0.0         255.255.0.0     U     0      0        0 docker0
192.168.3.0     0.0.0.0         255.255.255.0   U     600    0        0 wlp2s0

$ sudo docker network inspect bridge 

```
Linux 在网络栈中引入网络命名空间，将独立的网络协议栈隔离到不同的命令空间中，彼此间无法通信；Docker 利用这一特性，实现不容器间的网络隔离，并且引入 Veth 设备对来实现在不同网络命名空间的通信。Linux 系统包含一个完整的路由功能，当 IP 层在处理数据发送或转发的时候，会使用路由表来决定发往哪里。

本例中docker为container创建了172.17.0.0/16 这个网段。

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
id 999 应该是比较特殊。容器的实质是进程，但与直接在宿主执行的进程不同，容器进程运行于属于自己的独立的 命名空间。因此容器可以拥有自己的 root文件系统、自己的网络配置、自己的进程空间，甚至自己的用户 ID 空间。容器内的进程是运行在一个隔离的环境里，使用起来，就好像是在一个独立于宿主的系统下操作一样。

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

# sudo issue
saving time of "sudo" typing.

```bash
$ cat /etc/group
alex:x:1000:
sambashare:x:126:alex
docker:x:127:
```
可以看到新增的group:docker.

```bash
$ id
uid=1000(alex) gid=1000(alex) groups=1000(alex),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),116(lpadmin),126(sambashare)

$ sudo gpasswd  cdrom -d alex
Removing user alex from group cdrom

$ sudo gpasswd  docker -a alex
Adding user alex to group docker

$ id
uid=1000(alex) gid=1000(alex) groups=1000(alex),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),116(lpadmin),126(sambashare)
$ 

```
after reboot

```bash
$ id
uid=1000(alex) gid=1000(alex) groups=1000(alex),4(adm),27(sudo),30(dip),46(plugdev),116(lpadmin),126(sambashare),127(docker)
$ docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
redis               6.0.1               f9b990972689        13 days ago         104MB
redis               latest              f9b990972689        13 days ago         104MB
$ docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
$ docker run -it redis
```


# remove unused container

```bash
$ docker ps -a
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS                      PORTS               NAMES
aaa9a0826e78        redis               "docker-entrypoint.s…"   7 minutes ago       Exited (0) 7 seconds ago                        objective_kowalevski
181f88bd0f2a        redis               "docker-entrypoint.s…"   39 minutes ago      Exited (0) 11 minutes ago                       upbeat_hopper
36e5bd9e0276        redis               "docker-entrypoint.s…"   3 hours ago         Exited (0) 2 hours ago                          thirsty_hugle

$ docker rm aaa9a0826e78
aaa9a0826e78

$ docker rm 181f88bd0f2a
181f88bd0f2a

$ docker ps -a
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS                   PORTS               NAMES
36e5bd9e0276        redis               "docker-entrypoint.s…"   3 hours ago         Exited (0) 2 hours ago                       thirsty_hugle
$ 
```


# attach the redis container

```bash
$ docker ps -a
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS                      PORTS               NAMES
36e5bd9e0276        redis               "docker-entrypoint.s…"   3 hours ago         Exited (0) 22 seconds ago                       thirsty_hugle

$ docker start 36e5bd9e0276
36e5bd9e0276

$ docker attach --help

Usage:	docker attach [OPTIONS] CONTAINER

Attach local standard input, output, and error streams to a running container

Options:
      --detach-keys string   Override the key sequence for detaching a container
      --no-stdin             Do not attach STDIN
      --sig-proxy            Proxy all received signals to the process (default true)

$ docker attach 36e5bd9e0276

^C1:signal-handler (1589514440) Received SIGINT scheduling shutdown...
1:M 15 May 2020 03:47:20.102 # User requested shutdown...
1:M 15 May 2020 03:47:20.102 * Saving the final RDB snapshot before exiting.
1:M 15 May 2020 03:47:20.106 * DB saved on disk
1:M 15 May 2020 03:47:20.106 # Redis is now ready to exit, bye bye...

```
^C 后container就stop了，看来这个container就根本不带shell.

