#!/usr/bin/env python3

# 在Python中，这种一边循环一边计算的机制，称为生成器：generator。
# 要创建一个generator第一种方法很简单，只要把一个列表生成式的[]改成()，就创建了一个generator：

def test_generator():
    g = (x * x for x in range(3))
    #以下两种调用是互斥的,没有重置/初始化迭代对象的方法 print(next(g),next(g),next(g))
    for c in g:  # 如果上面已经执行完全部next,for循环不会执行
        print(c)


#链接：https://zhuanlan.zhihu.com/p/51016939
# 虽然这一算法非常简单，但用于构造杨辉三角的迭代方法可以归类为动态规划，因为我们需要基于前一行来构造每一行。

class Solution:
    def generate(self, num_rows):
        triangle = []

        for row_num in range(num_rows):
            # The first and last row elements are always 1.
            row = [None for _ in range(row_num+1)]
            row[0], row[-1] = 1, 1

            # Each triangle element is equal to the sum of the elements
            # above-and-to-the-left and above-and-to-the-right.
            for j in range(1, len(row)-1):
                row[j] = triangle[row_num-1][j-1] + triangle[row_num-1][j]

            triangle.append(row)

        return triangle

def test_YH2():
    s = Solution()
    results = s.generate(5)
    print(results)        


def test_YH():

    def yh():
        l = [1]
        yield l
        l=[1,1]
        yield l
        while True:
            l_next = l[:1]            #copy the first element of the above layer
            for i in range(1,len(l)):
                l_next.append(l[i-1]+l[i])
            l_next.append(l[i])            #copy the last element of the above layer
            yield l_next
            l = l_next

    results = []
    for i,l  in enumerate( yh() ):          #t= next(tr())   每次t 都返回[1]
        if i>=5:
            break
        results.append(l)
    print(results)        
       

# 如果一个函数定义中包含yield关键字，那么这个函数就不再是一个普通函数，而是一个generator：
def fib4(n):
    assert n > 0
    a, b = 0, 1
    for _i in range(n):
        yield a+b
        a, b = b, a+b
def testfib4():  # test module
    for i, j in enumerate(fib4(5)):
        print('fib({})={}'.format(i, j))

#如果不判断是否在main中，作为module 引用时，以下代码就被执行了
if __name__ == "__main__":
    test_generator()
    test_YH()
    test_YH2()
    testfib4()
