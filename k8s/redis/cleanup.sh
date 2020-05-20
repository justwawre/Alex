#!/bin/sh
kubectl delete  configmap redis-config		
kubectl delete -f redis-service.yaml  -f redis-pvc.yaml -f redis-deployment.yaml
