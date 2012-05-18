#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division
input = raw_input
from collections import Counter

def cake_cut(n):
    return ((n+1)*(n))//2 + 1

if __name__ == '__main__':
    C = int(input())

    for c in range(C):
        n = int(input())
        print('Case #{}: {}'.format(c+1, cake_cut(n)))

