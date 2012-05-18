#!/usr/bin/env python

import sys
import md5

if __name__ == "__main__":

    # Dict of Rules
    R = {} 
    Q = sys.stdin.readline().replace("\n","")
    i = 0
    for s in sys.stdin:
        D = {}
        rules = s.replace("\n","").split(",")
        newR = []

        #Read the rules
        for r in rules:

            (a,b) = r.split("=>")
            D[a] = b

            #If a rule is not in R, add add the final
            if a not in R:
                newR.append((a,b))

        
        #if i == 0:
        #    R = D
        #    i+=1
        #    continue
        
        #Replace the old rules with the old ones
        for r in R:
            nR = ""
            for c in R[r]:
                if c in D:
                    nR +=D[c]
                else:
                    nR+=c
            R[r] = nR
        
        #Add the old ones
        for (a,b) in newR:
            R[a]=b

    #Generate MD5 sum at each character, THE STRING IS SO LONG!
    M = md5.new()
    nQ = ""
    for c in Q:
        if c not in R:
            M.update(c)
        else:
            M.update(R[c])
    print M.hexdigest()
