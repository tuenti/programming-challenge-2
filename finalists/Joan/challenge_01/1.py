#!/usr/bin/env python

import sys



#Structure to know the position of a number
#d[letter] = (n,x,y,pos)

d= {}
d[" "] = (1,0,0,0)

#First three group members
sNum = 'abcdefghijklmno'
for a in range(len(sNum)):
    nKey = (a/3)+1
    pos = (a%3)
    x = nKey/3
    y = nKey%3
    d[sNum[a]] = (nKey+1,x,y,pos)

#Other groups
sNum = "pqrs"
for a in range(len(sNum)):
    d[sNum[a]]=(7,2,0,a)

sNum = "tuv"
for a in range(len(sNum)):
    d[sNum[a]]=(8,2,1,a)


sNum = "wxyz"
for a in range(len(sNum)):
    d[sNum[a]]=(9,2,2,a)


#Numbers
#1
d["1"] = (1,0,0,1)
d["2"] = (2,0,1,3)
d["3"] = (3,0,2,3)
d["4"] = (4,1,0,3)
d["5"] = (5,1,1,3)
d["6"] = (6,1,2,3)
d["7"] = (7,2,0,4)
d["8"] = (8,2,1,3)
d["9"] = (9,2,2,4)
d["0"] = (0,3,1,0)

d["+"] = (-1,3,2,0)

#Function to move
def movingcost(pos1,pos2):

    (x1,y1) = pos1
    (x2,y2) = pos2

    dist = 0
    
    costx = 300
    costy = 200
    costd = 350

    while True:
          if pos1 == pos2:
               return dist

          elif (x1 == x2):
                return dist+abs(y1 - y2)*costy
          elif (y1 == y2):
              return dist+abs(x1-x2)*costx
          
          else:
              #Moving in diagonal
              dist+= costd
              if x1 < x2:
                  x1 += 1
              else:
                  x1 -= 1

              if y1 < y2:
                  y1 += 1
              else:
                  y1 -= 1
    return 0

#get the position of a number
def getpos(k):
        return d[k][1:3]

#pos of the case key number
casepos = (3,2)
if __name__ == '__main__':
   

    ncases = int(sys.stdin.readline())
    for nc in range(ncases):
        
        text = sys.stdin.readline().replace("\n","")
        
        state = False
        antstate = False
        antpos = (3,1)
        
        total = 0
        for x in text:
            cost = 0

            #if is a number ignore the last state
            if x in "0123456789 ":
                state = antstate
            else:
                state = x.isupper()

            
            x = x.lower()

            # if different case-> move to the case letter
            if state != antstate:
                cost += movingcost(antpos,casepos)+100
                antpos = casepos
        #       print  "moving to case",cost
            
            pos = getpos(x)
            cost += movingcost(antpos,pos)
            #Waiting to press
            if(antpos == pos):
                cost+= 500
        #        print "waiting to press", antpos, pos

            #Pressing
            cost += (d[x][3]+1)*100
        #    print "pressing ",x

            antstate = state
            antpos = pos
            
            total += cost

        #    print "Cost of ",x, ":", cost,total
        #print "Total Cost: ",total
        print total
