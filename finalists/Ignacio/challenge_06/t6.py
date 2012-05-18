#!/usr/bin/env python
# -*- coding: utf-8 -*-

# *** Challenge 6: Cross-stitched fonts ***
# What a fabric!

import sys
import math

num_cases = int(sys.stdin.readline())

for nline in range(num_cases):
    W, H, ct = map(int, sys.stdin.readline().split())
    words = sys.stdin.readline().split()

    W_px = W * ct
    H_px = H * ct
    thread_per_stitch = 1.0 / ct

    longest_word_len = max(map(len, words))

    # Use the longest_word to calculate the maximum posible font_size
    max_font_size = min (int(math.floor(float(W_px) / longest_word_len)), H_px)
    
    font_size = max_font_size

    # Try different font size until one fits or 0
    while font_size > 0:
        x, y = 0, 0
        text_fits = True
        for word in words:
            word_width = len(word) * font_size
            if x + word_width <= W_px:
                x += word_width
                x += font_size  # Space for next word
            elif y + font_size <= H_px - font_size:
                y += font_size
                x = word_width + font_size # Space for next word
            else:
                font_size -= 1
                text_fits = False
                break
        
        # If the text fitted, we're done
        if text_fits:
            break

        
    minimum_thread = 0
    if font_size > 0:
        number_of_letters = sum(map(len,words))
        total_stitches = number_of_letters * ((font_size ** 2) / 2.0)
        minimum_thread = int(math.ceil(total_stitches * thread_per_stitch))
    
    print "Case #" + str(nline + 1) + ": " + str(minimum_thread)

