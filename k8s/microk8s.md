
 snap包是一个应用程序容器 - 您可以将其想象为Docker容器的轻量级版本。它使用了许多相同的底层技术进行隔离，而没有网络隔离的所有开销。最终结果是一种超越任何一个发行版的包格式，因为快照可以安装在大多数Linux操作系统上，同时还利用原子更新，升级失败回滚以及来自用户主机的软件限制级别等功能。


# install

1. https://snapcraft.io/microk8s

2. https://www.jianshu.com/p/02fd2540fab2


# Start

https://ubuntu.com/tutorials/install-a-local-kubernetes-with-microk8s

``` bash
$ sudo snap remove microk8s
$ sudo snap install microk8s --classic 
$ sudo usermod -a -G microk8s $USER
$ sudo chown -f -R $USER ~/.kube
$ su - $USER

$ microk8s kubectl get services
$ alias kubectl='microk8s kubectl'
$ microk8s enable dns storage
$ microk8s start

```
# dashboard issue

``` bash
$ microk8s enable dashboard
$ kubectl describe pod --all-namespaces  //any error message?
$ kubectl get deploy -A
NAMESPACE     NAME                             READY   UP-TO-DATE   AVAILABLE   AGE
kube-system   dashboard-metrics-scraper        1/1     1            1           70m
kube-system   heapster-v1.5.2                  1/1     1            1           70m
kube-system   hostpath-provisioner             1/1     1            1           15h
kube-system   kubernetes-dashboard             1/1     1            1           70m
kube-system   monitoring-influxdb-grafana-v4   1/1     1            1           70m

$  kubectl edit deploy kubernetes-dashboard -n kube-system //note 1

```
note 1:

发现 image kubernetesui/dashboard:v2.0.0-rc5 pulling 失败,按 https://github.com/kubernetes/dashboard/releases 操作失败。
root cause 还是网络问题。在hosts文件加上：199.232.4.133 raw.githubusercontent.com 解决。

# access dashboard
```bash
$ kubectl proxy --accept-hosts=.* --address=0.0.0.0 & 
[1] 30964
$ token=$(kubectl -n kube-system get secret | grep default-token | cut -d " " -f1)
$ kubectl -n kube-system describe secret $token
```
now can access 

http://127.0.0.1:8001/api/v1/namespaces/kube-system/services/https:kubernetes-dashboard:/proxy/

![dashboard](images/k8s_dashboard.png)

# get image inside gfw 
[Working with locally built images without a registry](https://microk8s.io/docs/registry-images)

``` bash
./alimirror.sh
```
reference:

https://ieevee.com/tech/2017/04/07/k8s-mirror.html
https://docs.docker.com/docker-hub/builds/

further: 

无需翻墙即可获取墙外镜像的小技巧。利用docker hub的自动构建。从github获取dockerfile来构建镜像。
如 mirrorgooglecontainers/k8s-dns-sidecar-amd64:1.14.7 中的 mirrorgooglecontainers 就是 docker hub id.

## the docker system inside the microk8s
```bash
microk8s ctr images lis
microk8s ctr containers list

```
