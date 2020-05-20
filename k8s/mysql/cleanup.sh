#!/bin/sh
kubectl delete -f mysql-secret.yaml 
kubectl delete -f mysql-deployment.yaml
kubectl delete -f mysql-service.yaml 
kubectl delete pvc mysql-pv-claim
kubectl delete pv mysql-pv-volume

