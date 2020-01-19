#!/usr/bin/env python3

def basic_type():
    _i = 0
    _i = 0xff00
    _f = 1.23
    _f=  12.3e10
    _s = 'I\'m \"OK\"!'
    _s= r'\\\t\\'
    _b = 1<3<5

# 最早只有127个字符被编码到计算机里，也就是大小写英文字母、数字和一些符号，这个编码表被称为ASCII编码
# 中文显然一个字节是不够的，至少需要两个字节，而且还不能和ASCII编码冲突，所以，中国制定了GB2312编码，用来把中文编进去。\
# Unicode标准最常用的是用两个字节表示一个字符（如果要用到非常偏僻的字符，就需要4个字节）
# UTF-8编码把一个Unicode字符根据不同的数字大小编码成1-6个字节，常用的英文字母被编码成1个字节，汉字通常是3个字节，只有很生僻的字符才会被编码成4-6个字节。
# 如果你要传输的文本包含大量英文字符，用UTF-8编码就能节省空间：

# 对于单个字符的编码，Python提供了ord()函数获取字符的整数表示，chr()函数把编码转换为对应的字符

# 由于Python的字符串类型是str，在内存中以Unicode表示，一个字符对应若干个字节。如果要在网络上传输，或者保存到磁盘上，就需要把str变为以字节为单位的bytes。
# Python对bytes类型的数据用带b前缀的单引号或双引号表示：
# 内部以Unicode表示的str==encode()==>utf/ascii 之类的bytes,bytes==decode()==>str
def test_enconding():

    import sys, locale

    expressions = """
            locale.getpreferredencoding()
            type(my_file)
            my_file.encoding
            sys.stdout.isatty()
            sys.stdout.encoding
            sys.stdin.isatty()
            sys.stdin.encoding
            sys.stderr.isatty()
            sys.stderr.encoding
            sys.getdefaultencoding()
            sys.getfilesystemencoding()
        """

    my_file = open('dummy', 'w')

    for expression in expressions.split():
        value = eval(expression)
        print(f'{expression:>30}-> {value}')

    enc = sys.getdefaultencoding()


    _a = ord('A')
    _a = ord('中')
    _a = chr(66)
    _a = chr(25991)

    _s = '\u4e2d\u6587'
    print('blockchain'.encode(enc), '中文'.encode(enc))

    print(b'blockchain'.decode(enc), b'\xe4\xb8\xad\xe6\x96\x87'.decode(enc))
    _a, _b = len('中文'), len('中文'.encode(enc))
    字符 = "中"
    _a = 字符

def test_Str():

    s = " I LOVE china "
    print("--", s.lstrip(), "--", sep="")
    print("--", s.rstrip(), "--", sep="")
    print("--", s.strip(), "--", sep="")

    #capitalize don't work?
    ss = s.capitalize()
    print("--",ss , "--", sep="")
    print("--", s.title(), "--", sep="")

    print("//".join(reversed("www.python.com".split("."))))
   
    _a,_b = eval('3+4*5-2'), eval('4 + 5')

def trim(s):
    for i,c in enumerate(s):  
        if c != ' ':
            break
    for j,c in enumerate(s[::-1]):#reverse
        if c != ' ':
            break
    if (i+j) >= len(s):
        return('')
    elif j==0:
        return s[i:]
    else:
        return s[i:-j]                


if __name__ == "__main__":
    basic_type()
    test_enconding()
    test_Str()

    print(trim('   -hello'),end='')
    print(trim('    world- '))
    print('-',trim('    '),'-',sep='')