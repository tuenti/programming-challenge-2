#!/usr/bin/env python

import sys
import math


#Compute the distance of a point from a rect with pendent m
def distR(m,x,y):

    return float(m*x-y)/math.sqrt((m*m)+1)


#Compute the mod of the vector and the angle
def modAngle(cx,cy,ex,ey):
        mod = math.sqrt(((cx-ex)**2)+((cy-ey)**2))

        #Using 2 angles to compute correctly the points 
        a = math.acos(float(ex-cx)/mod)%(math.pi*2)
        b = math.asin(float(ey-cy)/mod)
          
        return (mod,a,b)

#Given an angle and module generate the point
def rotateV(anglex,angley,mod):
    return (mod*math.cos(anglex),mod*math.sin(angley))

#Check if all the points are in the same zone of the pizza (finding cut)
def computePoints(m,p):

     first = p[0]
     sign = distR(m,first[0],first[1]) < 0
     
     
     for cp in p[1:]:
         if (distR(m,*cp) < 0) != sign:
          return False

     return True
        

if __name__ == "__main__":
    
    ncases = int (sys.stdin.readline())

    for nc in range(ncases):
        

        (Cx,Cy,R) = map(float,sys.stdin.readline().split())
        N = int(sys.stdin.readline())

        #List of the information of the type ingredients
        T = []

        #List of the information of each ingredient
        L = []
        
        for tp in range(N):
            (ID, edges, n) = sys.stdin.readline().split()

            edges = int(edges)
            n = int(n)
            
            #The rotation to generate the points
            rot = (2*math.pi)/edges

            T.append((tp,n,edges))
            
            l = []
            for i in range(n):
                
                 
                ingredient = map(float,sys.stdin.readline().split())
               
                ingredient[0]-=Cx
                ingredient[1]-=Cy
                ingredient[2]-=Cx
                ingredient[3]-=Cy
                (mod,anglex,angley) = modAngle(*ingredient)
                l.append(ingredient)
                 
                p = (ingredient[-2],ingredient[-1])
                points = []
                
                #Generate the rotating points
                for e in range(edges):

                    anglex2 = (anglex+ e*rot)#%(2*math.pi)
                    angley2 = (angley+e*rot)
                    p = rotateV(anglex2,angley2,mod)
                    p = (p[0]+ingredient[0],p[1]+ingredient[1])
                    points.append(p)
                
                ingredient.append(points)
            L.append(l)


            
#            print T, L

        #The algorithm



        cut = False

        #precision of the offset of the cut
        pres = 30000
        for alpha in range(int(math.pi*pres)):
            m = math.tan(float(alpha)/pres)

            #Can we cut ;)
            liada = True
            for tp in range(N):
                #Check that there are the same quantity in each side 
                nside = 0
                for ing in L[tp]:
                    d = distR(m,ing[0],ing[1])
                    if d < 0:
                       nside += 1

                    else:
                       nside -= 1
            
                    #Check if the ingredient is cut
                    if not computePoints(m,ing[4]):
                           liada = False
#                           print "Cut found in :", m, p
                           break
                    
                if not liada or nside != 0:
                   liada = False
                   break

            if liada == True:
               cut = True
               break

        if liada:
            sliada = "TRUE"
        else:
            sliada = "FALSE"
        print "Case #%d: %s"%(nc+1,sliada)
