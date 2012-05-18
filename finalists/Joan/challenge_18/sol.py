#!/usr/bin/env python

import sys
if __name__ == '__main__':


   ncases = int(sys.stdin.readline())


   for nc in range(ncases):

       n = int(sys.stdin.readline())

       print "Case #%d: %d" %((nc+1),(n*(n+1)/2)+1)
