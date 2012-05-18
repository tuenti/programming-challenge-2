#!/usr/bin/env python
# -*- conding: utf-8 -*-
from __future__ import print_function, division
input = raw_input

if __name__ == '__main__':
    N = int(input())

    for n in range(N):
        W, H, ct = [int(x) for x in input().split()]
        line = input()

        W *= ct
        H *= ct

        words = [len(w) for w in line.split()]

        biggest = 0
        for size in range(1, min(W, H)+1):
            w = W//size
            h = H//size

            if max(words) > w:
                continue

            lines = 0
            acum = 10000
            for ws in words:
                if acum + 1 + ws <= w:
                    acum += 1 + ws
                else:
                    acum = ws
                    lines += 1

            if lines <= h:
                biggest = size

        chars = sum([1 for x in line if not x.isspace()])
        r = int(0.5 + (biggest*biggest*chars)/(ct*2))
        

        print('Case #{0}: {1}'.format(n+1, r))

