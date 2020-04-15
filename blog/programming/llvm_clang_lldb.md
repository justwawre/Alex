recording some usage

## installation
* env: CentOS 7
* version: 6.01
* download src packge from: llvm.org

###  install the CMake 
```
bash-4.2$ cd CMake-3.12.0
bash-4.2# ./bootstrap && make && make install
-- Installing: /usr/local/bin/cmake
-- Installing: /usr/local/bin/ctest
-- Installing: /usr/local/bin/cpack
bash-4.2$ sudo yum install zlib
```    
### build llvm
```
bash-4.2$ mkdir build
bash-4.2$ cd build

bash-4.2# cmake  ../llvm-6.0.1.src
-- Build files have been written to: /home/alex/Downloads/build

bash-4.2# cmake --build .
bash-4.2# cmake --build . --target install

-- Installing: /usr/local/bin/llvm-config
-- Installing: /usr/local/bin/llvm-lto
-- Installing: /usr/local/bin/llvm-profdata
-- Installing: /usr/local/bin/bugpoint
-- Installing: /usr/local/lib/BugpointPasses.so
-- Installing: /usr/local/bin/llvm-dsymutil
-- Installing: /usr/local/bin/llc  
```
### build clang
```
bash-4.2$ mkdir clangbuild
bash-4.2$ cd clangbuild
bash-4.2# cmake ../cfe-6.0.1.src/
bash-4.2# cmake --build .

bash-4.2# cmake --build . --target install
-- Installing: /usr/local/lib/cmake/clang/ClangTargets-noconfig.cmake
-- Installing: /usr/local/lib/cmake/clang/ClangConfig.cmake
```
### build lldb
```    
bash-4.2$ sudo yum install libedit-devel libxml2-devel ncurses-devel python-devel swig

bash-4.2$ mkdir lldb
bash-4.2$ cd lldb
bash-4.2$ 
bash-4.2$ cmake ../lldb-6.0.1.src/
bash-4.2$ cmake --build .
bash-4.2# cmake --build . --target install
CMake Error at scripts/cmake_install.cmake:41 (file):
file INSTALL cannot find "/home/alex/Downloads/lldb/lib/python2.7".

bash-4.2# ls lib64
python2.7
bash-4.2# 
bash-4.2# cp  lib64/python2.7/  lib/ -R
bash-4.2# cmake --build . --target install
```    
### fix the lldb python interface issue
```    
bash-4.2$ lldb
(lldb) script
Traceback (most recent call last):
File "<string>", line 1, in <module>
ImportError: No module named lldb.embedded_interpreter
Traceback (most recent call last):
File "<string>", line 1, in <module> 

bash-4.2$ ls /usr/local/lib/python2.7/site-packages/ -l
total 48
drwxr-xr-x. 5 root root  4096 7月  29 16:31 lldb
-rwxr-xr-x. 1 root root  8840 7月  29 14:56 readline.so
-rw-r--r--. 1 root root 30130 7月  29 16:15 six.py
bash-4.2$ su 
Password: 
bash-4.2# mv /usr/local/lib/python2.7/site-packages/* /usr/lib/python2.7/site-packages/ 
bash-4.2# lldb
(lldb) script
Python Interactive Interpreter. To exit, type 'quit()', 'exit()' or Ctrl-D.
>>> 2+2
4
>>> 
```
## as compiler
* if C, almost same as GCC
* if C++, need link its C++ lib
```bash
clang++ -g -std=c++11 -stdlib=libc++ -lc++abi regex.cpp
```
   
## Using clang/lldb with VS Code
* tested extension: CodeLLDB
* different run/debug configuration file
* M$ C/C++ extension don't work for clang, to disable it when using clang

## common clang tools
* clang
* clang++
* clang-format, even you using the other compiler, VS Code using it to format your C/C++ code
* clang-modernize：change the C++98 code to C++11 codde
* Clang Static Analyzer

## misc
* [a false postive issue and its resolution](false_postive.md)
