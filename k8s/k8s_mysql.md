
```bash
$ chmod +x *.sh
$ ./start.sh
secret/mysql-pass created
service/mysql created
persistentvolume/mysql-pv-volume created
persistentvolumeclaim/mysql-pv-claim created
deployment.apps/mysql created

$ kubectl delete deployment mysql


```
