#!/bin/sh
kubectl delete  configmap redis-config		
kubectl delete -f redis-service.yaml -f redis-deployment.yaml
kubectl delete pvc redis-pv-claim
kubectl delete pv redis-pv-volume
