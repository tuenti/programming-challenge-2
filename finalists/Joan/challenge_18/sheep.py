#!/usr/bin/env python

import sys


    a = v[0][-1]
    b = v[1][-1]

    c = a+b

    if c == ".?":
        return ">"
    elif c == "?.":
        return "<"
    elif c == "..":
        return "+"
    elif c == "!!":
        return "-"
    elif c == "!.":
        return "."
    elif c == ".!":
        return ","
    elif c == "!?":
        return "["
    elif c == "?!":
        return "]"
    
    return c

if __name__ == '__main__':

   for line in sys.stdin: 
#    line = sys.stdin.readline()

    sequence = line.split()

    
    N = len(sequence)

    k = []
    x = 0
    while x+2 <= N:
        

        cad = sequence[x:x+2]

        k.append(translate(cad))
        
        x=x+2

    print ''.join(k)
