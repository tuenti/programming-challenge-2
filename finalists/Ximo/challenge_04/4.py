#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division
input = raw_input

T = int(input()) # number of test cases

for t in xrange(1,T+1):
    R,k,N = [ int(x) for x in input().split(' ') ]
    G = [ int(x) for x in input().split(' ') ]

    # precalc
    # what's the starting group if the current starting group is i
    dst = [0]*N
    liters = [0]*N
    for i in xrange(N):
        acum = G[i]
        next = (i+1)%N
        while acum+G[next] <= k:
            if next == i:
                next = (N+i-1)%N
                break
            acum += G[next]
            next = (next+1)%N
        dst[i] = next
        liters[i] = acum

    acum = 0
    current = 0
    visited = [False]*N
    cont = [0]*N
    runs = [0]*N
    x = 0
    while x < R:
        if visited[current]: # ciclo encontrado!
            dif_p = acum - cont[current]
            dif_r = x - runs[current]

            loops = (R-x-1)//dif_r
            rem = (R-x-1)%dif_r
            acum += loops*dif_p
            x += loops*dif_r

        visited[current] = True
        cont[current] = acum
        runs[current] = x

        acum += liters[current]
        current = dst[current]

        x += 1

    print(acum)

