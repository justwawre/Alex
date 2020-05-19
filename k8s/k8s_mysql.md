# modify the old script written for minikube
主要根据 https://hub.docker.com/_/mysql/  改了下image.

# create

```bash
$ chmod +x *.sh
$ ./cleanup.sh 
$ ./start.sh
```

# check
```bash
$ kubectl describe svc mysql
Name:              mysql
Namespace:         default
Labels:            app=mysql-app
Annotations:       <none>
Selector:          app=mysql-app
Type:              ClusterIP
IP:                10.152.183.70
Port:              <unset>  3306/TCP
TargetPort:        3306/TCP
Endpoints:         10.1.71.76:3306
Session Affinity:  None
Events:            <none>
```

# exec inside pod
```bash
#  mysql -u root -p
Enter password: 
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 8
Server version: 8.0.20 MySQL Community Server - GPL

Copyright (c) 2000, 2020, Oracle and/or its affiliates. All rights reserved.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> 
```

## insert a table
```sql
mysql> use mysql
mysql> CREATE TABLE Catalog(CatalogId INTEGER PRIMARY KEY,Journal VARCHAR(25), Publisher VARCHAR(25),Edition VARCHAR(25),Title VARCHAR(45),Author VARCHAR(25));
mysql> INSERT INTO Catalog VALUES('1','Oracle Magazine','Oracle Publishing','November December 2013','Engineering as a Service','David A. Kelly');
```
# access MySQL outside k8s

## install client

```bash
$ sudo apt-get install mysql-client
$ sudo apt-get install libmysqlclient-dev //C开发用库，  -lmsqlclient
```

## access
```bash
$ mysql -h 10.1.71.76 -u root -p
Enter password: 
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 12
Server version: 8.0.20 MySQL Community Server - GPL

Copyright (c) 2000, 2020, Oracle and/or its affiliates. All rights reserved.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> 
```

```sql
mysql> use mysql
mysql> SELECT * FROM Catalog;
+-----------+-----------------+-------------------+------------------------+--------------------------+----------------+
| CatalogId | Journal         | Publisher         | Edition                | Title                    | Author         |
+-----------+-----------------+-------------------+------------------------+--------------------------+----------------+
|         1 | Oracle Magazine | Oracle Publishing | November December 2013 | Engineering as a Service | David A. Kelly |
+-----------+-----------------+-------------------+------------------------+--------------------------+----------------+
1 row in set (0.00 sec)
```

