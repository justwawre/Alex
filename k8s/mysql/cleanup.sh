kubectl delete secret mysql-pass
kubectl delete deployment -l app=mysql-app
kubectl delete service -l app=mysql-app
kubectl delete pvc mysql-pv-claim
#kubectl delete pv mysql-pv-volume



