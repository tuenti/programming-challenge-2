#!/usr/bin/env python
# -*- coding: utf-8 -*-

# *** Challenge 12: Three keys one cup ***
#
# The Triforce consists of three separate triangles: 
# - The Triforce of Power on top
# - The Triforce of Courage on the right
# - The Triforce of Wisdom on the left
#
# The keys are MD5 of the words "power", "courage" and "wisdom"
#
# power: The LSB bits of the RGB pixels in the first scanline give the ASCII of the MD5
# courage: The decoded QR on the right side of the image
# wisdom: The comment of the image



import sys

keys = [ "62cd275989e78ee56a81f0265a87562e",    # power
         "ed8ce15da9b7b5e2ee70634cc235e363",    # courage
         "a541714a17804ac281e6ddda5b707952",    # wisdom
       ]


if __name__ == '__main__':
    sum = sys.stdin.readline().rstrip()
    keys.append(sum)

    result = ""
    for i in range(len(keys[0])):
        s = 0
        for j in range(len(keys)):
            s += int(keys[j][i],16)
    
        s %= 16
        result += "%x" % s

    print result


''' Code used to extract the MD5 from the top scanline:
import Image

im = Image.open("CANTTF.png")

width = im.size[0]
pix = im.load()

bits = ""

for x in range(86):
    r = bin(pix[x,0][0])[2:]
    g = bin(pix[x,0][1])[2:]
    b = bin(pix[x,0][2])[2:]

    bits += r[-1]
    bits += g[-1]
    bits += b[-1]
    


bits = bits[:256]

n = []
for i in range(0, len(bits), 8):
    n.append(int(bits[i:i+8], 2))

print "".join(map(chr, n))

'''
