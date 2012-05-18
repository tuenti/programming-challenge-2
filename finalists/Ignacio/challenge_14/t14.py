#!/usr/bin/env python
# -*- coding: utf-8 -*-

# *** Challenge 14: Nails ***

import sys
import string
        
    
def decode_hamming(text):
    ''' Receives a string of 7 characters and returns a list of integer with the 4 data bits '''
    result = []
    byte = map(int,list(text))
    
    p1 = byte[3 - 1] ^ byte[5 - 1] ^ byte[7 - 1]
    p2 = byte[3 - 1] ^ byte[6 - 1] ^ byte[7 - 1]
    p4 = byte[5 - 1] ^ byte[6 - 1] ^ byte[7 - 1]

    bad_bit = 0
    if p1 != byte[1 - 1]:
        bad_bit += 1

    if p2 != byte[2 - 1]:
        bad_bit += 2

    if p4 != byte[4 - 1]:
        bad_bit += 4

    # Fix the incorrect bit
    if bad_bit != 0:
        byte[bad_bit - 1] = 1 - byte[bad_bit - 1]

    result.append(byte[3 - 1])
    result.extend(byte[5 - 1:7])

    return result
        

def bit_list_to_ascii(l):
    ''' Receives a list of integers (0 & 1) and decodes them in 8 bit chars '''
    s = ""
    for i in range(0, len(l), 8):
        s += chr(int("".join(map(str,l[i:i+8])), 2))

    return s


if __name__ == '__main__':

    for line in sys.stdin:
        data = line.rstrip()

        # We are decoding 8-bit characters, so the length has to be 14 * n_chars
        # Each 7-bit group has 4 bit of data
        if len(data) % 14 != 0:
            print "Error!"
            continue

        decoded = []

        for i in range(0, len(data), 7):
            decoded.extend(decode_hamming(data[i:i+7]))

        decoded_text = bit_list_to_ascii(decoded)
        valid = True
        for c in decoded_text:
            if c not in string.printable:
                valid = False
                break

        if valid:
            print decoded_text
        else:
            print "Error!"        


