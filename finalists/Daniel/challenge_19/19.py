#!/usr/bin/python

import sys, multiprocessing
import base64

def main(input):
	
	input = base64.b64decode(input)
	# Ok, let's start. First, put the input into an array of 32 bit integers
	alphabet = "0123456789abcdef"
	n_input = []
	counter = 7
	acc = 0
	for ch in input:
		acc <<= 4
		acc |= alphabet.index(ch)
		if counter == 0:
			n_input.append(acc)
			acc = 0
			counter = 7
		else:
			counter -= 1
	# Output will be a bit array
	output = []
	previous_value = 0
	# iterate through the input integers
	for i in n_input:
		# Compute the difference with the previous integer
		diff = i - previous_value
		if -0x10 <= diff <= 0xf: # if diff can be represented with 5 bits (sign included)
			# store a "0", then the diff in 5 bits
			output.append(0)
			# convert to positive
			if diff < 0:
				diff += 0x10
				diff |= 0x10
			bit = 5
			while bit:
				bit -= 1
				output.append((diff & (1 << bit)) >> bit)
		else:
			# store a "1", then the full integer value
			output.append(1)
			bit = 32
			while bit:
				bit -= 1
				output.append((i & (1 << bit)) >> bit)
		previous_value = i
	output.append(0)
	
	# now, compress the bit array into an hexadecimal one
	hex_output = []
	counter = 3
	acc = 0
	for b in output:
		acc <<= 1
		acc |= b
		if counter == 0:
			hex_output.append(alphabet[acc])
			acc = 0
			counter = 3
		else:
			counter -= 1
	if counter != 3:
		hex_output.append(alphabet[acc])
	
	# aaaand, last but not least, encode it in base64
	encoded_output = base64.b64encode(''.join(hex_output))
	# strip the padding ("==")
	encoded_output = encoded_output.split("=")[0]
	
	return encoded_output


if __name__ == '__main__':
	print(main(sys.stdin.read()))
