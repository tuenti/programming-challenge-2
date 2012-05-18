#!/usr/bin/env python
# -*- coding: utf-8 -*-

# *** Challenge 8: The demented cloning machine ***
#
# Steve!!. This machine is getting out of control like the FLDSMDFR !!!!


import sys
import re
import hashlib


hash_md5 = hashlib.md5()
   

if __name__ == '__main__':
    queue = sys.stdin.readline().rstrip('\r\n')
    
    # This is a list with maps, one for every case
    transformations = []

    for line in sys.stdin:
        l = line.rstrip('\r\n').split(',')
        transf_dict = {}
        for t in l:
            m = re.match(r"(.+)=>(.+)", t)
            if m is None:
                continue

            transf_dict[m.group(1)] = m.group(2)

        transformations.append(transf_dict)   

    # This dictionary will contain the final transformation for each person
    final_transformation = {}
    set_of_people = set([x for x in queue])

    # Precalculate the final clones for each person
    for person in set_of_people:
        clones = person
        # Try every transformation
        for t in transformations:
            new_clones = ""
            for c in clones:
                if c in t:
                    new_clones += t[c]
                else:
                    new_clones += c

            clones = new_clones

        final_transformation[person] = clones
            
   
    hash_md5 = hashlib.md5()
    
    for person in queue:
        hash_md5.update(final_transformation[person])

    print ''.join([ "%02x" % ord(x) for x in hash_md5.digest() ])
   

