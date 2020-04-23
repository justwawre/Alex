# Copyright 2018  Alex(xuyc@sina.com).
# Licensed under the Apache License, Version 2.0
# http://www.apache.org/licenses/LICENSE-2.0
import itertools
PRIO = {'+': 1, '-': 1, '*': 2, '/': 2, '#': 0}
SOLUITON = set([])  # set

#粗糙版，没有考虑表达式等价，交换律 
def form_polish_expr(o, l_nums):
    for n in l_nums:
        l_expr = []
        expr = polish_to_expr([n[0], n[1], o[0], n[2], n[3], o[1], o[2]])
        l_expr.append(expr)
        expr = polish_to_expr([n[0], n[1], o[0], n[2], o[1], n[3], o[2]])
        l_expr.append(expr)
        expr = polish_to_expr([n[0], n[1], n[2], o[0], o[1], n[3], o[2]])
        l_expr.append(expr)
        expr = polish_to_expr([n[0], n[1], n[2], n[3], o[0], o[1], o[2]])
        l_expr.append(expr)
        expr = polish_to_expr([n[0], n[1], n[2], o[0], n[3], o[1], o[2]])
        l_expr.append(expr)

        for expr in l_expr:
            try:
                r = eval(expr)
            except:
                continue
            if r == 24:     #由于表达式秋之
                print(expr)
    return


def polish_to_expr(pol):
    pol.append('#')
    l_idx_op = []
    for i, c in enumerate(pol):
        if c in ['+', '-', '*', '/', '#']:
            l_idx_op.append(i)
    for i, idx in enumerate(l_idx_op):
        if pol[idx] == '#':
            break
        if l_idx_op[i+1]-idx > 2:  # tree type 1 only
            idx_next = l_idx_op[i+2]
        else:
            idx_next = l_idx_op[i+1]
        prio, prio_next = PRIO[pol[idx]], PRIO[pol[idx_next]]
        right = 0
        for i in range(0, idx):
            if pol[i] not in ['+', '-', '*', '/', '$']:
                left, right = right, i
        if prio < prio_next:
            braced = True
        elif prio > prio_next:
            braced = False
        else:
            if [pol[idx], pol[idx_next]] in [['+', '+'], ['-', '+'], ['*', '*']]:
                braced = False
            elif [pol[idx], pol[idx_next]] in [['-', '-'], ['+', '-'], ['*', '/']]:
                braced = (idx_next - idx == 1)
            else:
                braced = True
        if braced:
            expr = ['(', str(pol[left]), pol[idx], str(pol[right]), ')']
        else:
            expr = [str(pol[left]), pol[idx], str(pol[right])]
        expr = ''.join(expr)
        pol[idx], pol[left], pol[right] = expr, '$', '$'
    return expr


l = input("Please input 4 number (1~10):").split()
l_nums = list(set(itertools.permutations([int(x) for x in l])))
for op1 in ['+', '-', '*', '/']:
    for op2 in ['+', '-', '*', '/']:
        for op3 in ['+', '-', '*', '/']:
            form_polish_expr([op1, op2, op3], l_nums)
