# install

1. https://snapcraft.io/microk8s

2. https://www.jianshu.com/p/02fd2540fab2




# usage

https://ubuntu.com/tutorials/install-a-local-kubernetes-with-microk8s

```bash
$  microk8s kubectl get nodes
$  microk8s kubectl get services  //get cluster ip & port, e.g. https://10.152.183.1:443/

$ microk8s.enable dns dashboard storage ingress

$ microk8s.status
$ microk8s.kubectl get all --all-namespaces
$ microk8s kubectl get pods --namespace=kube-system -o json |grep messag  //找出missing images
    k8s.gcr.io/heapster-amd64:v1.5.2
    k8s.gcr.io/heapster-grafana-amd64:v4.4.3
    k8s.gcr.io/heapster-influxdb-amd64:v1.3.3


$ token=$(kubectl -n kube-system get secret | grep default-token | cut -d " " -f1)
$ microk8s.kubectl -n kube-system describe secret $token


$ microk8s kubectl create deployment kubernetes-bootcamp --image=s7799653/google-samples/kubernetes-bootcamp:v1





```
# May 18


microk8s不通过虚拟机但与主机隔离方式，快速轻巧安装Kubernetes。通过在单个快照包中打包Kubernetes，Docker.io，iptables和CNI的所有上游二进制文件来实现此隔离。 snap包是一个应用程序容器 - 您可以将其想象为Docker容器的轻量级版本。它使用了许多相同的底层技术进行隔离，而没有网络隔离的所有开销。最终结果是一种超越任何一个发行版的包格式，因为快照可以安装在大多数Linux操作系统上，同时还利用原子更新，升级失败回滚以及来自用户主机的软件限制级别等功能。

## install

``` bash
sudo snap remove microk8s
sudo snap install microk8s --classic --channel=1.12/stable
microk8s.start
sudo snap alias microk8s.kubectl kubectl
kubectl cluster-info
kubectl get nodes
kubectl get pods
microk8s.docker ps
microk8s.status

```
## gfw issue
里并没有安装最新版本，为什么呢？因为新版没有microk8s.docker命令。如果没有这个命令。必须使用代理方式，下载镜像！

``` bash
./gfw.sh
```
reference:

https://ieevee.com/tech/2017/04/07/k8s-mirror.html
https://docs.docker.com/docker-hub/builds/

note: 

无需翻墙即可获取墙外镜像的小技巧。利用docker hub的自动构建。从github获取dockerfile来构建镜像。
如 mirrorgooglecontainers/k8s-dns-sidecar-amd64:1.14.7 中的 mirrorgooglecontainers 就是 docker hub id.


## startup
```bash
microk8s.enable dashboard dns
kubectl get pods -n kube-system
kubectl delete pod <pod name> -n kube-system --grace-period=0 --force
kubectl cluster-info
kubectl get services // get the url: https://10.152.183.1:443
```

## set acess key
```bash
token=$(kubectl -n kube-system get secret | grep default-token | cut -d " " -f1)
kubectl -n kube-system describe secret $token
```


