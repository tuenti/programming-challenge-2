#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division
input=raw_input
import os

def crawl(path):
    ''' stores the files in which every word appears and the counter of ocurrences. '''
    index = dict()
    for filename in sorted(os.listdir(path)):
        filepath = os.path.join(path, filename)
        fin = open(filepath)
        for nline, line in enumerate(fin):
            line = line.lower().split()
            for pos, word in enumerate(line):
                if word not in index:
                    index[word] = []
                if len(index[word]) > 0:
                    if index[word][-1][0] != filename:
                        count = index[word][-1][1]
                        index[word].append( [filename, count] )
                else:
                    index[word].append( [filename, 0] )
                last = index[word][-1]
                last[1] += 1
        fin.close()
    return index


def find(word, position, index):
    ''' finds the positionth word at the corpus '''
    word = word.lower()
    i, discount = 0, 0
    # looks for the file where the word is
    while i < len(index[word]) and position-index[word][i][1] > 0:
        discount = index[word][i][1]
        i += 1
    line, pos = find_word(word, position-discount, index[word][i][0])
    return (index[word][i][0], line, pos)


def find_word(word, pos, filename):
    ''' looks for the posth ocurrence of word in filename '''
    with open(os.path.join('documents/', filename)) as fin:
        for nline, line in enumerate(fin):
            line = line.lower().split()
            n = line.count(word)
            if pos <= n:
                i = 0
                while True:
                    if line[i] == word:
                        pos -= 1
                        if pos == 0:
                            return (nline, i)
                    i += 1
            pos -= n


if __name__ == '__main__':
    index = crawl('documents/')

    C = int(input())
    for c in range(C):
        w, p = input().split()
        p = int(p)
        filename, line, position = find(w, p, index)
        filename = int(filename, 10)
        line += 1 # index starts with 1
        position += 1
        print(filename, line, position, sep='-')

