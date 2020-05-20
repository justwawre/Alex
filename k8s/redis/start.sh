#!/bin/sh
kubectl create configmap redis-config --from-file=redis-config
kubectl create -f redis-pv.yaml
kubectl create -f redis-deployment.yaml
kubectl create -f redis-service.yaml 
