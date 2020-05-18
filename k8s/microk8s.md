
microk8s不通过虚拟机但与主机隔离方式，快速轻巧安装Kubernetes。通过在单个快照包中打包Kubernetes，Docker.io，iptables和CNI的所有上游二进制文件来实现此隔离。 snap包是一个应用程序容器 - 您可以将其想象为Docker容器的轻量级版本。它使用了许多相同的底层技术进行隔离，而没有网络隔离的所有开销。最终结果是一种超越任何一个发行版的包格式，因为快照可以安装在大多数Linux操作系统上，同时还利用原子更新，升级失败回滚以及来自用户主机的软件限制级别等功能。


# install

1. https://snapcraft.io/microk8s

2. https://www.jianshu.com/p/02fd2540fab2


# Start

https://ubuntu.com/tutorials/install-a-local-kubernetes-with-microk8s

``` bash
$ sudo snap remove microk8s

sudo snap install microk8s --classic 

sudo usermod -a -G microk8s $USER
sudo chown -f -R $USER ~/.kube
su - $USER

microk8s kubectl get services
alias kubectl='microk8s kubectl'
microk8s enable dns storage
microk8s start

microk8s enable dashboard
microk8s enable ingress
kubectl proxy --accept-hosts=.* --address=0.0.0.0 & 

$ token=$(kubectl -n kube-system get secret | grep default-token | cut -d " " -f1)
$ kubectl -n kube-system describe secret $token

http://10.152.183.1 :8001/api/v1/namespaces/kube-system/services/https:kubernetes-dashboard:/proxy/

```
# daily usage

```bash
$ kubectl version

kubectl cluster-info
kubectl get nodes
kubectl get pods
kubectl get all --all-namespaces


kubectl describe pod --all-namespaces  //any error message?

kubectl delete pod <pod name> -n kube-system --grace-period=0 --force


kubectl cluster-info
kubectl get services // get the url: https://10.152.183.1:443/api/v1/namespaces/kube-system/services/
kubectl get svc -A


```
# gfw issue
[Working with locally built images without a registry](https://microk8s.io/docs/registry-images)

``` bash
./alimirror.sh
```
reference:

https://ieevee.com/tech/2017/04/07/k8s-mirror.html
https://docs.docker.com/docker-hub/builds/

note: 

无需翻墙即可获取墙外镜像的小技巧。利用docker hub的自动构建。从github获取dockerfile来构建镜像。
如 mirrorgooglecontainers/k8s-dns-sidecar-amd64:1.14.7 中的 mirrorgooglecontainers 就是 docker hub id.

# the docker inside the microk8s
```bash
microk8s ctr images lis
microk8s ctr containers list

```
# password

```bash
$ kubectl config view
apiVersion: v1
clusters:
- cluster:
    certificate-authority-data: DATA+OMITTED
    server: https://127.0.0.1:16443
  name: microk8s-cluster
contexts:
- context:
    cluster: microk8s-cluster
    user: admin
  name: microk8s
current-context: microk8s
kind: Config
preferences: {}
users:
- name: admin
  user:
    password: dDV6WnhYS0d1RnBTbmNJeGk0V0JYaUo3WUJiQkNTcWdwSEh4bDFoUjJDMD0K
    username: admin
```


# access dashboard
```bash
$ kubectl get pods -A
NAMESPACE     NAME                                              READY   STATUS              RESTARTS   AGE
kube-system   dashboard-metrics-scraper-db65b9c6f-v79rd         1/1     Running             0          5m24s

$ kubectl describe pod/dashboard-metrics-scraper-db65b9c6f-v79rd --namespace kube-system 

    Port:           8000/TCP
    Host Port:      0/TCP
$ kubectl port-forward --namespace=kube-system --address=0.0.0.0 pod/dashboard-metrics-scraper-db65b9c6f-v79rd 8000:8000

```