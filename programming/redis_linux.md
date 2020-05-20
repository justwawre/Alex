# install
```bash
$ uname -a
Linux minipc 5.3.0-46-generic #38~18.04.1-Ubuntu SMP Tue Mar 31 04:17:56 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux

$ gcc -v

gcc version 7.5.0 (Ubuntu 7.5.0-3ubuntu1~18.04) 

$ wget http://download.redis.io/releases/redis-6.0.1.tar.gz
$ tar xzf redis-6.0.1.tar.gz
$ cd redis-6.0.1
$ make

```
# start server
```bash
$ src/redis-server
```
# client
```bash
$ src/redis-cli
127.0.0.1:6379> set name alex
OK
127.0.0.1:6379> get name
"alex"
127.0.0.1:6379> 
```