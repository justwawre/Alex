# install

1. https://snapcraft.io/microk8s

2. https://www.jianshu.com/p/02fd2540fab2

3. cmd


```bash
$  microk8s kubectl get nodes
$  microk8s kubectl get services  //get cluster ip & port, e.g. https://10.152.183.1:443/

$ microk8s.enable dns dashboard

$ microk8s status
microk8s is running
addons:
dashboard: enabled
dns: enabled
cilium: disabled
fluentd: disabled
gpu: disabled
helm: disabled
helm3: disabled
host-access: disabled
ingress: disabled
istio: disabled
jaeger: disabled
knative: disabled
kubeflow: disabled
linkerd: disabled
metallb: disabled
metrics-server: disabled
prometheus: disabled
rbac: disabled
registry: disabled
storage: disabled

$ microk8s kubectl get po -n kube-system
NAME                                              READY   STATUS              RESTARTS   AGE
coredns-588fd544bf-j9fw6                          1/1     Running             0          48m
dashboard-metrics-scraper-db65b9c6f-psvkz         0/1     ImagePullBackOff    0          48m
heapster-v1.5.2-58fdbb6f4d-ldjzh                  0/4     ContainerCreating   0          48m
kubernetes-dashboard-67765b55f5-h2wd4             0/1     ErrImagePull        0          48m
monitoring-influxdb-grafana-v4-6dc675bf8c-2nsdn   0/2     ErrImagePull        0          48m

$ ~$ microk8s kubectl edit svc -n kube-system  kubernetes-dashboard

$ $ microk8s kubectl config view
users:
- name: admin
  user:
    password: ZWswQ3oraVhLN0FHeXI4NDM1TnF1ejlsa1dKUGV0ditpYWgzdFR2VmpWOD0K
    username: admin
```



note: 

无需翻墙即可获取墙外镜像的小技巧。利用docker hub的自动构建。从github获取dockerfile来构建镜像。
如 s7799653/heapster-amd64:v1.5.2 中的 s7799653 就是 docker hub id.


