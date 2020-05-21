No time waste on env issue, so as simple as possible

# Install
```bash
$ sudo apt install golang
$ cd 
$ sudo chown alex:alex go
$ go version
go version go1.10.4 linux/amd64
$ cat /etc/profile
$ source /etc/profile
$ env |grep GO
GOPATH=/home/alex/go
$ go env
GOARCH="amd64"
```
now all go code will put under folder ~/go

# The test program 
```bash
src$ vi hello.go
src$ go build hello.go 
src$ ./hello 
hello, world
src$ 
```
# gfw issue
golang 在 github 上建立了一个镜像库，如：https://golang.org/x/net 的镜像库，在GitHub上对应的是https://github.com/golang/net.

```bash
src/golang.org/x$ git clone https://github.com/golang/tools
src/golang.org/x$ git clone https://github.com/golang/lint
```

# github.com/sqs/goreturns failure
```bash
$ go get -v -u github.com/sqs/goreturns
github.com/sqs/goreturns (download)
Fetching https://golang.org/x/tools/imports?go-get=1
https fetch failed: Get https://golang.org/x/tools/imports?go-get=1: dial tcp 216.239.37.1:443: i/o timeout

$ code //restart the vs code via terminal
Installing github.com/sqs/goreturns SUCCEEDED
```
