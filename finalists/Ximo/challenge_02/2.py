#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function
input = raw_input

def solve(n):
    ''' minimum number of multiplications needed to calc a**n '''
    j, k = n+1, 0
    while j > 1:
        if j%2: j -= 1
        else: j /= 2
        k += 1
    return k

if __name__ == '__main__':
    C = int(input())
    for c in range(C):
        N = int(input())
        print('Case #{}: {}'.format(c+1, solve(N)))

