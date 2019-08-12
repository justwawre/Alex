#need run as root

hostname minikube

#run once is enough
#echo "192.168.0.101 minikube " >> /etc/hosts 
sysctl kernel.hostname=minikube

#cat /proc/swaps
swapoff -a


kubeadm reset

echo 1 > /proc/sys/net/bridge/bridge-nf-call-iptables
setenforce 0

systemctl daemon-reload
systemctl start docker

export FLUENT_UID=0
export KUBERNETES_PROVIDER=local
export MINIKUBE_WANTUPDATENOTIFICATION=false
export MINIKUBE_WANTREPORTERRORPROMPT=false
export MINIKUBE_HOME=$HOME
export CHANGE_MINIKUBE_NONE_USER=true



export KUBECONFIG=$HOME/.kube/config


minikube start --registry-mirror=https://registry.docker-cn.com  --vm-driver=none

#use iptables instead
#kubectl proxy --port=8080 &

# this for loop waits until kubectl can access the api server that Minikube has created
for i in {1..150}; do # timeout for 5 minutes
   kubectl get po &> /dev/null
   if [ $? -ne 1 ]; then
      break
  fi
  sleep 2
done

# kubectl commands are now able to interact with Minikube cluster

