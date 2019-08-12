kubectl create -f mysql-secret.yaml 
kubectl create -f service.yaml 
kubectl create -f mysql-pv.yaml
kubectl create -f deployment.yaml

