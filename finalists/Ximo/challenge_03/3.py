#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function
import sys

if __name__ == '__main__':
    values = [int(x) for x in sys.stdin]
   
    m = [0, values[0]] # [min, time]
    b = [0, 0, 0] # [buy time, sell time, gain]
    for i, v in enumerate(values):
        if v < m[1]:
            m = [i, v]
        if v-m[1] > b[2]:
            b = [m[0], i, v-m[1]]
    print(b[0]*100, b[1]*100, b[2])

