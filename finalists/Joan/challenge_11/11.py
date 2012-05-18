#!/usr/bin/env python
import os
import collections


JOKER_CHAR = '*'

 

#TODO: Read from file
score_dic = {'A':1,'B':3,'C':3,'D':2,'E':1,'F':4,\
                  'G':2,'H':4,'I':1,'J':8,'K':5,'L':1,'M':3,'N':1,'O':1,'P':3,\
                  'Q':10,'R':1,'S':1,'T':1,'U':1,'V':4,'W':4,'Y':4,'X':8,'Z':10}



#Return the score of a word
def scoreLetters(w):
    
    p = 0
    
   
        
    for l in w:       
        if l in score_dic:
           p += score_dic[l]
    return p



class DicCount:
    def __init__(self,voc):
        #load dict in memory
        self.dwords =[]
        fw = open(voc,"r")
        
        for w in fw:
            
            word = w.strip().replace("\n","")
            #word = w.stripno().replace("\n","").lower()
            
            self.dwords.append([word,scoreLetters(word)])
            
    
     
    def returnMaxWords(self,word,board):
        
        max_word = ""
        max_score = 0
        
        #iterate each word
        for (w,s) in self.dwords:
                        
            lw = len(w)
            w2 = w
            #replace one per one character
            for o in word:
                w2 = w2.replace(o,"",1)
                
                #if fits with the board letters
                if len(w2) == 1 and w2 in board:
                    if s > max_score:
                       max_score = s
                       max_word = w
       
        return (max_word,max_score)
    

default_dic = os.path.join(os.path.dirname(__file__),"descrambler_wordlist.txt")

#Preload the dict

Dic = DicCount(default_dic)

import sys

if __name__ =="__main__":

    
    ncases = int(sys.stdin.readline())
    
    for nc in range(ncases):
               
        (rack, board) = sys.stdin.readline().split()
#        print rack, board
        print "%s %d" %  Dic.returnMaxWords(rack,board)

            
