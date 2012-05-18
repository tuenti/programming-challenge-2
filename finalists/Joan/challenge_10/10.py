#!/usr/bin/env python

import sys


#RPN
def operate(op, dig):
    

    #Print the solution
    if op == ".":
        print dig.pop()
        
    # -top
    elif op == "mirror":
        
        k = dig.pop()

        dig.append(-k)

    # replicate the top
    elif op == "breadandfish":
        k = dig.pop()
        dig.append(k)
        dig.append(k)
    # Remove the top
    elif op == "fire":
        a = dig.pop()
        #dig.append(a)
    # Multiplication
    elif op == "#":
        a = dig.pop()
        b = dig.pop()
        dig.append(a*b)

    # substraction
    elif op == "$":
        a = dig.pop()
        b = dig.pop()

        dig.append(b-a)
    # reverse
    elif op == "dance":
        dig.reverse()

    # divide and conquer ;)
    elif op == "conquer":
        a = dig.pop()
        b = dig.pop()
        dig.append(b%a)

    #Division
    elif op == "&":
        a = dig.pop()
        b = dig.pop()
        dig.append(b/a)

    #Addition
    elif op == "@":
        a = dig.pop()
        b = dig.pop()
        dig.append(a+b)

    
    else:
        #ERROR
        pass
        #print "ERROR"

if __name__ == '__main__':
    for s in sys.stdin:

   
            fields = s.split()

            dig = []

            for t in fields:
                if t.isdigit():
                    z = int(t)
                    dig.append(z)
                else:
                    operate(t,dig)
                    #k = []
    
