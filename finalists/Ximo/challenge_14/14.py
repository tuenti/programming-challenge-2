#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function
input = raw_input
import sys

def check(word):
    v = map(int, list(word))

    h1 = [1,0,1,0,1,0,1]
    h2 = [0,1,1,0,0,1,1]
    h3 = [0,0,0,1,1,1,1]
    r1 = sum([a*b for a,b in zip(v,h1)])%2
    r2 = sum([a*b for a,b in zip(v,h2)])%2
    r3 = sum([a*b for a,b in zip(v,h3)])%2

    r = (r1,r2,r3)

    if r == (0,0,0):
        return v

    for i in range(7):
        if r == (h1[i], h2[i], h3[i]):
            v[i] = 1-v[i]

    return v

if __name__ == '__main__':
    for line in sys.stdin:
        line = line.strip()
        #print(len(line), len(line)%4, len(line)%7)

        msg = []
        error = False
        while len(line) >= 7:
            word = check(line[:7])
            word = [word[2]] + word[4:7]
            msg += word
            line = line[7:]
        if len(line) != 0: # invalid length
            print("Error!")
            continue

        chars = ''
        while len(msg) >= 8:
            if msg[0] == 1: # non ascii char
                error = True
                break
            c = eval('0b' + str.join('', map(str, msg[:8])))
            chars += chr(c)
            msg = msg[8:]

        if not error:
            print(chars)
        else:
            print("Error!")

