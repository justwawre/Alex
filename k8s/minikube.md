minikube is local Kubernetes, focusing on making it easy to learn and develop for Kubernetes.


# referecne
* [project homepage](https://github.com/kubernetes/minikube)
* [doc](https://minikube.sigs.k8s.io/docs/start/)


# preparation

## generate github personal token
https://help.github.com/en/github/authenticating-to-github/creating-a-personal-access-token-for-the-command-line

copy token, paste to file  ~/TOKEN.txt

## GitHub Docker Registry login
```bash
$ cat ~/TOKEN.txt | docker login https://docker.pkg.github.com -u yc-alex-xu --password-stdin
```

# official procedure
The Docker driver allows you to install Kubernetes into an existing Docker install. On Linux, this does not require virtualization to be enabled.

offical guide: https://minikube.sigs.k8s.io/docs/drivers/docker/

failed , then rise a issue: https://github.com/kubernetes/minikube/issues/8160


# aliyun procedure

https://github.com/AliyunContainerService/minikube
https://github.com/AliyunContainerService/minikube/wiki

https://developer.aliyun.com/mirror/
https://developer.aliyun.com/mirror/kubernetes

https://shrill-pond-3e81.hunsh.workers.dev/
https://githubd.com/#/

aliyun镜像加速器 https://cr.console.aliyun.com/cn-hangzhou/instances/mirrors

Kubernetes 镜像 https://developer.aliyun.com/mirror/kubernetes

minikube start --image-mirror-country cn \
    --iso-url= file:///home/alex/base/mini/minikube-v1.9.0.iso

minikube start --image-mirror-country cn \
    --iso-url=https://kubernetes.oss-cn-hangzhou.aliyuncs.com/minikube/iso/minikube-v1.9.0.iso \
    --registry-mirror=https://r595z7z6.mirror.aliyuncs.com

failed too.

# summary
虽然以前在CentOS也安装过minikube, 各种曲折，难度不在软件本身，而是如何突破GFW的阻碍。
