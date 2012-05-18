#!/usr/bin/env python

import sys
import math
#Extracted of my own code of the Facebook Hacker Cup 2012 ;)
if __name__ == '__main__':
    #file_in = "small.in"
    
    #fs = open(file_in)
    
    fs = sys.stdin
    num_cases = int(fs.readline())
    
    #print num_cases
    
    def fits(h,w,box,words):
        
        haux = box
        waux = 0
        
        for cword in words:
            current_width = len(cword)*box
                          
            if waux == 0:
                if current_width > w:
                    return False
                else:
                    waux = current_width
                    
            elif waux + box + current_width > w:
                if current_width > w:
                    return False
                                     
                waux = current_width
                        
                if haux + box > h:
                    return False
                haux += box
            else:
                waux +=current_width+box
             
        return True
                  
              
        
    
    for nc in range(num_cases):
        camps = fs.readline().split()
        
        w = int(camps[0])
        h = int(camps[1])
        ct = int(camps[2])

        words = fs.readline().strip().replace("\n","").split(" ")
 #       print words 
        ncar = sum([len(x) for x in words])
        
        max_word = max([len(t) for t in words])
               
        max_cot = w/max_word
        
        box = 1
        
        #Take in account the inches
        w*=ct
        h*=ct
        #The same algorithm
        while fits(h,w,box,words) and box <= min(h,w):
            box = box + 1                           
        
        #The last one is the good one
        box-=1
        #The formula
        ctbox = float(box*box)/2
#        print box, ncar, ct
        sol = math.ceil(float(ctbox*ncar)/ct)
        print "Case #%d: %d" %(nc+1,sol)               
