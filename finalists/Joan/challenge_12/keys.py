#!/usr/bin/env python


#key1 = "a182"
#key2 = "1357"
#key3 = "23f1"

#key 1: was coded in the hex code of the image.
#key 2: was extracted applying module 2 at each pixel and component, and codifiying the result as an hex character set.
#key 3: is the qr code in the image

key1 = "a541714a17804ac281e6ddda5b707952"
#key2 = "482a9a4cd222fc2086c52698893e6b22"
key2 = "62cd275989e78ee56a81f0265a87562e"
key3 = "ed8ce15da9b7b5e2ee70634cc235e363"
def getkey(key):

    fkey = ""
    for k in range(len(key)):
        aux = int(key1[k],16)+int(key2[k],16)+int(key3[k],16)+int(key[k],16)
        aux = aux%16
        fkey+="%x"%aux
    
    return fkey

import sys

if __name__ == '__main__':
   indigit = sys.stdin.readline().replace("\n","")

    
   print getkey(indigit)
