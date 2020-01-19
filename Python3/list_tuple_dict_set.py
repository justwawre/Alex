#!/usr/bin/env python3

import sys
import re
import collections


# {'one': 1, 'two': 2, 'three': 3}                                          dict
# {a,b,c}                                                                   set
# -----------------------------------------------------------------------------------------
# (1, 2, (30, 40))                                                          tuple  Immutable
# (1, 2, [30, 40])                                                          tuple including a list
# [28, 14, '28',5, '9', '1', 0, 6, '23', 19]                                list

def test_list():
    a = [66.25, 333, 333, 'a' ]

    print('oringal=>',a,'reversed copy:', end=',')
    print(a[::-1], end=',')
    print(list(reversed(a)), end=',')
    a.reverse()
    print('in place reverse=>',a)    #This method does not return any value but reverse the given object from the list.

    a.insert(2, -1)
    a.append(444)
    print(a,"<=a.insert(2, -1); a.append(444);a.index(333)=>", a.index(333))
    try:
        a.sort()
    except Exception as e:
        print('a.sort()',e)
    a.remove(333)
    a.pop()  # pop the tail, not top as stack!!!
    del a[2:3]
    print(a,'<=a.remove(333); a.pop() ;del a[2:3]')
    _mult = [[1, 2, 3], ['a', 'b', 'c'], 'd', 'e']
    
    squares = [x**2 for x in range(10)]
    print("squares=>", squares)
    from math import pi
    pis = [str(round(pi, i)) for i in range(1, 6)]
    print("PIs:\t", pis)

    some_list = ['a', 'b', 'c', 'b', 'd', 'm', 'n', 'n']
    # 列表生成式
    duplicates = set([x for x in some_list if some_list.count(x) > 1])
    print(some_list, 'duplites=>',duplicates)
    print([m + n for m in 'abc' for n in 'XYZ'])   #双重循环
    print( [k + '=>' + v for k, v in {'x': 'A', 'y': 'B', 'z': 'C' }.items()]  )  #dict

    import random
    score = random.sample(range(101), 5)
    print('avg=',sum(score)/len(score))

    l1 = ['Hello', 'World', 18, 'Apple', None]
    l1 = [s.lower() for s in l1 if isinstance(s,str)]



def list_trick():
    a = [i for i in range(10)]
    print(f"the head of {a} is {a[0]}, tail is {a[-1]}")
    print("skip ", a[::3])
    print("skip with start &end ", a[1:9:3])
    # a[-8] is the end, not inlucded
    print("skip with start &end negative step ", a[:-8:-2])
    print(a[-8])
    a[2:9:1] = {}  # the pos 0,1,9 left
    print(a,'<=a[2:9:1] = {}')
    a = [[[1, 2], [3, 4]], [[5, 6], [7, 8]]]
    _a = [x for l1 in a for l2 in l1 for x in l2]
    print(_a,'<= after expand')
    import os
    #pathlib 可以适应多种OS
    print("当前目录:", [f for f in os.listdir() if os.path.isdir(f)])




def speed_compar():
    import timeit
    TIMES = 10000

    SETUP = """
symbols = '$¢£¥€¤'
def non_ascii(c):
    return c > 127
    """
    def clock(label, cmd):
        res = timeit.repeat(cmd, setup=SETUP, number=TIMES)
        print(label, *(f'{x:.3f}' for x in res))

    clock('listcomp        :', '[ord(s) for s in symbols if ord(s) > 127]')
    clock('listcomp + func :', '[ord(s) for s in symbols if non_ascii(ord(s))]')
    clock('filter + lambda :', 'list(filter(lambda c: c > 127, map(ord, symbols)))')
    clock('filter + func   :', 'list(filter(non_ascii, map(ord, symbols)))')


# tuple,str 与list十分类似
# tuple/str也可以用切片操作，只是操作的结果仍是tuple/str
def common():
    print('--------------common------------')
    s = "012456789"
    for i in s:
        print(i, end=" ")
    print('<=str')

    for i in list(s):
        print(i, end=" ")
    print('<=list')

    for i in set(s):  # 副作用:字符排序随机了
        print(i, end=" ")
    print('<=set')

    for i in tuple(s):  
        print(i, end=" ")
    print('<=tuple')

