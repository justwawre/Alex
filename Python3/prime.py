#!/usr/bin/env python3

import math
def is_prime(n):
    if n < 2:
        return False
    for d in range(2, round(math.sqrt(n))+1):
        if n % d == 0:
            return False
    else:
        return True

class cls_prime:
    max = 2
    primelist = [0, 1, 2]
    #above variable 是属于类的,但是如果用self.max 使用又属于instance
    def cal(self, m):
        for i in range(cls_prime.max+1, m+1):
            if is_prime(i):
                cls_prime.primelist.append(i)
                print("add prime", i)
        cls_prime.max = m

    def __call__(self, n):
        if n > cls_prime.max:
            self.cal(n)
        if n in cls_prime.primelist:
                print(n, "is prime")
        else:
                print(n, "not prime")
def testPrime3():
    p= cls_prime()
    p(27)
    p(17)
    p(31)

if __name__ == "__main__":
    print('--------prime-----------')
    testPrime3()