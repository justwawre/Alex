#kubectl delete secret mysql-pass
#kubectl delete deployment -l app=mysql
#kubectl delete service -l app=mysql
#kubectl delete pvc -l app=mysql

kubectl delete deployment,svc mysql
kubectl delete pvc mysql-pv-claim
kubectl delete pv mysql-pv-volume



