# reference 
    book: Mastering Redis
    https://github.com/PacktPublishing/Mastering-Redis
    https://static.packt-cdn.com/downloads/MasteringRedis_ColorImages.pdf

# NoSQL
Traditional database 可以看成是一张表,某一列的数据类型是确定的统一的。
NoSQL database 可以看成是一个JSON文件可以表示的类型。 Redis 数据库对应一MAP。

## 配合使用场景
* rational database，如MySQL 存关键/基本信息，ACID，
* MongoDB 存附加文档，如图片，文档
* Redis 缓存热点数据。


# 操作
关系数据的操作命令，也就是SQL命令都是集合命令： 投影，选择，交。
Redis 类似informix 等数据库，访问rowset 的方式，对一某一row, 操作key/value, 它的key 往往来自关系型数据库

## 支持的数据类型
* string: 相当于excel中的表格，可以存任何转化成string的数据类型。
```
>set user:id:78:blog 22
OK
> get user:id:78:blog
"22"

>set user:id:78 {name:john,blog:22,fans:88}
OK
> get user:id:78
"{name:john,blog:22,fans:88}"

```
扩展操作： 设置数据有效时间

* hash
```
> hmset user name john blog 22 fans 88
OK
> hgetall user
1) "name"
2) "john"
3) "blog"
4) "22"
5) "fans"
6) "88"

> hsetnx user name smith
(integer) 0
> hgetall user
1) "name"
2) "john"
3) "blog"
4) "22"
5) "fans"
6) "88"
> hsetnx user sex male
(integer) 1
> hgetall user
1) "name"
2) "john"
3) "blog"
4) "22"
5) "fans"
6) "88"
7) "sex"
8) "male"

```
* list
多个数据，用双向链表表示，有序
```
> lpush student john smith
(integer) 2
> rpush student mary kate
(integer) 4
> llen student
(integer) 4
> lrange student 0 3
1) "smith"
2) "john"
3) "mary"
4) "kate"
> lpop student
"smith"
> rpop student
"kate"
> lrange student 0 1
1) "john"
2) "mary"

```
扩展操作： blpop/brpop  (Alex: block & wait some time, 类似select()操作)
* set
内部储存为hash表的key部分。
```
> sadd set a b c d e
(integer) 5
> sadd set c
(integer) 0
> SMEMBERS set
1) "a"
2) "c"
3) "d"
4) "b"
5) "e"
> srem set d
(integer) 1
> SMEMBERS set
1) "c"
2) "a"
3) "b"
4) "e"
```
扩展操作： 标准的集合运算sunion/sinter/sdiff

* sorted_set
set 中增加 score 属性 (Alex:类似调度算法中的weight)
```
> zadd height 170 john  180 smith 160 kate 165 mary
(integer) 4
> zrange height 0 -1
1) "kate"
2) "mary"
3) "john"
4) "smith"
> zrange height 0 -1 withscores
1) "kate"
2) "160"
3) "mary"
4) "165"
5) "john"
6) "170"
7) "smith"
8) "180"
> zrem height kate
(integer) 1

```

## summary
kV pair 是非常常用的库，过去有很多库用来解析配置文件，也就是将 configuration file --> KV pairs in memory.
Redis 的创新就是
* 从KV pair lib --> service, 
* configuraiton file -->rational database
* 更丰富的value 数据类型



# 
 Redis master-slave and Redis cluster modes


# 