#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division
input=raw_input
import sys

if __name__ == '__main__':
    for line in sys.stdin:
        ops = []
        for o in line.split():
            if o.isdigit():
                ops.append(int(o))
            elif o == 'mirror':
                ops[-1] *= -1
            elif o == 'breadandfish':
                ops.append(ops[-1])
            elif o == '#':
                b = ops.pop()
                a = ops.pop()
                ops.append(a*b)
            elif o == 'conquer':
                b = ops.pop()
                a = ops.pop()
                ops.append(a%b)
            elif o == 'dance':
                ops[-1], ops[-2] = ops[-2], ops[-1]
            elif o == '.':
                print(ops[-1])
            elif o == '$':
                b = ops.pop()
                a = ops.pop()
                ops.append(a-b)
            elif o == 'fire':
                b = ops.pop()
                a = ops.pop()
                ops.append(max(a,b))
            elif o == '@':
                b = ops.pop()
                a = ops.pop()
                ops.append(a+b)
            elif o == '&':                
                b = ops.pop()
                a = ops.pop()
                ops.append(a//b)
            else:
                print('o=', o)
                break
 
