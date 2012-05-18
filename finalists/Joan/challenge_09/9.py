#!/usr/bin/env python

#Auxiliar index generator
import pickle

#The main idea is to generate a index list T, where we store for each word the ocurrences in the documents. Also we use a dict (sparse)
doc_dir = "9-magnolia/documents"
#doc_dir = "documents"
#For retrieval an ocurrence of a word, we find the document in the T list, and then search the file D the n-th ocurrence of the word
T = {}

for d in range(1,801):
    f = doc_dir+"/%04d"%d

    fs = open(f)
#    print f
    
    cl = 1
    D = {}
    #Generate the list D for the ocurrences in the file
    for line in fs:

        l = line.split()
        for w in range(len(l)):
            
            word = l[w].lower()
            if word not in D:
                D[word] =1
            else:
                D[word] += 1
    
    #Update the T #ocurrences file
    for w in D:
        if w in T:
            T[w].append((d,D[w]))
        else:
            T[w] = [(d,D[w])]
    fs.close()

import pickle
import sys

#find the word inside the document
def find_word(doc, word, oc):
    fs = open(doc_dir+"/%04d"%doc)
    
    i = 0
    cl = 1
    for line in fs:
        l = line.lower().split()
        
        for w in range(len(l)):
            cw = l[w]
            if word == cw:
                
                i = i+1
                if i == oc:
                    fs.close()
                    return(cl,w+1)
        cl+=1
    fs.close()

def find_document(w,ocurrences):

    acum = 0
    for doc in T[w]:
        #print doc
        if acum + doc[1] >= ocurrences:
            d = doc[0]


            #load the document
            #We have a precomputed index file, where indicates the line and position of each ocurrence of the word in the document            

            #Check the position within the structure data
            pos = ocurrences - acum
            (l,p) = find_word(d,w,pos)
            return (d,l,p)
            
        acum += doc[1]
    return -1

if __name__ == '__main__':
    

    #Read the input
    ncases = int(sys.stdin.readline())
    for nc in range(ncases):

        (word, oc) = sys.stdin.readline().split()
        word = word.lower()
        oc = int(oc)
        #print word, oc
        
        #Find the document
        print "%d-%d-%d" % find_document(word, oc)

        
