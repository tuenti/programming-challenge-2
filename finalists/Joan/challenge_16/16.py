#!/usr/bin/env python

import sys


#I've also tried a Perceptron, but I've haven't so much data so i'm not sure of tunning up al the parameters correct (training stop conditions)

#I've used k-nn with k = 1
def knn(S,V,f, k = 1):

    res = []
    
    for s in S:
#        print s
        res.append((f(s[1:],V),s[0]))

    res.sort()
#    print res 
    nS = 0
    nM = 0
    for i in range(k):
        if res[i][1] == 1:
            nM += 1
        else:
            nS += 1

#    print "Result",nM, nS
    return nM > nS
    
#Is it important to compute normalization, I use max-min normalization

norm = []
def computeNorm(lR, N):                                                       
  for i in range(N):
      norm.append(max([ x[i+1] for x in lR]))


def normalizeL(L,N,add = 0):
    
    for l in L:
        normalize(l,N,add)
#            print i, L[l][i+add], norm[i] 
def normalize(l,N,add = 0):
    
        for i in range(N):
            l[i+add]=float(l[i+add])/norm[i]

#I use euclidean distance sqrt is no needed because is linear increasing function
def euclideanDist(v1,v2):
    assert len(v1) == len(v2), "No len: %d %d"%(len(v1),len(v2))
    
    dist = sum([(a-b)*(a-b) for (a,b) in zip(v1,v2)])

    return dist
if __name__ == '__main__':
    
    R = int(sys.stdin.readline())
    U = int(sys.stdin.readline())
    N = int(sys.stdin.readline())

    lR = []
    lU = []

    for r in range(R):
        sample = sys.stdin.readline().split()

        if sample[0] == 'M':
            sample[0] = 1
        else:
            sample[0] = -1

        lR.append(map(int,sample))
    
    total = 0
    # Normalize al the data
    computeNorm(lR,N)

 #   print norm
    normalizeL(lR,N,1)
#    print lR

    for u in range(U):
        sample = sys.stdin.readline().split()
        sample = map(int,sample)
        
        #copy the original to compute the final sum
        orig = [x for x in sample]
        normalize(sample,N)
        
        #If the nn is M, add the sum of the parameters
        if knn(lR,sample,euclideanDist):
            total+= sum(orig)
        
    print total
