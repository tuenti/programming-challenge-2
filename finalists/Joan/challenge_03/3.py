#!/usr/bin/env python

import sys

if __name__ == '__main__':

    #Keep the minimum node at each point
    currentmin = 9999999999
    indexmin = -1
    #Maximize the different between stocks
    diffmax = 0
    #Current time
    time = 0
    #Time of the minimum
    timemin = 0
    #Time of the maximization
    timeini = 0
    timeend = 0


    for l in sys.stdin:
        s = int(l)
        #Checks the min
        if s < currentmin:
            currentmin = s
            timemin = time
        diff = s-currentmin
        #Checks the difference
        if diff > diffmax:
            diffmax = diff
            timeend = time
            timeini = timemin
        time += 100

    print timeini, timeend, diffmax



