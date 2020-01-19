#!/usr/bin/env python3

def func_basic():
    _a=abs(-10.3)
    _a = str(123)
    _a = bool(1)
    _a = bool(10)
    _a = hex(10)
    _a = bin(10)
    _a = oct(10)

# 在Python中定义函数，可以用必选参数、默认参数、可变参数、关键字参数和命名关键字参数，
# 这5种参数都可以组合使用。但是请注意，参数定义的顺序必须是：必选参数、默认参数、可变参数、命名关键字参数和关键字参数。
# *args是可变参数，args接收的是一个tuple；
# **kw是关键字参数，kw接收的是一个dict。
################# * 把 list/tuple 展开unpack?  ** unpack dict/set???
    def power(x, n=2): 
        s = 1
        while n > 0:
            n = n - 1
            s = s * x
        return s
    print('pow:',power(5),power(2,3))    

    def 平方和(*numbers):  #在函数内部，参数numbers接收到的是一个tuple
        sum = 0
        for n in numbers:
            sum = sum + n * n
        return sum
    print('求和:',平方和(3,4), 平方和(*[3,4]))   #starred expression  to upack the list
    

   """ 
    The *args calling convention is documented in the Expressions reference:
   
    If the syntax *expression appears in the function call, expression must evaluate to an iterable. Elements
     from this iterable are treated as if they were additional positional arguments; if there are positional 
     arguments x1, ..., xN, and expression evaluates to a sequence y1, ..., yM, this is equivalent to a call
      with M+N positional arguments x1, ..., xN, y1, ..., yM.
 """

    def person( **kw): #关键字参数 传一个dict
        if 'city' not in kw:
            print('mandatory param missing')
            return
        for k,v in kw.items():  # 如果只使用kw, 则报 ValueError: too many values to unpack (expected 2)
            print(k,v)
    person(**{'city': 'Beijing', 'job': 'Engineer'})   # so here, still need a ** to upack the dict
    person()  

    def person2( *arg, city='Beijing', job): #命名关键字参数需要一个特殊分隔符*，*后面的参数被视为命名关键字参数。
                                          #如果函数定义中已经有了一个可变参数，后面跟着的命名关键字参数就不再需要一个特殊分隔符*了：
        print( city, job) 
    person2(1,2,3,job='Engineer')    
    person2(city='sh',job='artist')   

def scope_test():
    def do_local():  
        spam = "changed via local assignment "  
    def do_nonlocal():  
        nonlocal spam  
        spam = "changed via nonlocal assignment"  
    def do_global():  
        global spam  
        spam = "changed via global assignment"
        
    spam = "intial value of scope_test"   #itself is not global variable too.
    do_local()  
    print("After  do_local():", spam)
    do_nonlocal()  
    print("After do_nonlocal():", spam)
    do_global()  
    print("After do_global():", spam)



def test_funcpointer():
    """
    example of func pointer
    """
    def hi():
        print( "hi ")
    greet = hi #函数名其实就是指向函数的变量        
    del hi
    try:
        hi()
    except Exception as inst:
        print("Exception", inst)   # __str__ allows args to be printed directly,
    greet()

def test_defaultparams():
    def hi(name="yasoob"):
        #inner func can't access directly
        def greet():
            return "greet"
        def welcome():
            return "welcome "+ name
        if name == "yasoob":
            return greet
        else:
            return welcome

    a = hi()
    print(a())
    a = hi(name="ali")
    print(a())

    def foo(bar=[]):  # foo 也像class 一样有初始化概念,默认参数L的值在定义的时候就被计算出来了,它与func这对象关联
        bar.append("foo")
        print( bar)

    foo()
    foo(["not default value"])
    foo()  # 用id(bar) 单步跟踪发现,到这一步bar的地址是不变的,完全类似c里的static variable

class BingoClass:   
    def __init__(self,items):
        self._items = set(items)    
    def __call__(self): 
        return self._items.pop()
def test_callable():
    bingo= BingoClass('0123456789') # 如果是数字list传进去,就没法得到随机值
    print('bingo=>',bingo(),bingo(),bingo())

def test_keywordpara():
    def f1(a,*b, c=None,**d):      #all kind of params included.
        if a is not None:
            print('a is:',a,end=' ')
        if len(b)>0:
            print('b is:',end=' ')
            for v in b:
                print(v,end=' ')
        print('c is:',c,end=' ')
        print ('d is:',end=' ')
        for k,v in d.items():
            print(k,'=',v,sep='',end=' ')
    f1(1,2,3,e=6,f=7)
    print('<=test_keywordpara')

 

if __name__ == "__main__":

    func_basic()

    spam="global spam"
    scope_test()

    test_funcpointer()
    test_defaultparams()
    test_callable()
    test_keywordpara()
