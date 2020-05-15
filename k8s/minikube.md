minikube is local Kubernetes, focusing on making it easy to learn and develop for Kubernetes.

All you need is Docker (or similarly compatible) container or a Virtual Machine environment, and Kubernetes is a single command away: minikube start

# referecne
* [project homepage](https://github.com/kubernetes/minikube)
* [doc](https://minikube.sigs.k8s.io/docs/start/)


# preparation

## clear images since it will moved to POD
```bash
$ docker image ls
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
redis               6.0.1               f9b990972689        13 days ago         104MB
redis               latest              f9b990972689        13 days ago         104MB
$ docker image rm redis
Untagged: redis:latest
$ docker image ls
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
redis               6.0.1               f9b990972689        13 days ago         104MB
$ docker image rm redis
Error: No such image: redis
$ docker image rm f9b990972689
Untagged: redis:6.0.1
Untagged: redis@sha256:584db7c588cd6d1e0a97bcf67c49016d4f19320b614e07049404bea1d681965e
Deleted: sha256:f9b9909726890b00d2098081642edf32e5211b7ab53563929a47f250bcdc1d7c
Deleted: sha256:7bd7286c61dee81eb691f022d070202ba2840574c460f6dcbc21792f8bf22a7f
Deleted: sha256:ba618723adf8eb28ec3d2b2003442599e3f947b4d66875b80dc6582c61f89a27
Deleted: sha256:cd3c331f934414f0d7a2a3ceb80935a54252dba553f1c1ee823961a07e8d1957
Deleted: sha256:09f9b5d7722b181ae2acd61396c20549afdea66ee31f921850191db5afe6738a
Deleted: sha256:3bd2921d0d3dd52dbcdc462f35b11cb89df901205284b0fea03c19bb8359907a
Deleted: sha256:c2adabaecedbda0af72b153c6499a0555f3a769d52370469d8f6bd6328af9b13
$ docker image ls
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE

```

## generate github personal token: k8s
https://github.com/settings/tokens

assign rigtht:   read:packages Download packages from github package registry

## GitHub Docker Registry login
```bash
$  docker login https://docker.pkg.github.com
Username: <github 用户名>
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

failed as https://github.com/kubernetes/minikube/issues/8160

