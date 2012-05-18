#!/usr/bin/python
# I recommend using "PyPy" instead, it's a lot faster on algorithmic code

import sys, multiprocessing
import hashlib

# The real algorithm starts here:
def main(d):
	result = data['queue']
	md5 = hashlib.md5()
	memoized = dict()
	for r in result:
		rs = r
		if r in memoized:
			m = memoized[r]
		else:
			for row in data['transforms']:
				new_queue = []
				for p in rs:
					if p in row:
						new_queue += row[p]
					else:
						new_queue.append(p)
				rs = new_queue
			m = ''.join(rs)
			memoized[r] = m
		md5.update(m)
	return md5.hexdigest()


def parse_input():
	# The input is parsed into a list of dictionaries, one for each test case
	data = dict()
	line = sys.stdin.readline()
	input_dump = open("input.txt", "w")
	input_dump.write(line)
	data['queue'] = list(line.split("\n")[0])
	data['transforms'] = []
	for line in sys.stdin:
		input_dump.write(line)
		all_t = dict()
		for t in line.split("\n")[0].split(","):
			chunks = t.split("=>")
			all_t[chunks[0]] = list(chunks[1])
		data['transforms'].append(all_t)

	input_dump.close()
	return data


if __name__ == '__main__':
	data = parse_input()
	print(main(data))
