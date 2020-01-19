#!/usr/bin/python Hanoi.py
# Copyright 2018  Alex(xuyc@sina.com).
# Licensed under the Apache License, Version 2.0
# http://www.apache.org/licenses/LICENSE-2.0

import time

SEQ_STATE = 0


def draw_towers():
    ll = [[0]*(H-len(TOWERS[0]))+TOWERS[0], [0]*(H-len(TOWERS[1])) +
          TOWERS[1], [0]*(H-len(TOWERS[2]))+TOWERS[2]]
    width = 80//3                              # the assume screen width is 80
    for i in range(H):
        for l in ll:
            num = l[i]
            if num > 0:
                centeer, left_bias = width // 2, num//2
                s1, s2, s3 = " "*(centeer-left_bias), '*'*num, ' ' * \
                    (width-centeer-num+left_bias)
                print(s1, s2, s3, sep='', end='')
            else:
                print(" "*width, sep='', end='')
        print()  # end the line

    global SEQ_STATE
    print("                              ------state %d----" % (SEQ_STATE))
    SEQ_STATE += 1
    time.sleep(1)
    return


def move_the_top(f, t):  # move in the LL, and update the change in screen
    TOWERS[t].insert(0, TOWERS[f].pop(0))
    draw_towers()
    return


def hanoi(tail, tower_src, tower_dst, tower_between):
    if tail == 1:
        move_the_top(tower_src, tower_dst)
        return
    else:
        hanoi(tail-1, tower_src, tower_between, tower_dst)
        move_the_top(tower_src, tower_dst)
        hanoi(tail-1, tower_between, tower_dst, tower_src)
    return

H = int(input(" Please input the height (2~12)) of Hanoi tower:"))
assert H >= 2
assert H <= 12
TOWERS = [[x+1 for x in range(H)], [], []]
draw_towers()
hanoi(H, 0, 2, 1)
