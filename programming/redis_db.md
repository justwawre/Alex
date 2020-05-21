# reference 
    book: Mastering Redis
    https://github.com/PacktPublishing/Mastering-Redis
    https://static.packt-cdn.com/downloads/MasteringRedis_ColorImages.pdf

# NoSQL
Traditional database 可以看成是一张表,某一列的数据类型是确定的统一的。
NoSQL database 可以看成是一个JSON文件可以表示的类型。 Redis 数据库对应一MAP。

# 配合使用场景
* rational database，如MySQL 存关键/基本信息，ACID，
* MongoDB 存附加文档，如图片，文档
* Redis 缓存热点数据。

Rational DB的操作命令，也就是SQL命令都是集合命令： 投影，选择，交。
Redis 类似informix 等数据库，访问rowset 的方式，对一某一row, 操作key/value, 它的key 往往来自关系型数据库

# Detail
* [支持的数据类型及操作](redis_datatype.md)
* [持久化](redis_persist.md)

# summary
kV pair 是非常常用的数据结构，过去有很多库用来解析配置文件，也就是将 configuration file --> KV pairs in memory.
Redis 的创新就是
* 从KV pair lib --> service, 
* configuraiton file -->rational database
* 更丰富的value 数据类型


