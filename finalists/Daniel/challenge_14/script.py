#!/usr/bin/python
# I recommend using "PyPy" instead, it's a lot faster on algorithmic code

import sys, multiprocessing
from Hamming import Hamming

# I got the Hamming code from http://lionel.textmalaysia.com/hamming-code-in-python.html#.T5xPYu0RVVE

# The real algorithm starts here:
def main(d):
	
	result = ""
	bit_str = ""
	h = Hamming()
	if len(d['bits']) % 7: # Invalid message length
		return "Error!"
	for i in xrange(len(d['bits']) / 7):
		chunk = d['bits'][i*7:(i+1)*7]
		h.code(chunk)
		error_bit = h.check()
		if error_bit:
			bit_list = map(int, list(chunk))
			bit_list[error_bit - 1] = int(not bit_list[error_bit - 1])
			chunk = ''.join(map(str, bit_list))
			h.code(chunk)
		if h.check(): # Still error after error correcting
			return "Error!"
		bit_str += ''.join(map(str, h.data()))
	
	#print bit_str
	for i in xrange(len(bit_str) / 8):
		chunk = bit_str[i*8:(i+1)*8]
		ch = 0
		for b in chunk:
			ch <<= 1
			ch |= int(b)
		if ch < 32 or ch > 127:
			return "Error!" # Contains non-printable characters
		result += chr(ch)
	
	return result


def parse_input():
	# The input is parsed into a list of dictionaries, one for each test case
	data = []
	input_dump = open("input.txt", "w")
	for line in sys.stdin:
		input_dump.write(line)
		d = dict()

		d['bits'] = line.split("\n")[0]

		data.append(d)
	input_dump.close()
	return data


if __name__ == '__main__':
	data = parse_input()
	# Taking advantage of multi-core systems
	#pool = multiprocessing.Pool(processes=multiprocessing.cpu_count())
	#for n, result in enumerate(pool.map(main, data)):
	for n, d in enumerate(data):
		result = main(d)
		print(str(result))
