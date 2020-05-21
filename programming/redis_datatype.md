# string
相当于excel中的表格，可以存任何转化成string的数据类型。扩展操作： 设置数据有效时间
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
# hash
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
# list
多个数据，用双向链表表示，有序。 扩展操作： blpop/brpop  (Alex: block & wait some time, 类似select()操作)
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
# set
内部储存为hash表的key部分。扩展操作： 标准的集合运算sunion/sinter/sdiff
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
# sorted_set
set 中增加 score 属性 
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
> zrevrank height mary
(integer) 2
> zrank height mary
(integer) 0

```
