#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import asyncio

def gen():
    for _i in range(4):  #要多循环一次,否则 g.send(j) StopIteration,原因: 否则执行权无法通过yield 转回 test_yield_send???
        x = yield        # 写成yield _i 或其他值都没区别
        print('gen recived:',x)

def test_yield_send():
    g = gen()
    g.send(None)         # next(g) 同样可以启动g 
    for j in range(3,0,-1):
        g.send(j)
    g.close()

@asyncio.coroutine
def wwwget(host):
    connect = asyncio.open_connection(host, 80)
    #@asyncio.coroutine可以把一个generator标记为coroutine类型，
    # 然后在coroutine内部用yield from调用另一个coroutine(应该是任何func都可以吧???)实现异步操作。
    reader, writer = yield from connect
    header = 'GET / HTTP/1.0\r\nHost: %s\r\n\r\n' % host
    writer.write(header.encode('utf-8'))
    yield from writer.drain()
    while True:
        line = yield from reader.readline()
        if line == b'\r\n':
            break
        print('%s header > %s' % (host, line.decode('utf-8').rstrip()))
    # Ignore the body, close the socket
    writer.close()

def test_asyncio():
    loop = asyncio.get_event_loop()
    tasks = [wwwget(host) for host in ['www.sina.com.cn', 'www.sohu.com', 'www.163.com']]
    loop.run_until_complete(asyncio.wait(tasks))
    loop.close()


#https://docs.python.org/3/library/asyncio-task.html
# The async def type of coroutine was added in Python 3.5, and is recommended if there is no need to support older Python versions.
#the very good example was under fluent Python
if __name__ == "__main__":
    test_yield_send()
    test_asyncio()