#Python的元组与列表类似，不同之处在于元组的元素不能修改。
# 定义tuple与定义list的方式相同,除了整个元素集是用小括号包围的而不是方括号.

def test_Tuples():
    print('--------------tuple--------------')
    t = 1, 3, '3!'     #不用括号也可以
    print ('type of t is:',type(t))
    _u = t, (1, 2, 3, 4, 5)            # Tuples may be nested:
    print ('type of _u is:',type(_u))
    print ('2nd element of  _u is:',_u[1])
    t= (1, 2, [30, 40])  
    t[2].append(50)
    print('t\'s list changed',t)

    import collections

    Card = collections.namedtuple('Card', ['rank', 'suit'])  # return a subclass
    class FrenchDeck:
        ranks = [str(n) for n in range(2, 11)] + list('JQKA')
        suits = 'spades diamonds clubs hearts'.split()

        def __init__(self):
            self._cards = [Card(rank, suit) for suit in self.suits
                        for rank in self.ranks]

        def __len__(self):
            return len(self._cards)

        def __getitem__(self, position):
            return self._cards[position]


    deck = FrenchDeck()
    print("card number %d" % len(deck))
    print("cards are: ", deck[13:18])


#both dict,set is {}
def test_Dict():
    print('--------------dict--------------')
    tel = {}       # a = set()  # 只能以这种方式创建空set
    tel = {'jack': 4098, 'sape': 4139}
    tel['guido'] = 4127
    tel.update({'john':4888})

    #build the dict 
    name = (["first", "Google"], ["second", "Yahoo"])
    website = dict(name)
    print(website)
    website = {}.fromkeys(("third", "forth"), "facebook")   #这个method名有点误导,实际参数是 key/value
    print(website)

    import collections
    print("OrderedDict=>", collections.OrderedDict(tel))

    del tel['sape']
    tel['irv'] = 4127

    print("keys()=>", tel.keys())

    # 默认情况下，dict迭代的是key。如果要迭代value，可以用for value in d.values()，
    for k, v in tel.items():
        print(k,'=>', v)
    print()    

    for i, k in enumerate(tel.keys(),100):
        print(i, k,'=>', tel[k])
    print()

    city_code = {("suzhou", "苏州"): "0512", ("tangshan", "唐山"): "0315", ("beijing"): "010", ("shanghai", "上海"): "021"}
    s = '唐山'
    for k in city_code.keys():
        if s in set(k):
            code = city_code[k]
            break
    assert code == '0315'

    dd = collections.defaultdict(lambda : 0)
    dd["blockchain"] = 88
    print(dd["blockchain"],'default dict=>', dd["efg"])

    A = collections.Counter([1, 2, 2])
    B = collections.Counter([2, 2, 3])
    print(A | B, A & B, A+B, A-B,)

def test_defauldict():
    """Build an index mapping word -> list of occurrences"""

    WORD_RE = re.compile('\\w+')

    index = collections.defaultdict(list)     # <1>
    with open(sys.argv[1], encoding='utf-8') as fp:
        for line_no, line in enumerate(fp, 1):
            for match in WORD_RE.finditer(line):
                word = match.group()
                column_no = match.start()+1
                location = (line_no, column_no)
                index[word].append(location)  # <2>

    if len(index)==0:
        return
    for word in index:
        print(word, index[word][0])
    # END INDEX_DEFAULT

# set和dict类似，但只是key的集合,由于key不能重复，所以，在set中，没有重复的key。
def test_Set():
    print('-------set------')
    a = set()  # 只能以这种方式创建空set
    a.add('bcccc')
    a = set('blockchainccc')
    b = frozenset('blockchaindeeeee')

    print("a,b:", a, b)
    print("a-b:", a-b)              # letters in a but not in b
    print("a|b:", a | b)                # letters in either a or b
    print("a&b:", a & b)                # letters in both a and b
    print("a^b:", a ^ b)                # letters in a or b but not both
    print("a<b:", a < b)

if __name__ == "__main__":
    if '-v' in sys.argv:
        sys.argv.remove('-v')
        verbose = True
    else:
        verbose = False    
    test_list()
    list_trick()

    speed_compar()
    common()
    test_Tuples()

    test_Dict()
    test_defauldict()

    test_Set()