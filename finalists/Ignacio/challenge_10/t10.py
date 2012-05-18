#!/usr/bin/env python
# -*- coding: utf-8 -*-

# *** Challenge 10: Coding m00re and m00re ***

import sys
import re

for line in sys.stdin:
    operations = line.rstrip('\r\n').split()

    stack = []

    for op in operations:
        if re.match(r"\d+$", op):       # Add integer to the stack
            stack.append(int(op))

        elif op == ".":                 # Pop and print
            print stack.pop()

        elif op == "mirror":            # Negate the last element
            stack.append(-stack.pop())

        elif op == "breadandfish":      # Copy the last element
            stack.append(stack[-1])

        elif op == "#":                 # Multiply
            n2 = stack.pop()
            n1 = stack.pop()
            stack.append(n1 * n2)

        elif op == "fire":              # Discard last element
            stack.pop()

        elif op == "$":                 # Substract
            n2 = stack.pop()
            n1 = stack.pop()
            stack.append(n1 - n2)

        elif op == "dance":             # Swap the order of the last 2 elements
            stack[-1], stack[-2] = stack[-2], stack[-1]

        elif op == "conquer":           # Module (divide and CONQUER)
            n2 = stack.pop()
            n1 = stack.pop()
            stack.append(n1 % n2)

        elif op == "&":                 # Division
            n2 = stack.pop()
            n1 = stack.pop()
            stack.append(n1 / n2)

        elif op == "@":                 # Add
            n2 = stack.pop()
            n1 = stack.pop()
            stack.append(n1 + n2)
            

   

            
        

    
