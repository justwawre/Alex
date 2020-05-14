# Targets
* practise the Linux/C programming via code reading,including tcp/ip, epoll()
* mastering the Redis as NoSQL DB
* integraed it into k8s env, 
* try Redis as publish/subscribe message system

# standalone configuration 
Redis 6.0 带来的主要变化：
* 提供了众多的新模块（modules）API
* 提供了客户端缓存功能
* 多线程 I/O 能力 (内部的执行逻辑依旧是单线程?)

## install
```
$ uname -a
Linux minipc 5.3.0-46-generic #38~18.04.1-Ubuntu SMP Tue Mar 31 04:17:56 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux

$ gcc -v

gcc version 7.5.0 (Ubuntu 7.5.0-3ubuntu1~18.04) 

$ wget http://download.redis.io/releases/redis-6.0.1.tar.gz
$ tar xzf redis-6.0.1.tar.gz
$ cd redis-6.0.1
$ make

```
## start server
```
$ src/redis-server
```
## test
```
$ src/redis-cli
127.0.0.1:6379> set name alex
OK
127.0.0.1:6379> get name
"alex"
127.0.0.1:6379> 
```

# As NoSQL databse
[NoSQL databse](DB.md)

# Programming with Redis
[Programming](Programming.md)

# Source code reading
[source](.md)

# access redis in docker/k8s
[redis in docker](../k8s/docker.md)