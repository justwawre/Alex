#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import os

def run_proc(name):
    print('child process %s (%s)...' % (name, os.getpid()))

def test_fork():
    # Only works on Unix/Linux/Mac:
    pid = os.fork()
    if pid == 0:
        run_proc('test_fork')
        os._exit(0)           #否则继续往下执行了        
    else:
        print('I (%s) just created a child process (%s).' % (os.getpid(), pid))
        os.waitpid(pid,0)      #不能先结束,否则child process 成孤儿进程
    print('test_fork end here')

def test_multi_process():
    # CPython mulit thread 有GIL限制所以效率不高;但multiprocessing 下 process有各自独立的GIL锁
    from multiprocessing import Process  

    p = Process(target=run_proc, args=('test_multi_process',))
    p.start()
    print('parent process of test_multi_process-----' )
    p.join()
    print('Child process end.')

def test_pool():
    from multiprocessing import Pool
    p = Pool(3)
    for i in range(5):
        p.apply_async(run_proc, args=(i,))
    p.close()
    p.join()
    print('test_pool:all subprocesses done...')

def test_subprocess():
    import subprocess
    r = subprocess.call(['nslookup', 'www.python.org'])
    print('Exit code:', r)

    print('$ nslookup')
    p = subprocess.Popen(['nslookup'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, _err = p.communicate(b'set q=mx\npython.org\nexit\n')
    print(output.decode('utf-8'))
    print('Exit code:', p.returncode)    

from multiprocessing import Process, Queue
def write(q):
    for value in ['A', 'B', 'C']:
        q.put(value)

def read(q):
    while True:
        value = q.get(True)
        print('Get %s from queue.' % value)

def test_queue():
    q = Queue()
    pw = Process(target=write, args=(q,))
    pr = Process(target=read, args=(q,))
    pr.start()
    pw.start()
    pw.join()
    pr.terminate()    # pr进程里是死循环，无法等待其结束，只能强行终止:

if __name__ == "__main__":
    test_fork()
    test_multi_process()
    test_pool()
    test_subprocess()
    test_queue()