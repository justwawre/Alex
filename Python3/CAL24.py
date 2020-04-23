# Copyright 2018  Alex(xuyc@sina.com).
# Licensed under the Apache License, Version 2.0
# http://www.apache.org/licenses/LICENSE-2.0
import itertools
POLISH = []
PRIO = {'+': 1, '-': 1, '*': 2, '/': 2, '#': 0}
def form_polish_expr(o,l_nums):
    for n in l_nums:
        POLISH.append([n[0], n[1], o[0], n[2], n[3], o[1], o[2]])
        if [o[1], o[2]] not in[['+', '+'], ['*', '*']]:
            POLISH.append([n[0], n[1], o[0], n[2], o[1], n[3], o[2]])
        if [o[0], o[1]] not in[['+', '+'], ['*', '*']]:
            POLISH.append([n[0], n[1], n[2], o[0], o[1], n[3], o[2]])
        if o[2] not in ['+', '*']:
            POLISH.append([n[0], n[1], n[2], n[3], o[0], o[1], o[2]])
        if [o[0], o[1]] not in[['+', '+'], ['*', '*']]:
            POLISH.append([n[0], n[1], n[2], o[0], n[3], o[1], o[2]])
    return

def cal_polish(ll):
    ss = []
    for c in ll:
        if c in ['+', '-', '*', '/']:
            n1 = ss.pop(0)
            n0 = ss.pop(0)
            if n0 > n1 and c in ['+', '*']:
                raise Exception("skip due to commutation")
            elif c == '+':
                val = n0 + n1
            elif c == '-':
                val = n0 - n1
            elif c == '*':
                val = n0*n1
            elif c == '/':
                val = n0/n1
            else:
                raise Exception("unexpected op")
            ss.insert(0, val)
        else:
            ss.insert(0, c)
    return val

def polish_to_expr(pol):
    pol.append('#')
    l_idx_op =[]
    for i, c in enumerate(pol):
        if c in ['+', '-', '*', '/', '#']:
            l_idx_op.append(i)
    for i,idx in enumerate(l_idx_op):
        if pol[idx]=='#':
            break
        if l_idx_op[i+1]-idx > 2:  # tree type 1 only
            idx_next = l_idx_op[i+2]
        else:
            idx_next = l_idx_op[i+1]
        prio,prio_next= PRIO[pol[idx]],PRIO[pol[idx_next]]                
        right = 0
        for i in range(0,idx):
            if pol[i] not in ['+', '-', '*', '/', '$']:
                left,right=right,i 
        if prio < prio_next:
            braced = True
        elif prio > prio_next:
            braced = False
        else:    
            if [pol[idx],pol[idx_next]] in [['+','+'],['-','+'], ['*','*']]:
                braced = False
            elif  [pol[idx],pol[idx_next]] in [['-','-'],['+','-'],['*','/']]:
                braced = (idx_next - idx ==1)
            else:
                braced = True     
        if braced:
            expr = ['(', str(pol[left]), pol[idx],str(pol[right]), ')']
        else:
            expr = [str(pol[left]), pol[idx], str(pol[right])]
        expr = ''.join(expr)
        pol[idx], pol[left], pol[right] = expr, '$', '$'
    return expr
 
l = input("Please input 4 number (1~10):").split()
l_nums = list(set(itertools.permutations([int(x) for x in l])))
for op1 in  ['+', '-', '*', '/']:
    for op2 in  ['+', '-', '*', '/']:
        for op3 in  ['+', '-', '*', '/']:
            form_polish_expr([op1, op2, op3],l_nums)
l_expr = []
for l in POLISH:
    try:
        if 24 == cal_polish(l):
            expr=polish_to_expr(l)
            l_expr.append(expr)
    except:
        continue
l = len(l_expr)
if l > 0:
    l_expr = list(set(l_expr))
    print("there is %d kind of solution:" % (l))
    for ll in l_expr:
        print(ll)
else:
    print("no solution")
