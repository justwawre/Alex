# install

1. https://snapcraft.io/microk8s

2. https://www.jianshu.com/p/02fd2540fab2


note: 

无需翻墙即可获取墙外镜像的小技巧。利用docker hub的自动构建。从github获取dockerfile来构建镜像。
如 s7799653/heapster-amd64:v1.5.2 中的 s7799653 就是 docker hub id.


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


$ token=$(microk8s.kubectl -n kube-system get secret | grep default-token | cut -d " " -f1)
$ microk8s.kubectl -n kube-system describe secret $token


$ microk8s kubectl create deployment kubernetes-bootcamp --image=s7799653/google-samples/kubernetes-bootcamp:v1





```



