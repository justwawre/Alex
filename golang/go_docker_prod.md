# Deploy product as an image
It a little different from [Dev env](go_docker.md), since it needn't image to recompilation with code change. 

```bash
$ docker build -t hello_prod:1.0 .
Sending build context to Docker daemon  25.29MB
Step 1/8 : FROM golang
 ---> 7e5e8028e8ec
Step 2/8 : LABEL maintainer="xuyc@sina.com"
 ---> Using cache
 ---> db54e061b9b8
Step 3/8 : RUN go get -u github.com/astaxie/beego
 ---> Using cache
 ---> 3c957998ed9f
Step 4/8 : RUN go get -u github.com/beego/bee
 ---> Using cache
 ---> fb6cebfb5579
Step 5/8 : ADD app  /go/src/app
 ---> 55b3a2fde6c9
Step 6/8 : WORKDIR /go/src/app
 ---> Running in cc194a8b8f6d
Removing intermediate container cc194a8b8f6d
 ---> 08875fddfabe
Step 7/8 : EXPOSE 8080
 ---> Running in 0889fc04cd87
Removing intermediate container 0889fc04cd87
 ---> c9135137f7c8
Step 8/8 : CMD ["bee", "run"]
 ---> Running in 50e1d385c172
Removing intermediate container 50e1d385c172
 ---> 949d638f93a9
Successfully built 949d638f93a9
Successfully tagged hello_prod:1.0
alex@minipc:~/go$ script/deploy/run.sh 
______
| ___ \
| |_/ /  ___   ___
| ___ \ / _ \ / _ \
| |_/ /|  __/|  __/
\____/  \___| \___| v1.10.0
2020/05/21 07:33:48 INFO     ▶ 0001 Using 'app' as 'appname'
2020/05/21 07:33:48 INFO     ▶ 0002 Initializing watcher...
app
2020/05/21 07:33:51 SUCCESS  ▶ 0003 Built Successfully!
2020/05/21 07:33:51 INFO     ▶ 0004 Restarting 'app'...
2020/05/21 07:33:51 SUCCESS  ▶ 0005 './app' is running...
2020/05/21 07:33:51.408 [I] [asm_amd64.s:1373]  http server Running on http://:8080

```

# CI/CD
No time now.
* [publish docker image](https://help.github.com/cn/actions/language-and-framework-guides/publishing-docker-images)
* [用 GitHub Action 构建一套 CI/CD 系统](https://cloud.tencent.com/developer/article/1624786)

