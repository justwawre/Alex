# Dockerfile
create subfolder prod;
create [Dockerfile under prod](prod/Dockerfile)

# build
```bash
$ cd prod
$ docker build -t hello:1.0 .

```
# check the new image
```bash
$ docker images
REPOSITORY                                             TAG                 IMAGE ID            CREATED             SIZE
hello                                                  1.0                 786010540979        42 seconds ago      867MB

```
# run
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
note:
* 因为启动container时用了 -v 的映射，所以本地修改的程序/其他文件，就会影响到container.
e.g. 修改了main.go　后有
```
2020/05/20 15:30:54 SUCCESS  ▶ 0006 Built Successfully!
2020/05/20 15:30:54 INFO     ▶ 0007 Restarting 'app'...
2020/05/20 15:30:54 SUCCESS  ▶ 0008 './app' is running...
2020/05/20 15:30:54.600 [I] [asm_amd64.s:1373]  http server Running on http://:8080
```
Now app can be accessed via:  http://localhost:8080/sum/4/5


