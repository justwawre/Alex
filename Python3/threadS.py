#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import time, threading

# In CPython, the global interpreter lock, or GIL, is
#  a mutex that prevents multiple native threads from executing Python bytecodes at once. 
# This lock is necessary mainly because CPython’s memory management is not thread-safe.
#  (However, since the GIL exists, other features have grown to depend on the guarantees that it enforces.)

balance = 0
lock = threading.Lock()
N    = 100000

def change_it(n):
    global balance
    balance = balance + n
    balance = balance - n

def run_thread(n):
    print('thread %s  deposit/withdraw %d ' % (threading.current_thread().name,n))
    for _ in range(N):
        lock.acquire()
        try:
            change_it(n)
        finally:
            lock.release()
def run_thread_GIL(n):
    for _ in range(N):
        change_it(n)

def test_threadlock():

    start_time = time.time()
    run_thread(5)
    run_thread(8)
    end_time = time.time()
    print("Total time when run as 1 thread : {}".format(end_time - start_time))
    assert balance==0

    t1 = threading.Thread(target=run_thread, args=(5,))
    t2 = threading.Thread(target=run_thread, args=(8,))
    start_time = time.time()
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    end_time = time.time()
    print("Total time when run as 2 thread : {}".format(end_time - start_time))
    assert balance==0

    t1 = threading.Thread(target=run_thread_GIL, args=(5,))
    t2 = threading.Thread(target=run_thread_GIL, args=(8,))
    start_time = time.time()
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    end_time = time.time()
    print("Total time when run as 2 thread GIL : {}".format(end_time - start_time))
    assert balance==0


if __name__ == "__main__":
    test_threadlock()