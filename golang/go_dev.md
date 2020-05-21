# Target

Working with containers/k8s extension

# env
* Ubuntu
* VS Code
* beego framework

# install bee
```bash
~/go/src$ go get github.com/beego/bee
$ cat /etc/profile
export GOPATH=/home/alex/go
export PATH=$PATH:/home/alex/go/bin
```


# dockerize via bee
这个命令可以通过生成Dockerfile文件来实现docker化你的应用。

例子:
生成一个以1.6.4版本Go环境为基础镜像的Dockerfile,并暴露9000端口:
```
$ bee dockerize -image="library/golang:1.6.4" -expose=9000
```



# Ref
* [VSCode guide](https://code.visualstudio.com/docs/containers/overview)
* [beego](https://beego.me/docs/intro/)
