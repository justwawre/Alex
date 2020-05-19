# modify the old script written for minikube
主要根据 https://hub.docker.com/_/mysql/  改了下image.

# create the service 

```bash
$ chmod +x *.sh
$ ./cleanup.sh 
$ ./start.sh
```

# check
```bash
$ kubectl describe svc mysql
Name:              mysql
Namespace:         default
Labels:            app=mysql-app
Annotations:       <none>
Selector:          app=mysql-app
Type:              ClusterIP
IP:                10.152.183.57
Port:              <unset>  3306/TCP
TargetPort:        3306/TCP
Endpoints:         <none>
Session Affinity:  None
Events:            <none>
```