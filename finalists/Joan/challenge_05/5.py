#!/usr/bin/env python


from datetime import timedelta
import datetime

import sys

#Cost of the leds (old clock)
led_vec = [6,2,5,5,4,5,6,3,7,6]

#Cost of changes (new clock)
led_new = {(0,1):0,(1,2):4, (2,3):1,(2,0):2,(3,4):1,(3,0):2,(4,5):2,(5,6):1,(5,0):2,(6,7):1,(7,8):4,(8,9):0,(9,0):1}

#Compute the cost of a second in the new
def getLedsNew(seconds):

   s = seconds%86400

   if s == 0:
    return 10
   ant = s -1

   diff = 0

      
   h = s/3600
   s -= h*3600

   h2 = h/10
   h1 = h%10
   
   hant = ant/3600

   ant -= hant*3600
    
   h2ant = hant/10
   h1ant = hant%10

   m = s/60
   s -= m*60

   mant = ant/60
   ant -= mant*60

   m2 = m/10
   m1 = m%10

   m2ant = mant/10
   m1ant = mant%10

   s2 = s/10
   s1 = s%10

   s2ant = ant/10
   s1ant = ant%10
   #calc diff

#   print h2ant, h1ant, m2ant, m1ant, s2ant, s1ant, "->", h2, h1, m2, m1, s2, s1
   if h2ant != h2:
       diff += led_new[(h2ant,h2)]
   if h1ant != h1:
       diff += led_new[(h1ant,h1)]
   if m2ant != m2:
       diff += led_new[(m2ant,m2)]
   if m1ant != m1:    
       diff += led_new[(m1ant,m1)]
   if s2ant != s2:
       diff += led_new[(s2ant,s2)]
   if s1ant != s1:
       diff += led_new[(s1ant,s1)]
   
   return diff
def getLedsOld(seconds):
  s = seconds%86400
#  s = seconds
  h = s/3600
  s -= h*3600

  h2 = h/10
  h1 = h%10
 
  m = s/60
  s -= m*60

  m2 = m/10
  m1 = m%10

  s2 = s/10
  s1 = s%10

  suma = led_vec[h2]+led_vec[h1]+led_vec[m2]+led_vec[m1]+led_vec[s2]+led_vec[s1]

#  print "Hora", seconds, h2, h1, m2, m1, s2, s1, suma 
  return suma

#Precalculate the cost of a day
cost_day2 = 36

for s in range(86400):
    cost_day2 += getLedsNew(s)

#exit()

cost_day = 36
for s in range(86400):
  cost_day += getLedsOld(s)

#print "Cost days", cost_day, cost_day2
import sys

if __name__ == '__main__':
    
    for s in sys.stdin:
        f = s.split()

        (year1,month1,day1) = f[0].split("-")
        (hour1,min1,sec1) = f[1].split(":")
        
#        print year1, month1, day1, hour1, min1, sec1


        (year2,month2,day2) = f[3].split("-")
        (hour2,min2,sec2) = f[4].split(":")
        
#        print year2, month2, day2, hour2, min2, sec2


        date1 = datetime.datetime(int(year1),int(month1), int(day1), int(hour1),int(min1),int(sec1))
        date2 = datetime.datetime(int(year2),int(month2), int(day2), int(hour2),int(min2),int(sec2))

        dt = date2-date1
        #Cost of the days
        ini = date1.hour*3600+date1.minute*60+date1.second
        total = getLedsOld(ini)+ dt.days*cost_day
        #total2 = 
        total2 = getLedsOld(ini)+dt.days*cost_day2
         
       # The rest seconds
        for s in range(1,dt.seconds+1):
            total+= getLedsOld(ini+s)
            total2+= getLedsNew(ini+s)
        print total - total2
