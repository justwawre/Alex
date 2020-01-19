#!/usr/bin/env python3

def testArithem():
    a=2
    b=3
    a+=b
    print("a:",a,"b:",b,"a/b :", a/b,"a%b :", a%b,"a**b:", a**b,"a//b :", a//b)
    _a, _b, _c = 10, 20, 30
    _a, _b, _c = [1, 2, 3]
    a, b, _c = [i*3 for i in range(3)]
    a, b = b, a
    _a, *_b, _c = [1, 2, 3, 4, 5]
    print("10<=10<=20 is", 0 <= 10<= 20)
  
def testAddress():
    a,b=10,20
    print("a:",a,"b:",b,"id(a)==id(b):",id(a)==id(b))

    a=b=10
    print("a:",a,"b:",b,"id(a)==id(b):",id(a)==id(b))  #python 3, the int become object too

    a,b=30,30
    print("a:",a,"b:",b,"id(a)==id(b):",id(a)==id(b))  #python 3, the int become object too
   
    a = b = "same string"
    print("a:",a,"b:",b,"id(a)==id(b):",id(a)==id(b))
   
    a= "duplicate string"
    b= "duplicate string"
    print("a:",a,"b:",b,"id(a)==id(b):",id(a)==id(b))  #python 3 so smart?
  
    a= "I am a "
    b= "I am b"
    print("a:",a,"b:",b,"id(a)==id(b):",id(a)==id(b))  


def testLogic():
    
    print("4!=3", 4!=3)
    print(" 4>3 and 4<2 is",  4>3 and 4<2)
    print(" 4>3 or 4<2 is",  4>3 or 4<2)
    print(" 4>3 and not 4<2 is",  4>3 and not 4<2)
    print(" 4>=3 and not 4<=2 is",  4>=3 and not 4<=2)

    string2, string3 = 'Trondheim', 'Hammer Dance'
    s = '' or string2 or string3  #or 运算符是短路操作
    print(s,"==",string2)

def test3op():
    cp = 'zh'
    name ="John" if cp=="en"  else "张三"
    print("name is", name)

def test_object_type():
    print(type(3),type(3.0),type('blockchain'),isinstance(3.0,float))



if __name__ == "__main__":
    testArithem()
    testAddress()
    testLogic()
    test3op()
    test_object_type()

