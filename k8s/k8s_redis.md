# env
microk8 is ready

# try the config/script used before

```bash
$ kubectl run redis --image=docker.io/redis 
pod/redis created

$ kubectl get pods -A
NAMESPACE     NAME                                      READY   STATUS              RESTARTS   AGE
default       redis                                     0/1     ContainerCreating   0          23s

$ ./create_map.sh 
configmap/redis-config created

$ kubectl create -f redis-deployment.yaml 
deployment.apps/redis created

```

# access redis inside k8s
```bash

```