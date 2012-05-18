#!/usr/bin/python
# I recommend using "PyPy" instead, it's a lot faster on algorithmic code

import sys, multiprocessing

def ones(number):
	ones = 0
	while number:
		if number & 1:
			ones += 1
		number >>= 1
	return ones

def zeroes(number):
	zeroes = 0
	while number:
		if not (number & 1):
			zeroes += 1
		number >>= 1
	return zeroes

# The real algorithm starts here:
def main(d):
	number = d['number']
	with_carry = -99
	without_carry = 0
	while number:
		digit = number & 1
		number >>= 1
		#print digit,
		if digit: # 1
			# 1 + 1 + C = (C)
			# 1 + 0
			# 0 + 0 + C
			# without carry: 1 + 0 or 0 + 0 + C
			without_carry = max(without_carry + 1, with_carry)
			# with carry: 1 + 1 + C = (C)
			with_carry = with_carry + 2
		else: # 0
			# 1 + 1 = (C)
			# 1 + 0 + C = (C)
			# 0 + 0
			# without carry: 0 + 0
			#without_carry = without_carry
			# with carry: 1 + 1 = (C) or 1 + 0 + C = (C)
			with_carry = max(without_carry + 2, with_carry + 1)
#	print
#	print with_carry, without_carry
	return without_carry


def parse_input():
	# The input is parsed into a list of dictionaries, one for each test case
	data = []
	input_dump = open("input.txt", "w")
	n = int(raw_input())
	for line in sys.stdin:
		input_dump.write(line)
		d = dict()

		d['number'] = int(line)

		data.append(d)
	input_dump.close()
	return data


if __name__ == '__main__':
	data = parse_input()
	# Taking advantage of multi-core systems
	pool = multiprocessing.Pool(processes=multiprocessing.cpu_count())
	for n, result in enumerate(pool.map(main, data)):
	#for n, d in enumerate(data):
	#	result = main(d)
		print("Case #" + str(n+1) + ": " + str(result))
