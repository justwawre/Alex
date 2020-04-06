#!/usr/bin/env python3
def adder(x):
    def add_internal(y):
        return x+y
    return add_internal     

add5 = adder(5)
print(add5(3))    