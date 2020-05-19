
 snap包是一个应用程序容器 - 您可以将其想象为Docker容器的轻量级版本。它使用了许多相同的底层技术进行隔离，而没有网络隔离的所有开销。最终结果是一种超越任何一个发行版的包格式，因为快照可以安装在大多数Linux操作系统上，同时还利用原子更新，升级失败回滚以及来自用户主机的软件限制级别等功能。


# install

version: 1.18/stable:

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
$ microk8s enable dns
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
token:      eyJhbGciOiJSUzI1NiIsImtpZCI6InBkbmMtRHB5dTlvUWxwSlowYVNSVmhjdkVHLUtadHJ6QUpidUtMMjI0NncifQ.eyJpc3MiOiJrdWJlcm5ldGVzL3NlcnZpY2VhY2NvdW50Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9uYW1lc3BhY2UiOiJrdWJlLXN5c3RlbSIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VjcmV0Lm5hbWUiOiJkZWZhdWx0LXRva2VuLXZtZmM5Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9zZXJ2aWNlLWFjY291bnQubmFtZSI6ImRlZmF1bHQiLCJrdWJlcm5ldGVzLmlvL3NlcnZpY2VhY2NvdW50L3NlcnZpY2UtYWNjb3VudC51aWQiOiJmNTk4YmRhYy0yZTQ0LTQ2NGYtYjlhNS1jZDllMjlhNWQ4NTEiLCJzdWIiOiJzeXN0ZW06c2VydmljZWFjY291bnQ6a3ViZS1zeXN0ZW06ZGVmYXVsdCJ9.FkxA14bZjCf4uEocfRCgQw6igZGWfbqc8JF5RTtUPE6i5tUSYOGO2WGSiC5kHBr62EJjQ1DMZFVqZvRM7M24zNgIiJfXAkdLO2mUkmv2Veo-qPKPnzsVDUjfZW2woYnLv0jpMJNWpfk1PW8tP3dzbjNsFu1JxLp-uO3wgaEhFEJxG4boFGtnRVRNulQx6R__FDSjW4EuHxgxmFJ3fVY55PG5-oQzHW39RrhDx1DUmfIwVe-GuZ4Hdbw3h33SulajDfdSTZKxfdzx1KmXu6PXT4x_lwIvvGbxDyMIfoUROPBZALZcG_8jBUl-6ljEqq9c0zmzpUvmy2Hza5QbQA_8OA
```

now can access: http://127.0.0.1:8001/api/v1/namespaces/kube-system/services/https:kubernetes-dashboard:/proxy/

![dashboard](images/k8s_dashboard.png)

note:
* 这里使用了最简单的PROXY访问模式，高级的可以 enable ingress: 它是使用了ngnix来做 ingress controller for external access.
* authenticate 用的是token, 而不是更复杂的Role-based access control (RBAC)。

# get image behind gfw 
reference:

* [Working with locally built images without a registry](https://microk8s.io/docs/registry-images)
* [guide in Chinese](https://segmentfault.com/a/1190000019534913)

```bash
microk8s ctr images lis
microk8s ctr containers list

```
my script: alimirror.sh

## further 

无需翻墙即可获取墙外镜像的小技巧。利用docker hub的自动构建。从github获取dockerfile来构建镜像。
如 mirrorgooglecontainers/k8s-dns-sidecar-amd64:1.14.7 中的 mirrorgooglecontainers 就是 docker hub id.
https://ieevee.com/tech/2017/04/07/k8s-mirror.html
https://docs.docker.com/docker-hub/builds/


# troubleshooting

https://microk8s.io/docs/troubleshooting

