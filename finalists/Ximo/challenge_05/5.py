#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division
import sys
from datetime import datetime, timedelta
import time

# old clock
# working leds for each digit
old_leds = [6, 2, 5, 5, 4, 5, 6, 3, 7, 6]

# the new clock
# delta costs
new_leds = {(0,1):0, (1,2):4, (2,3):1, (3,4):1, (4,5):2, (5,6):1, (6,7):1,
        (7,8):4, (8,9):0, (9,0):1, (2,0):2, (3,0):2, (5,0):2}
for x in range(10): # not moving costs 0
    new_leds[(x,x)] = 0


if __name__ == '__main__':
    for line in sys.stdin:
        from_date, from_time, _, to_date, to_time = line.split()
        from_dt = datetime(*time.strptime(from_date + ' ' + from_time, '%Y-%m-%d %H:%M:%S')[0:6])
        to_dt = datetime(*time.strptime(to_date + ' ' + to_time, '%Y-%m-%d %H:%M:%S')[0:6])
        delta = to_dt - from_dt

        ti = [0, 0, 0] # [h, m, s]
        old = 36 + delta.days*2401956 # changes in one day
        new = 36 + delta.days*146479 # changes in one day

        for s in range(delta.seconds):
            pt = [ti[0], ti[1], ti[2]]

            ti[2] += 1
            if ti[2] >= 60:
                ti[2] = 0
                ti[1] += 1
                if ti[1] >= 60:
                    ti[1] = 0
                    ti[0] = (ti[0]+1)%24

            old += sum([old_leds[i//10] + old_leds[i%10] for i in ti])

            for p,t in zip(pt, ti):
                ori_u = p%10
                ori_d = p//10
                dst_u = t%10
                dst_d = t//10
                new += new_leds[(ori_u, dst_u)] + new_leds[(ori_d, dst_d)]

        print(old-new)

