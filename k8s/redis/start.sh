#!/bin/sh
kubectl create configmap redis-config --from-file=redis-config
kubectl create -f redis-service.yaml 
kubectl create -f redis-pvc.yaml
kubectl create -f redis-deployment.yaml

