#!/usr/bin/env python3

#那么一个函数就可以接收另一个函数作为参数，这种函数就称之为高阶函数

# map顾名思义: x--map--->f(x)。;   接收两个参数，一个是函数f，一个是Iterable，返回Iterator
def test_map():
    l = map(lambda s:s.capitalize() , ['adam', 'LISA', 'barT'])
    print('l=>',list(l))

# reduce把一个函数作用在一个序列[x1, x2, x3, ...]上，这个函数必须接收两个参数(x,y) x是以前调用的结果
def test_reduce():
    from functools import reduce
    n = 0 
    def cal_float(x,y):
        nonlocal n
        if y is None:
            n=1
            return x
        if n == 0:
            return 10*x+y
        else:
            r= x+y * (0.1**n)
            n+=1
            return r    

    digits2 = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9,'.':None}
    r = map(lambda s:digits2[s] ,'123.456')
    print(f'=> {reduce(cal_float,r)} ' )   
   
    print(f'{r}=>{list(r)}')   # map object 被引用过后就是empty

    
# 和map()类似，filter()也接收一个函数和一个序列。和map()不同的是，
# filter()把传入的函数依次作用于每个元素，然后根据返回值是True还是False决定保留还是丢弃该元素。
def test_filter():
    def is_palindrome(n): #回数是指从左向右读和从右向左读都是一样的数
        s = str(n)
        return (s == s[::-1])
    r = filter(is_palindrome, range(100,200))
    print("palindrome are:", list(r))    


def test_sorted():
    ll=['123','1','-5']
    l= sorted(ll,key=int)
    print('sorted via int=>',l)
    ll = [('Bob', 75), ('Adam', 92), ('Bart', 66), ('Lisa', 88)]
    l= sorted(ll,key=lambda x:x[0])
    print('sort by name=>',l)
    l= sorted(ll,key=lambda x:x[1],reverse=True)
    print('sort by score=>',l)



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


# 在面向对象（OOP）的设计模式中，decorator被称为装饰模式 
# 简单的来说就是用一个新的对象来替换掉原有的对象，新的对象包含原有的对象  
# 代理模式类似,不过它就是明显的方式调用
from functools import wraps
import time

def log_file(logfile='out.log'):    #log_file 接收参数,而wraps只接收function,所以需要外面包裹一层接收参数,然后作为outer layer变量使用
    def dec(func):
        @wraps(func)
        def logging(*args, **kwargs):
            str = func.__name__ + " was called"
            with open(logfile, 'a') as opened_file:
                opened_file.write(str + '\n')
            return func(*args, **kwargs)
        return logging
    return dec

def metric(fn):
    @wraps(fn)
    def  dec(*args,**kwargs):
        t0 = time.time()
        r=fn(*args,**kwargs) 
        print(f'{fn.__name__} {args} =>{r} in {time.time()-t0:.4f} s'  )
        return r
    return dec


if __name__ == "__main__":
    test_map()
    test_reduce()
    test_filter()
    test_sorted()

    print('-----------decoration-------')
    test_closure()

    import functools
    @functools.lru_cache() # <1>
    @metric  # <2>
    def fibonacci(n):
        time.sleep(0.0012)   #unit is second

        if n < 2:
            return n
        return fibonacci(n-2) + fibonacci(n-1)

    fibonacci(6)

    @log_file()       #如果不加括号,不报错,但结果完全不对
    def add(x):
        return x + x
    add(3)
  
    #通过设定参数的默认值，可以降低函数调用的难度。而偏函数也可以做到这一点
    from functools import partial
    int2 = partial(int, base=2)
    ss = '1000000'
    print(f'{ss}=>{int2(ss)}')
