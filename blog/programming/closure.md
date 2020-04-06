闭包（Closure）是词法闭包（Lexical Closure）的简称。对闭包的具体定义有很多种说法,本文也无意学术气息的讨论,只是介绍一下自己的理解.

* Closure 不是所有的语言支持的,如Python,javascript是支持
* Closure 的目的是为了保存状态/历史, Java,C++ 中的对象也有类似的作用
* Closure 有代价的,往往意味着所在的fuction object 得延迟释放内存.

以一个adder函数演示一下实现.
* [C++](adder.cpp)
* [Python](adder.py)

* Closure 会带来安全问题

```
def test_closure():
    def mul():
        fs = []
        for i in range(3):
            def f(x):  # 只要改为 def f(x,i=i) 就是安全的的
                return i*x
            fs.append(f)
        return fs        
    for m in mul():
        print(m(2),'\t',end='',)
    print('<= mul unsafe')
```