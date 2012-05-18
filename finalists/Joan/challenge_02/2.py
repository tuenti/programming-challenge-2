#!/usr/bin/env python

import sys
import math


#Sequence to calculate the numbers
def calc(num):

    j = num+1
    k = 0
    while j > 1:
        if j % 2 == 1:
            j = j-1
        else:
            j = j/2
        k = k + 1
    return k 


if __name__ == '__main__':
   
    
    ncases = int(sys.stdin.readline())

    for nc in range(ncases):
        n = int(sys.stdin.readline())

        print "Case #%d: %d"%(nc+1,calc(n))
