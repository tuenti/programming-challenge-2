#!/usr/bin/env python
# -*- coding: utf-8 -*-


# *** Challenge 18: SOP (Sheep Oriented Programming) ***

# This Challenge has Super Cow Powers.
#
#
#         (__) 
#         (oo) 
#   /------\/ 
#  / |    ||   
# *  /\---/\ 
#    ~~   ~~   
#...."Have you mooed today?"...
#
# Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo.
# Moo. Moo. Moo. Moo! Moo? Moo! Moo! Moo. Moo? Moo. Moo. Moo. Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo? Moo. Moo?
# Moo! Moo. Moo? Moo. Moo. Moo. Moo. Moo. Moo. Moo! Moo. Moo? Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo. Moo! Moo? Moo! Moo! Moo. Moo? Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo? Moo. Moo? Moo! Moo. Moo? Moo. Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo! Moo. Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo. Moo?
# Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo.
# Moo. Moo. Moo! Moo? Moo! Moo! Moo. Moo? Moo! Moo! Moo! Moo! Moo! Moo! Moo!
# Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo? Moo. Moo? Moo! Moo. Moo?
# Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo. Moo? Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo.
# Moo! Moo? Moo! Moo! Moo. Moo? Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo? Moo. Moo? Moo! Moo. Moo? Moo. Moo.
# Moo. Moo. Moo. Moo. Moo! Moo. Moo! Moo! Moo! Moo! Moo! Moo. Moo? Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo! Moo? Moo! Moo! Moo. Moo? Moo. Moo. Moo. Moo.
# Moo. Moo. Moo? Moo. Moo? Moo! Moo. Moo? Moo. Moo. Moo! Moo. Moo! Moo! Moo!
# Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo. Moo? Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo!
# Moo? Moo! Moo! Moo. Moo? Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo!
# Moo! Moo! Moo! Moo! Moo! Moo! Moo? Moo. Moo? Moo! Moo. Moo? Moo! Moo! Moo!
# Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo. Moo? Moo. Moo. Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo! Moo? Moo!
# Moo! Moo. Moo? Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo? Moo. Moo? Moo! Moo. Moo? Moo. Moo. Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo! Moo.
# Moo? Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo! Moo? Moo! Moo! Moo. Moo? Moo.
# Moo. Moo. Moo. Moo. Moo. Moo? Moo. Moo? Moo! Moo. Moo? Moo. Moo. Moo! Moo.
# Moo? Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo! Moo? Moo! Moo! Moo. Moo? Moo! Moo! Moo! Moo!
# Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo?
# Moo. Moo? Moo! Moo. Moo? Moo! Moo! Moo! Moo! Moo! Moo. Moo? Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo!
# Moo? Moo! Moo! Moo. Moo? Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo. Moo? Moo. Moo? Moo! Moo. Moo? Moo. Moo. Moo!
# Moo. Moo? Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo! Moo? Moo! Moo! Moo. Moo? Moo! Moo! Moo! Moo! Moo!
# Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo? Moo. Moo? Moo!
# Moo. Moo? Moo! Moo! Moo! Moo. Moo? Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo! Moo? Moo! Moo! Moo. Moo?
# Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo.
# Moo. Moo? Moo. Moo? Moo! Moo. Moo? Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo.
# Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo. Moo.
# Moo. Moo! Moo. Moo! Moo! Moo! Moo! Moo! Moo! Moo! Moo. Moo! Moo! Moo! Moo!
# Moo! Moo! Moo! Moo! Moo! Moo. Moo? Moo.

import sys

if __name__ == '__main__':
	num_cases = int(sys.stdin.readline())

	for ncase in range(num_cases):
		N = int(sys.stdin.readline())
		print "Case #%d: %d" % (ncase + 1, ((N ** 2) + N + 2) / 2)
		
