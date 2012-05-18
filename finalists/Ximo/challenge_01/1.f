#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function
input = raw_input

keys = {
        (0,0):' 1', (0,1):'abc2ABC', (0,2):'def3DEF', (1,0):'ghi4GHI',
        (1,1):'jkl5JKL', (1,2):'mno6MNO', (2,0):'pqrs7PQRS', (2,1):'tuv8TUV',
        (2,2):'wxyz9WXYZ', (3,1):'0', (3,2):'^',
}

positions = {} # reverse of keys
for k,v in keys.items():
    for c in v:
        positions[c] = k + (keys[k].index(c)+1,)


def mov_cost(a, b):
    ''' Returns the cost of the movement from a to b in ms. '''
    y1, x1, _ = positions[a]
    y2, x2, _ = positions[b]
    difx = abs(x2-x1)
    dify = abs(y2-y1)
    diag = min(difx, dify)
    return diag*350 + (difx-diag)*200 + (dify-diag)*300


def cost(pos, key, case):
    ''' Returns the cost in ms needed to write key with the finger at pos. '''
    p = positions[pos][0:2]
    k = positions[key][0:2]
    modifiers = 0
    if key.isalpha() and key.islower() != case.islower(): # need a lock change
        # going to ^ and pushing
        modifiers += mov_cost(pos, '^') + 100 + mov_cost('^', key)
    else: # same case
        if p == k: # same key, wait 500...
            modifiers += 500
        else: # moving to key
            modifiers += mov_cost(pos, key)

    return positions[key.lower()][2]*100 + modifiers


C = int(input())
for c in range(C):
    seq = input()
    time = 0 if seq[0] != '0' else -500
    pos = '0'
    case = 'l'
    for s in seq:
        time += cost(pos, s, case)
        if s.isalpha():
            case = s
        pos = s
    print(time)

