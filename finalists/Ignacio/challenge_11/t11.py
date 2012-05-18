#!/usr/bin/env python
# -*- coding: utf-8 -*-

# *** Challenge 11: Descrambler ***

import sys

score_table = { 'A': 1, 'E': 1, 'I': 1, 'L': 1, 'N': 1, 'O': 1, 'R': 1, 'S': 1, 'T': 1, 'U': 1,
                'D': 2, 'G': 2,
                'B': 3, 'C': 3, 'M': 3, 'P': 3,
                'F': 4, 'H': 4, 'V': 4, 'W': 4, 'Y': 4,
                'K': 5,
                'J': 8, 'X': 8,
                'Q': 10, 'Z': 10 }


def count_letters(word):
    ''' Return a dictionary with keys as letters and the values are the ocurrences of each letter '''
    d = {}
    for c in word:
        if c not in d:
            d[c] = 1
        else:
            d[c] += 1

    return d


def calculate_score(word):
    ''' Calculates the score of a word '''
    score = 0
    for c in word:
        score += score_table[c]

    return score



if __name__ == '__main__':

    # First read all the dictionary and add it to a dictionary using the length of the word for the key
    dictionary = {}

    f = open('descrambler_wordlist.txt', 'r')
    for line in f:
        line = line.rstrip()
        if len(line) in dictionary:
            dictionary[len(line)].append(line)
        else:
            dictionary[len(line)] = [ line ]

    f.close()

    num_cases = int(sys.stdin.readline())

    for ncase in range(num_cases):
        line = sys.stdin.readline().rstrip()

        rack, board = line.split()
        max_word = ""
        max_score = 0

        letters_in_board = set(board)
        count_rack = count_letters(rack)
        
        max_word_length = len(rack) + 1

        for word_length in range(max_word_length, 1, -1):
            if word_length not in dictionary:
                continue

            for word in dictionary[word_length]:

                # Is it possible to obtain more points with this word?
                score = calculate_score(word)
                if score < max_score or (score == max_score and word > max_word):
                    continue

                # Check if it share any letter with the board word
                valid_candidate = False
                for c in letters_in_board:
                    if c in word:
                        valid_candidate = True
                        break

                if not valid_candidate:
                    continue

                # Check if there is a chance to make this word with our rack
                count_word = count_letters(word)
                for letter in count_word:
                    if letter in count_rack:
                        count_word[letter] -= count_rack[letter]
                
                # Sum only the positive values
                max_letters_missing = sum(map(lambda x: max(x, 0), count_word.values()));

                if max_letters_missing > 1:
                    continue    # We can't use this word

                elif max_letters_missing == 1:   # We must use the missing letter using one from the board word
                    missing_letter = [letter for letter, count in count_word.items() if count == 1]

                    if missing_letter[0] not in board:
                        continue

                # If we have reached this point, the current word is a possible winner                
                if score > max_score or (score == max_score and word < max_word):
                    max_score = score
                    max_word = word               
                        
        print max_word + " " + str(max_score)                

