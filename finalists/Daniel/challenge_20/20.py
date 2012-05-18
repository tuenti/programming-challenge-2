#!/usr/bin/python

# It could run a lot faster in C/C++, but F*** IT, I'm tired of this problem! -.-
# I'm not commenting the code either. Suffer reading it as you made us suffer with this problem! Just kidding xD
# The test input runs in about 12 minutes in a Core i5 1.7GHz, using the full power of all 4 (virtual) cores (but still, it's Python...).

import sys, multiprocessing
# Requires PyCrypto
from Crypto.Cipher import DES, AES
from itertools import product
import string

# The keys are compossed of lowercase letters and numbers. Since the last bit is not relevant (parity),
# select only the "even" characters.
letters = string.ascii_lowercase + string.digits + "`" # "`" is ord 96, 97 is "a"
letters = ''.join(filter(lambda x: ord(x)%2==0, letters))
alphabet = "0123456789abcdef"

def decrypt_game(g):
	
	# convert hexadecimal input into array of chars
 	msg = []
	counter = 1
	acc = 0
	for ch in g:
		acc <<= 4
		acc |= alphabet.index(ch)
		if counter == 0:
			msg.append(chr(acc))
			acc = 0
			counter = 1
		else:
			counter -= 1
	msg = ''.join(msg)
	
	# This is the real deal
	for k in product(letters, repeat=4):
		dec = DES.new(''.join(k) + "0000").decrypt(msg)
		if dec[:4] == "Key=" and dec[20:30] == " & Puzzle=":
			return dec[4:20]


def main(d):
	# Decode hexadecimal input into array of chars
	msg = []
	counter = 1
	acc = 0
	for ch in d['code']:
		acc <<= 4
		acc |= alphabet.index(ch)
		if counter == 0:
			msg.append(chr(acc))
			acc = 0
			counter = 1
		else:
			counter -= 1
	code = ''.join(msg)
	
	# Decode each game and try the key against the encrypted message
	for g in d['games']:
		k = decrypt_game(g)
		dec = AES.new(k).decrypt(code)
		
		pad = ord(dec[-1]) # padding char
		if pad > 16:
			continue
		padding_correct = True
		for p in dec[-pad:]: # check if padding is correct
			if ord(p) != pad:
				padding_correct = False
				break
		if not padding_correct:
			continue
		# Message has correct padding, this is possibly a good decrypted message. Discard padding
		real_msg = dec[:-pad]
		
		msg_correct = True
		for ch in real_msg:
			if ord(ch) < 32 or ord(ch) > 126: # Check if all characters are printable
				msg_correct = False
				break
		if not msg_correct:
			continue
		return real_msg


def parse_input():
	# The input is parsed into a list of dictionaries, one for each test case
	data = []
	input_dump = open("input.txt", "w")
	for line in sys.stdin:
		d = dict()
		input_dump.write(line)
		
		line = line.split("\n")[0]
		
		d['code'], d['games'] = line.split(":")
		d['games'] = d['games'].split("~")
		
		data.append(d)
	input_dump.close()
	return data


if __name__ == '__main__':
	data = parse_input()
	# Taking advantage of multi-core systems
	pool = multiprocessing.Pool(processes=multiprocessing.cpu_count())
	for n, result in enumerate(pool.map(main, data)):
		print result
