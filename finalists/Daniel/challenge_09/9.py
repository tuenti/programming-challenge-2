#!/usr/bin/python
# I recommend using "PyPy" instead, it's a lot faster on algorithmic code

import sys, multiprocessing
import os

# Up to 2GB RAM... but it's fast. It'd probably be less RAM-hungry in Java or C++
# This could be easily done with a relational database, but this way is faster (provided you have enough RAM)
documents = []
def read_documents():
	for i in xrange(1, 801):
		f_name = str(i)
		documents.append(dict())
		while len(f_name) < 4:
			f_name = '0' + f_name
		f = open('documents/' + f_name)
		doc = map(lambda x: x.split(), f.read().lower().split("\n"))
		f.close()
		cur_line = 1
		for line in doc:
			col = 1
			for word in line:
				if not word in documents[-1]:
					documents[-1][word] = 0
				documents[-1][word] += 1
				col += 1
			cur_line += 1


# The real algorithm starts here:
def main(d):
	#result = documents[d['word']][d['rep'] - 1]
	#return '-'.join(map(str, result))
	counter = d['rep']
	for i in xrange(1, 801):
		if d['word'] in documents[i-1]:
			if counter > documents[i-1][d['word']]:
				counter -= documents[i-1][d['word']]
				continue
		else:
			continue
		f_name = str(i)
		while len(f_name) < 4:
			f_name = '0' + f_name
		f = open('documents/' + f_name)
		doc = map(lambda x: x.split(), f.read().lower().split("\n"))
		f.close()
		cur_line = 1
		for line in doc:
			col = 1
			for word in line:
				if word == d['word']:
					counter -= 1
					if counter == 0:
						return '-'.join(map(str, [i, cur_line, col]))
				col += 1
			cur_line += 1


def parse_input():
	# The input is parsed into a list of dictionaries, one for each test case
	data = []
	input_dump = open("input.txt", "w")
	line = sys.stdin.readline()
	input_dump.write(line)
	n = int(line)
	for line in sys.stdin:
		input_dump.write(line)
		d = dict()

		d['word'] = line.split()[0].lower()
		d['rep'] = int(line.split()[1])

		data.append(d)
	input_dump.close()
	return data


if __name__ == '__main__':
	data = parse_input()
	read_documents()
	# Taking advantage of multi-core systems
	#pool = multiprocessing.Pool(processes=multiprocessing.cpu_count())
	#for n, result in enumerate(pool.map(main, data)):
	for n, d in enumerate(data):
		result = main(d)
		print(str(result))
