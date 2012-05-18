"""  -*- mode: python; coding: utf-8; -*-
"""

import sys, base64

line=sys.stdin.readline()
numbers=base64.b64decode(line)
n=[]
for i in range(0, len(numbers), 8):
    n+=[int("0x"+numbers[i:i+8], 16)]

num=n[0]
pattern=""
for i in range(32):
    pattern+=(num&(1<<31)) and '1' or '0'
    num<<=1

#print "Pattern: ", pattern

sol="1"+pattern
for i in range(1, len(n)):
    diff=n[i]-n[i-1]
    if diff<=15 and diff>=-16:
        # store difference only
        sol+="0"
        for j in range(5):
            sol+=(diff&0x10) and '1' or '0'
            diff<<=1
    else:
        # store complete number
        sol+="1"
        nn=n[i]
        for j in range(32):
            sol+=(nn&(1<<31)) and '1' or '0'
            nn<<=1

while len(sol)&3: sol+='0'
solution=base64.b64encode(hex(int(sol, 2))[2:-1])
while solution[-1]=='=': solution=solution[0:-1]
print solution
