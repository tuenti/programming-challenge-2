#!/usr/bin/env python

import sys, os


if __name__ == '__main__':

    ncases = int(sys.stdin.readline())

    for nc in range(ncases):
        fields = sys.stdin.readline().split()
        R = int(fields[0])
        K = int(fields[1])
        G = int(fields[2])
        groups = [int(f) for f in sys.stdin.readline().split()]

        #compute the endings, for each group we note the next group starting

        M = {}
        for i in range(G):
            t = groups[i]
            
            act = (i+1)%G

            while t + groups[act] <= K:
                    #If is the same node
                    if act == i:
                        n = (G+i-1)%G
                        break
                    t += groups[act] 
                    act = (act+1)%G

            M[i] = (act,t)
         
#        print M

        #compute the rounds
        total = 0
        ini = 0
  
        
        #visited nodes
        #For avoid repeting cycles we note [visited,cost_of_cycle,round]
        V = [(False,0,0) for g in range(G)]
        r = 0
        while r < R:
            if V[ini][0]:
                #avoid cycles
                cyclet = total - V[ini][1]
                cycler = r - V[ini][2]

                #coumpute the number of cycles
                it = (R-r-1)/cycler
                total += it*cyclet
                r += it*cycler
            #update visited information
            V[ini] = (True, total, r) 
            total += M[ini][1]

            ini = M[ini][0]
            r += 1
#        print "Case #%d: %d"%(nc+1,total)
        print total
