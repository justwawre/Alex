minikube is local Kubernetes, focusing on making it easy to learn and develop for Kubernetes.

All you need is Docker (or similarly compatible) container or a Virtual Machine environment, and Kubernetes is a single command away: minikube start

# referecne
* [project homepage](https://github.com/kubernetes/minikube)
* [doc](https://minikube.sigs.k8s.io/docs/start/)


# preparation
authenticate with docker id
```bash
$ docker login
Login with your Docker ID to push and pull images from Docker Hub. If you don't have a Docker ID, head over to https://hub.docker.com to create one.
Username: justware
Password: 
Login Succeeded\

$  docker login https://docker.pkg.github.com
Username: yc-alex-xu
Password: 
WARNING! Your password will be stored unencrypted in /home/alex/.docker/config.json.
Configure a credential helper to remove this warning. See
https://docs.docker.com/engine/reference/commandline/login/#credentials-store

Login Succeeded

```

# install over Docker driver
The Docker driver allows you to install Kubernetes into an existing Docker install. On Linux, this does not require virtualization to be enabled.

offical guide: https://minikube.sigs.k8s.io/docs/drivers/docker/

```bash
$ curl -LO https://storage.googleapis.com/minikube/releases/latest/minikube_latest_amd64.deb

$ sudo dpkg -i minikube_latest_amd64.deb
Selecting previously unselected package minikube.
(Reading database ... 188735 files and directories currently installed.)
Preparing to unpack minikube_latest_amd64.deb ...
Unpacking minikube (1.10.1) ...
Setting up minikube (1.10.1) ...

$ minikube start --driver=docker



```

