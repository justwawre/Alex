#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from datetime import datetime

def test_file():
    with open('temp', 'a') as f:  #r w rb a+
        f.write(datetime.now().strftime('%c'))
        f.write('\n')

def test_stringIO():    #StringIO顾名思义就是在内存中读写str
    from io import StringIO

    # write to StringIO:
    f = StringIO()
    f.write('hello world')
    print(f.getvalue())

    # read from StringIO:
    f = StringIO('水面细风生，\n菱歌慢慢声。\n客亭临小市，\n灯火夜妆明。')
    while True:
        s = f.readline()
        if s == '':
            break
        print(s.strip())   

def test_bytesIO():
    from io import BytesIO
    # write to BytesIO:
    f = BytesIO()
    f.write(b'hello')
    f.write(b' ')
    f.write(b'world!')
    print(f.getvalue())

    # read from BytesIO:
    data = '人闲桂花落，夜静春山空。月出惊山鸟，时鸣春涧中。'.encode('utf-8')
    f = BytesIO(data)
    print(f.read())

def test_dir():
    import os

    pwd = os.path.abspath('.')
    print('------------------------------------------------------------')
    print('      Size     Last Modified  Name')

    for f in os.listdir(pwd):
        fsize = os.path.getsize(f)
        mtime = datetime.fromtimestamp(os.path.getmtime(f)).strftime('%c')
        flag = '/' if os.path.isdir(f) else ''
        print('%10d  %s  %s%s' % (fsize, mtime, f, flag))   


def test_serialize():
    import pickle                #Python语言特定的序列化模块是pickle

    d = dict(name='Bob', age=20, score=88)
    data = pickle.dumps(d)
    reborn = pickle.loads(data)
    print(reborn)

def test_JSON():
    import json

    d = dict(name='Bob', age=20, score=88)
    data = json.dumps(d)                  #dumps()方法返回一个str，内容就是标准的JSON。类似的，dump()方法可以直接把JSON写入一个file-like Object。
    reborn = json.loads(data)            #用loads()或者对应的load()方法，前者把JSON的字符串反序列化，后者从file-like Object中读取字符串并反序列化
    print(reborn)

    class Student(object):

        def __init__(self, name, age, score):
            self.name = name
            self.age = age
            self.score = score

        def __str__(self):
            return 'Student object (%s, %s, %s)' % (self.name, self.age, self.score)

    s = Student('Bob', 20, 88)
    #通常class的实例都有一个__dict__属性，它就是一个dict，用来存储实例变量。也有少数例外，比如定义了__slots__的class。
    std_data = json.dumps(s, default=lambda obj: obj.__dict__) 
    rebuild = json.loads(std_data, object_hook=lambda d: Student(d['name'], d['age'], d['score'])) #lamda 调用一构造函数
    print(rebuild)    

if __name__ == "__main__":
    test_file()
    test_stringIO()
    test_bytesIO()
    test_dir()

    test_serialize()
    test_JSON()