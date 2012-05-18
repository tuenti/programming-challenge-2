#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

ncasos = int(sys.stdin.readline())
for caso in range (1,ncasos+1):
    ncortes = int(sys.stdin.readline())
    print "Case #%d: %d"%(caso,ncortes*(ncortes+1)/2+1)
