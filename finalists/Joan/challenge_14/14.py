#!/usr/bin/env python
import sys
import math



#Hamming decoding algorithm for 7 bits
def hamming(T):
   

    #Parity bits
    P1 = T[0]
    P2 = T[1]
    P3 = T[3]

    #Check parity
    p1 = 0
    p2 = 0
    p3 = 0
    
    if P1 != (T[2]^T[4]^T[6]):
        p1 = 1
        
    
    if P2 != T[2]^T[5]^T[6]:
        p2 = 1
    
    
    if P3 != T[4]^T[5]^T[6]:
        p3 = 1

    #if there is any mistake correct the wrong byte
    if p3+p2+p1 > 0:
        err = p3*4+p2*2+p1-1
#        assert err<7,"err: %d"% err
        if T[err] == 1:
            T[err] = 0
        else:
            T[err] = 1

    #return the decoded 4 bits
    return [str(T[j]) for j in range(7) if j not in [0,1,3]]

if __name__ == '__main__':

    for s in sys.stdin:
          
        sc = s.replace("\n","")
        N = len(sc)
        code = [int(i) for i in sc]

        #Chek if can decode
        if N%7 != 0:
            print "Error!"
            continue

        y = 7
        message = ""

        #Iterate 7 bits
        while y <= N:
            T = code[y-7:y]
            y+=7

            #Add the decoding message 
            message+= ''.join(hamming(T))

        #print message
        decoded = ""

        N = len(message)

        #Iterate over the decoded message to extract 8 bits ascii message
#        print N
        y = 8
        while y <= N:
            T = message[y-8:y]
            
            asc = (int(T,2))
            #if the ascii code is wrong
            if asc > 127:
                print "Error!"
                break
            decoded += chr(asc)
            y+=8
        else:
            #if no error
            print decoded

