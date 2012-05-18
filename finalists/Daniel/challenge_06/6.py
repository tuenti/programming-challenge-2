#!/usr/bin/python
# I recommend using "PyPy" instead, it's a lot faster on algorithmic code

import sys, multiprocessing
from math import ceil

# The real algorithm starts here:
def main(d):
	h = d['h'] * d['ct']
	w = d['w'] * d['ct']
	font_size = h # One big line
	total_len = sum(d['len_words'])
	fits = (total_len + len(d['len_words']) - 1) * font_size <= w
	if not fits:
		tmp_font_size = (w // max(d['len_words'])) + 1 # line for the longest word (+1, because it will decrease in the loop
		font_size = min(font_size, tmp_font_size)
		
	while not fits:
		font_size -= 1
		fits = True
		max_lines = h // font_size
		chars_per_line = w // font_size
		#print font_size, max_lines, chars_per_line
		
		current_line = 0
		current_column = 0
		for l in d['len_words']:
			#print l
			#print current_line, current_column
			if current_column != 0:
				current_column += 1 # space
			current_column += l
			if current_column > chars_per_line:
				current_line += 1
				if current_line >= max_lines:
					fits = False
					break
				current_column = l
		
	#print font_size
	result = (1.0 / d['ct']) * (font_size**2)/2.0 * total_len
	return int(ceil(result))


def parse_input():
	# The input is parsed into a list of dictionaries, one for each test case
	data = []
	input_dump = open("input.txt", "w")
	line = sys.stdin.readline()
	input_dump.write(line)
	n = int(line)
	for i in xrange(n):
		line1 = sys.stdin.readline()
		line2 = sys.stdin.readline()
		input_dump.write(line1)
		input_dump.write(line2)
		d = dict()
		
		d['w'], d['h'], d['ct'] = map(int, line1.split())
		d['len_words'] = map(len, line2.split("\n")[0].split())
		if d['len_words'][-1] == 0:
			d['len_words'].pop()		

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
		print("Case #" + str(n+1) + ": " + str(result))
