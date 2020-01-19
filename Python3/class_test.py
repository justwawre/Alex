#!/usr/bin/env python3

def test_inherit():     #多重继承
    class Woman:
        #in C++ class, self needn't mention so many times
        def speakself(self):
            print( "My length is:",self.__length)
        def setHeight(self, n):
            self.__length = n                     #实例的变量名如果以__开头, 就变成了一个私有变量（private）

    class Child:

        def __init__(self,parent):                 #变量名类似__xxx__的,是特殊变量，特殊变量是可以直接访问的，
            self.__parent= parent
        def setHeight(self, n):
            self.__length = 'secret'
        def speak2parent(self):
            print(self.__parent,"My length is:", self.__length)

    class Girl(Woman,Child):
        pass
    class NGirl(Child,Woman):
        pass
            
    class NNGirl(Child,Woman):
        def setHeight(self,n):
            Woman.setHeight(self,n)    #这个值就赋给:_Woman__length了
  
    girl = Girl('Adult')
    print('Child ?',isinstance(girl,Child),'Woman?',isinstance(girl,Woman))
    girl.setHeight(1.6)
    girl.speakself()

    girl = NGirl("mama")
    girl.setHeight(1.2)
    girl.speak2parent()

    girl = NNGirl("DADY")
    girl.setHeight(1.1)
    print(girl._Child__parent,end=':')
    girl.speakself()

def test_empty_class():
    class Employee:
        dept='N/A'
        pass
    john = Employee()  
    john.name = 'John Doe'                 #变量名并不需要在Class中事先定义
    print(john.name,':', john.dept)
    john.dept = 'lab'
    print(john.name,':', john.dept)
    del john.dept
    print(john.name,':', john.dept)


def test_slot():
    # 使用__slots__要注意，__slots__定义的属性仅对当前类实例起作用，对继承的子类是不起作用的：
    # 除非在子类中也定义__slots__，这样，子类实例允许定义的属性就是自身的__slots__加上父类的__slots__。

    class Employee:
        __slots__ = ('name', 'dept') # 用tuple定义允许动态绑定的属性名称
    john = Employee()  
    john.name = 'John Doe'                 #变量名并不需要在Class中事先定义
    try:
        john.age= 30
    except Exception as e:
        print(john.name,e)

def test_property():
    class Screen(object):     # 实际就是decorator 只定义getter方法，不定义setter方法就是一个只读属性：
        _width = 200
        @property
        def width(self):
            return self._width
        @property
        def height(self):
            return self._height

        @height.setter
        def height(self, h):
            self._height =h

    s = Screen()
    s.resolution = 'h'
    try:
        s.width      = 100    
    except :
        pass
    s.height     = 200  
    print('test_property()=>',s.width,s.height,s.resolution)

def test_special_method():
    class Fib(object):
        def __init__(self):
            self.a, self.b = 0, 1 # 初始化两个计数器a，b
        def __iter__(self):
            return self # 实例本身就是迭代对象，故返回自己

        def __next__(self):
            self.a, self.b = self.b, self.a + self.b # 计算下一个值
            if self.a > 100: # 退出循环的条件
                raise StopIteration()
            return self.a 

        def __getitem__(self, n):
            if isinstance(n, int):
                a, b = 1, 1
                for x in range(n):
                    a, b = b, a + b
                return a
            if isinstance(n, slice):
                start = n.start
                stop = n.stop
                if start is None:
                    start = 0
                a, b = 1, 1
                L = []
                for x in range(stop):
                    if x >= start:
                        L.append(a)
                    a, b = b, a + b
                return L   

        def __getattr__(self, attr):
            if attr=='a':
                return self.a
            elif attr=='b':
                return lambda :self.b
            else:
                raise AttributeError(' no attribute \'%s\'' % attr)    

        def __call__(self,name):  #把对象看成函数，
            print('hi %s, class fib is for demo special mehtod' % name)                                 
    
    for n in Fib():
        print(n,end=',') 
    print('<=fib')

    f = Fib()
    print(f[0])
    print(f[5])
    print(f[0:5])
    print(f[:10])  
    print(f.a,f.b,'<==fib') 
    f('alex')        

def test_Enum():
    
    from enum import Enum,unique
    @unique
    class Gender(Enum):
        Male = 0
        Female = 1

    class Student(object):
        def __init__(self, name, gender):
            self.name = name
            self.gender = gender

    bart = Student('Bart', Gender.Male)
    if bart.gender == Gender.Male:
        print('test_Enum通过!')
    else:
        print('test_Enum失败!')

def test_vector():
    from math import hypot
    class Vector:
        def __init__(self, x=0, y=0):
            self.x = x
            self.y = y

        def __repr__(self):
            return 'Vector(%r, %r)' % (self.x, self.y)

        def __abs__(self):
            return hypot(self.x, self.y)  # hypot() 返回欧几里德范数 sqrt(x*x + y*y)。

        def __bool__(self):
            return bool(abs(self))

        def __add__(self, other):
            x = self.x + other.x
            y = self.y + other.y
            return Vector(x, y)

        def __mul__(self, scalar):
            return Vector(self.x * scalar, self.y * scalar)

        def __len__(self):  # the speical method mock the __abs__
            amp = (self.x**2+self.y**2) ** (1/2)
            amp = int(amp)  # must return int
            return(amp)

        def __neg__(self):
            return(Vector(-self.x, -self.y))

    v1 = Vector(2, 3) *3
    v2 = -Vector(3, 5)
    print(len(v1+v2))


if __name__ == "__main__":
    test_inherit()
    test_empty_class()
    test_slot()
    test_property()
    test_special_method()
    test_Enum()
    test_vector()
