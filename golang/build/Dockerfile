FROM golang
MAINTAINER Alex

#复制文件指令。它有两个参数<source>和<destination>。destination是容器内的路径。source可以是URL或者是启动配置上下文中的一个文件。
#ADD build.sh /build.sh

#RUN指令会在新创建的镜像上添加新layer
RUN go get -u github.com/astaxie/beego
RUN go get -u github.com/beego/bee

#设置环境变量。它们使用键值对，增加运行程序的灵活性
#ENV PATH $PATH:$GOPATH/bin


#WORKDIR：指定RUN、CMD与ENTRYPOINT命令的工作目录

#USER：镜像运行时，设置一个UID

#VOLUME：授权访问从容器内到主机上的目录 

#EXPOSE：指定容器在运行时监听的端口
EXPOSE 8080

#CMD：提供了容器默认的执行命令。 Dockerfile只允许使用一次CMD指令。 使用多个CMD会抵消之前所有的指令，只有最后一个指令生效。 
CMD ["bee", "run"]