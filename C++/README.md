# intro
Those code is mainly written during reading book  **A Tour of C++  2e**, some come from **https://en.cppreference.com**. 

It serve as C++ syntax/feature review, so all functions was organized as xxx_test(); 

It was developed & test under Linux, using VS Code or gdb.

Most code follow the C++17 standard, to find out the C++ standard supported by your compiler

```
$ g++ -v
gcc version 7.5.0 (Ubuntu 7.5.0-3ubuntu1~18.04) 
$ man g++
    -std=
    c++1z
            The next revision of the ISO C++ standard, tentatively planned for 2017.  Support is highly experimental, and will almost certainly change in incompatible ways in future releases.


````

#  dump the class layout

```
$ g++ -fdump-class-hierarch Container.h  //the file where class is defined
$ cat Container.h.002t.class 

```

