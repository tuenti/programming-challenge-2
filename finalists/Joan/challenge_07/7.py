#!/usr/bin/env python


import sys
from copy import copy
M = {}
L = []
S = []

def post_sort(V,x, N):

    #Generates all posibles topological orders

    if x == N-1:
        cad = ''.join(V)
        if cad not in S:
            S.append(cad)
        return

    
    for j in range(x+1,N):
        
        ind = True
        #If two or more consecutive nodes change it
        for k in range(x,j):
            if V[j] in M[V[k]]:
                ind = False
                break
        if ind:
            nV = copy(V)
            nV[x],nV[j] = nV[j], nV[x]
            
            post_sort(nV,x+1,N)
            #break

    post_sort(V,x+1,N)

#DFS topological sort
def top_sort(n,visited):
    if n not in visited:
       visited[n] = True
       for m in M[n]:
              top_sort(m,visited)
       L.append(n)


if __name__ == "__main__":


    for s in sys.stdin:
        
        l = s.replace("\n","")

        #Generate the graf M
        lsize=len(l)
        for i in range(lsize):
            for j in range(i+1,lsize):

            
                    if l[i] not in M:
                        M[l[i]] = [l[j],]
                    else:
                        if l[j] not in M[l[i]]:
                            M[l[i]].append(l[j])
                    if l[j] not in M:
                        
                        M[l[j]]=[]
                    


    N = len(M)
    #Topological Order
    visited = {}
    for v in M:
        top_sort(v,visited)
    
    
    L = L[::-1]

    #Generates all the topological order for one of them
    post_sort(L,0,N)
    
    S.sort()
    
    for s in S:
        print s
