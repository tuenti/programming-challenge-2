#!/usr/bin/env python
# -*- coding: utf-8 -*-


import Image
import sys

img_file = sys.argv[1]

img = Image.open(img_file)
data = img.load()
cols, rows = img.size

t = []
end = False
for y in range(rows):
    for x in range(cols):
            p = list(data[x, y])
            for i in [0,1,2]:
                t.append(p[i]%2)

#data = data[:-(len(data)%3)-7]

#print ( len(t) )
key = ''
y = 0
while y < len(t):
    c = t[y:y+8]
    y += 8
    c = '0b' + str.join('', [str(x) for x in c])
    c = eval(c)
    if c == 0:
        break
    key += chr(c)

print key


