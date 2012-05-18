#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function
input = raw_input
import sys
import hashlib

if __name__ == '__main__':
    line = input().strip()
    md5 = hashlib.md5()

    trans = []
    for C in sys.stdin:
        C = C.strip().split(',')
        d = {a:a for a in line}
        for c in C:
            a, b = c.split('=>')
            assert len(a) == 1
            assert len(b) > 0
            d[a] = b
        trans.append(d)
    trans.reverse() 

    for i in range(len(trans)-1):
        # applies trans[i] to trans[i+1]
        for d, t in trans[i+1].items():
            result = ''
            for c in t:
                result += trans[i].get(c, c)
            trans[i+1][d] = result
    d = trans[-1]

    for c in line:
        md5.update(d.get(c, c))

    print(md5.hexdigest())

