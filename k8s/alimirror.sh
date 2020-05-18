#!/bin/sh
for imageName in $(cat images.txt) 
do
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/${imageName}
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/$imageName k8s.gcr.io/${imageName}
    docker rmi registry.cn-hangzhou.aliyuncs.com/google_containers/${imageName}
    docker save k8s.gcr.io/${imageName} > ${imageName}.tar
    microk8s.ctr image import ${imageName}.tar
done