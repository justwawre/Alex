#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def create_hello_via_type():
    def fn(self, name='world'): # 先定义函数
        print('Hello, %s.' % name)

    Hello = type('Hello', (object,), dict(hello=fn)) # 创建Hello class, 把函数fn绑定到方法名hello上

    h = Hello()   #instance
    h.hello()
    print('type(Hello) =', type(Hello))
    print('type(h) =', type(h), isinstance(h,Hello))

def create_class_via_metaclass():  # metaclass是创建类，所以必须从`type`类型派生：
    class ListMetaclass(type):    #这个metaclass可以给我们自定义的MyList增加一个add方法：
        def __new__(cls, name, bases, attrs):
            attrs['add'] = lambda self, value: self.append(value)   #method 也可以看成 attribute???
            return type.__new__(cls, name, bases, attrs)

    class MyList(list, metaclass=ListMetaclass):    # 指示使用ListMetaclass来定制类, list还是基类吗?
        pass

    L = MyList()
    L.add(1)
    L.add(2)
    L.add(3)
    L.add('END')
    print(L)

if __name__ == "__main__":
    create_hello_via_type()
    create_class_via_metaclass()
