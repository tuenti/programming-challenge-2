#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division
input = raw_input

if __name__ == '__main__':
    R = int(input())
    U = int(input())
    N = int(input())

    V = []
    m = [False]*N
    s = [False]*N
    for _ in range(R):
        label, vector = input().split(None, 1)
        V.append([label, map(int, vector.split())])
        out = m
        total = sum(V[-1][1])
        for i in range(N):
            V[-1][1][i] = V[-1][1][i]/total

    # 1-nearest neighbor
    acum = 0
    for _ in range(U):
        vector = map(int, input().split())
        total = sum(vector)
        vector2 = [i/total for i in vector]
        label = None
        dist = 100000000000000
        for lab, v in V:
            d = sum([abs(a-b)**2 for a,b in zip(vector2,v)])
            if d < dist:
                dist = d
                label = lab
        if label == 'M':
            acum += sum(vector)

    print(acum)
