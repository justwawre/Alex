# Target
Save time to build up env needed for SW Dev & test. And whole team can share the same env.

# Preparation
* create subfolder app: Here is source of files which be copied to the building docker image.
* create Dockerfile

# Build
```bash
$ docker build -t hello:1.0 .
Sending build context to Docker daemon  9.728kB
Step 1/6 : FROM golang
 ---> 7e5e8028e8ec
Step 2/6 : MAINTAINER Alex
 ---> Using cache
 ---> 6b9ec9ca5cc2
Step 3/6 : RUN go get -u github.com/astaxie/beego
 ---> Using cache
 ---> 77867e2948a0
Step 4/6 : RUN go get -u github.com/beego/bee
 ---> Using cache
 ---> 6cb2ad5a16c7
Step 5/6 : EXPOSE 8080
 ---> Running in 5be7522b1097
Removing intermediate container 5be7522b1097
 ---> 2820abf0aea2
Step 6/6 : CMD ["bee", "run"]
 ---> Running in f6ffbb68333b
Removing intermediate container f6ffbb68333b
 ---> 786010540979
Successfully built 786010540979
Successfully tagged hello:1.0
```
# Check the image
```bash
$ docker images
REPOSITORY                                             TAG                 IMAGE ID            CREATED             SIZE
hello                                                  1.0                 786010540979        42 seconds ago      867MB
redis                                                  latest              987b78fc9e38        2 days ago          104MB
golang                                                 latest              7e5e8028e8ec        4 days ago          810MB
mysql                                                  8.0.20              94dff5fab37f        5 days ago          541MB

```
# Run
```bash
$ docker run -it --rm --name hello -p 8080:8080 \
>    -v /home/alex/base/Alex/golang/app:/go/src/app -w /go/src/app hello:1.0
______
| ___ \
| |_/ /  ___   ___
| ___ \ / _ \ / _ \
| |_/ /|  __/|  __/
\____/  \___| \___| v1.10.0
2020/05/20 15:20:43 INFO     ▶ 0001 Using 'app' as 'appname'
2020/05/20 15:20:43 INFO     ▶ 0002 Initializing watcher...
app
2020/05/20 15:20:47 SUCCESS  ▶ 0003 Built Successfully!
2020/05/20 15:20:47 INFO     ▶ 0004 Restarting 'app'...
2020/05/20 15:20:47 SUCCESS  ▶ 0005 './app' is running...
2020/05/20 15:20:47.089 [I] [asm_amd64.s:1373]  http server Running on http://:8080
2020/05/20 15:21:11.545 [D] [server.go:2807]  |     172.17.0.1| 404 |    356.852µs| nomatch| GET      /  
2020/05/20 15:21:11.685 [D] [server.go:2807]  |     172.17.0.1| 404 |    300.755µs| nomatch| GET      /favicon.ico
```
# Dev & build

因为启动container时用了 -v 的映射，所以本地修改的程序/其他文件，container就会自动重新build.
```
2020/05/20 15:30:54 SUCCESS  ▶ 0006 Built Successfully!
2020/05/20 15:30:54 INFO     ▶ 0007 Restarting 'app'...
2020/05/20 15:30:54 SUCCESS  ▶ 0008 './app' is running...
2020/05/20 15:30:54.600 [I] [asm_amd64.s:1373]  http server Running on http://:8080
```

# Test
Now app can be accessed via:  http://localhost:8080/sum/4/5


