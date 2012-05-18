#!/usr/bin/env python
# -*- coding: utf-8 -*-

# *** Challenge 7: The "secure" password ***

import sys

# The key is the letter we are looking for and the value is a list of all the letters
# that SHOULD be present before in the final password
letters_before = {}


def generate_passwords(text, required_length, l):
    """ Try to complete a password until a required length 

    text - Text of the password we should complete
    required_length - The required length of the password
    l - List to store the found possible passwords
    """
    c = text[-1:]

    # If the password is complete, store it and return
    if len(text) == required_length:
        l.append(text)
        return
    
    # Now we are going to try with all the letters
    for c_after in letters_before.keys():
        # The letters can only appear once in the password
        if c_after not in text:
            # Check that all the required letters are already in the text
            all_required = True
            for c_before in letters_before[c_after]:
                if c_before not in text:
                    all_required = False
                    break

            if all_required:
                generate_passwords(text + c_after, required_length, l)


if __name__ == '__main__':

    for line in sys.stdin:
        line = line.rstrip('\r\n')

        # Fill the letters_before dictionary
        for i in range(len(line)):
            c = line[i]
            if c not in letters_before:
                letters_before[c] = []

            for j in range(0, i):
                c_before = line[j]
                if c_before not in letters_before[c]:
                    letters_before[c].append(c_before)
                    

    password_length = len(letters_before)

    # Now we search the letters that don't have to have any
    # letter before. They are the ones that can be used as
    # a first letter in the password
    first_letters = []
    for letter, l in letters_before.items():
        if len(l) == 0:
            first_letters.append(letter)

    # Try to generate password starting with each possible first_letter
    l = []
    for first in first_letters:
        generate_passwords(first, password_length, l)

    l.sort()

    for password in l:
        print password


