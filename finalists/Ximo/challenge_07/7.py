#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division
input = raw_input
import sys
import itertools

def alltopsorts(k, pref=''):
    '''
    Prints every possible topological sort
    Based on the paper:
    Knuth, Szwarcfiter. A Structured Program to Generate All Topological
    Sorting Arrangements. May, 1974.
    '''

    global n, relations, chars

    if k == n:
        print(pref)
        return

    count = [ sum([1 for r in relations if r[1] == i]) for i in range(n)]
    D = [i for i,c in enumerate(count) if c == 0 and chars[i] not in pref]

    if len(D) > 0:
        for d in D:
            erased = [r for r in relations if r[0] == d]
            relations = [r for r in relations if r[0] != d]
            alltopsorts(k+1, pref+chars[d])
            relations += erased


if __name__ == '__main__':
    lines = [ line.strip() for line in sys.stdin ]
    chars = list(sorted(set(itertools.chain(*lines))))
    codes = {c:chars.index(c) for c in chars}
    n = len(chars)

    relations = set()
    for line in lines:
        for i in range(len(line)):
            for c in line[:i]:
                relations.add( (codes[c], codes[line[i]]) )
    
    alltopsorts(0) 

