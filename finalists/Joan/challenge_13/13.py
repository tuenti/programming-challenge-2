#!/usr/bin/env python

import sys

def  order(L,N):
    
    C = range(N)
    #For each position compute the next position
    f = C[:L]
    k = C[L:]

    nexts = [-1]*N
    turn = 0

    #Simulate the suffle algorithm to calculte this next vectors
    while True:
            if len(f) == 0 and len(k) == 0:
                break   
            elif  len(f) == 0:
                while k:
                    nexts[k.pop()]=turn
                    turn+=1
                break
            elif len(k) == 0:
                while f:
                    nexts[f.pop()]=turn
                    turn+=1
                break


            if turn%2 == 0:
                nexts[f.pop()]= turn
            else:
                nexts[k.pop()]= turn
            turn += 1

    #Compute cicles
    # We compute all the cicles in this "directed graph"
    # The loop is the Least Cmmon Multiple of all the cycles
    
    visited = [False]*N

    #len of the cycle
    cycle = 1

    for n in range(len(nexts)):

       if not visited[n]:
         visited[n]=True
         x = nexts[n]
         #iterate until find a cycle
         l = 1
         while x != n:
            visited[x] = True
            x = nexts[x]
            l+=1

         #compute the MCM in incremental way
         cycle = MCM(cycle,l)
    return cycle


#Maximun Common Divisor (aux)
def MCD(a,b): 
   if a<b: 
      x = a 
      a = b 
      b = x 
   while a%b>0: 
     r = a%b 
     a = b 
     b=r 
   return b 

#Minimum Common Multiple
def MCM(f,g): 
    z= (f*g)/MCD(f,g) 
    return z 

    


if __name__ == "__main__":
    
    # Read the input and compute the algorithm
    nc = int(sys.stdin.readline())

    for ncase in range(nc):
        (N,L) = sys.stdin.readline().split()
        N = int(N)
        L = int(L)

        cards = range(N)


        print "Case #%d: %d" % (ncase+1,order(L,N))
              
