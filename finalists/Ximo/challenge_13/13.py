#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function
input = raw_input
from fractions import gcd

def lcm(a, b):
    ''' returns the least common multiple of a and b. '''
    return (a*b)/gcd(a,b)

def shuff(a, b):
    ''' generalized faro-shuffling. '''
    r = []
    for i in range(min(len(a), len(b))):
        r.append(a.pop())
        r.append(b.pop())
    if len(a) > 0:
        r += reversed(a)
    if len(b) > 0:
        r += reversed(b)
    return r

if __name__ == '__main__':
    C = int(input())

    for c in range(C):
        N, L = map(int, input().split())

        orig = range(N)
        # creates the permutation
        perm = shuff(orig[0:L], orig[L:])
        moves = [0]*len(perm)
        for i in orig:
            moves[perm[i]] = i

        # cycle-length for each position in the permutation
        used = set()
        result = 1
        for n in orig:
            if n not in used:
                used.add(n)
            else:
                continue
            count = 1
            v = moves[n]
            while v != n:
                count += 1
                v = moves[v]
                used.add(v)
            #print('cycle for {}: {}'.format(n, count))
            result = lcm(count, result)

        print('Case #{}: {}'.format(c+1, result))
