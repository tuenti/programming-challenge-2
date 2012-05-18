#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division
input = raw_input

tmp = [('A E I L N O R S T U', 1), ('D G', 2), ('B C M P', 3), ('F H V W Y', 4),
    ('K', 5), ('J X', 8), ('Q Z', 10)]
points = {}
for v, p in tmp:
    for l in v:
        if l.isalpha():
            points[l] = p

def score(w):
    ''' returns the score of a w '''
    return sum([points[c] for c in w.upper()])

def match(w1, w2):
    ''' true if w2 can be created with the letters form w1. '''
    for c in w2:
        if w1.count(c) < w2.count(c):
            return False
    return True

if __name__ == '__main__':
    # reads dictionary
    with open('descrambler_wordlist.txt') as fin:
        d = {l.strip():score(l.strip()) for l in fin.readlines()}
    # words indexed by letter
    index = {c:[] for c in points}
    for w,s in d.items():
        for c in w:
            index[c].append(w)
    
    C = int(input())
    for c in range(C):
        letters, word = input().split()
        
        best_word, best_score = None, 0
        for l in word:
            cl = letters+l
            for w in index[l]:
                if match(cl, w):
                    if d[w] > best_score:
                        best_score = d[w]
                        best_word = w
                    if d[w] == best_score and best_word > w:
                        best_word = w
        
        print(best_word, best_score)

