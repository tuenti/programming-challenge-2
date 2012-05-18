#!/usr/bin/env python
# -*- coding: utf-8 -*-

# *** Challenge 19: Find the algorithm ***
#
# I don't even see the code. All I see is blonde, brunette, redhead...


import sys
import base64


def int_to_list_bits(n, min_length = 32):
	''' Converts an integer to a list of 1s and 0s of the specified length '''
	b = bin(n)[2:]

	if len(b) < min_length:
		b = ("0" * (min_length - len(b))) + b
	else:
		b = b[-min_length:]

	return map(int, [x for x in b])



if __name__ == '__main__':

	for line in sys.stdin:
		decoded = base64.b64decode(line.rstrip())

		# Convert the input to a list of integers
		list_int32 = map(lambda x: int(x,16), [decoded[i:i+8] for i in range(0,len(decoded), 8)])

		# Compression mode:
		# 1: Store the full 32-bit integer
		# 0: Store the 5-bit delta from the previous integer

		# Store the first integer in full mode
		binary_output = [ 1 ]
		previous_int32 = list_int32.pop(0)
		binary_output.extend(int_to_list_bits(previous_int32, 32))

		for int32 in list_int32:
			dif = int32 - previous_int32

			# Can the delta be fitted in 5 bits?
			if dif > 15 or dif < -16:
				binary_output.append(1)
				binary_output.extend(int_to_list_bits(int32, 32))
			else:
				binary_output.append(0)
				if dif >= 0:
					binary_output.extend(int_to_list_bits(dif, 5))
				else:
					binary_output.extend(int_to_list_bits(32 + dif, 5))
			
			previous_int32 = int32


		# Add padding to complete until byte boundary
		if len(binary_output) % 8 != 0:
			binary_output.extend([0 for i in range(8 - (len(binary_output) % 8))])

		# Convert the binary output to ASCII
		ascii_output = ""	
		for i in range(0, len(binary_output), 8):
			byte = int("".join(map(str,binary_output[i:i+8])),2)
			ascii_output += "%02x" % byte

		# Encode in base64 and remove the trailing "="
		base64_output = base64.b64encode(ascii_output)
		print base64_output.rstrip("=")
	
