#!/usr/bin/python
# I recommend using "PyPy" instead, it's a lot faster on algorithmic code

import sys, multiprocessing


# The real algorithm starts here:
def main(d):
	words = []
	for w in d:
		words.append(list(w))
	used_chars = set()
	for w in words:
		used_chars.update(w)
	password_len = len(used_chars)
	posibilities = [[]]
	for i in xrange(len(used_chars)):
		new_posibilities = []
		for p in posibilities:
			for ch in used_chars.difference(set(p)): # iterate through available chars
				tmp_p = p + [ch]
				valid = True
				for w in words:
					for cw in w:
						if cw in tmp_p:
							for cw2 in w:
								if cw == cw2:
									break
								if not cw2 in tmp_p:
									valid = False
									break
						else:
							for cw2 in w[::-1]:
								if cw == cw2:
									break
								if cw2 in tmp_p:
									valid = False
									break
						if not valid:
							break
					if not valid:
						break
				if valid:
					new_posibilities.append(tmp_p)
				
		posibilities = new_posibilities
	return sorted(map(lambda x: ''.join(x), posibilities)[::-1])


def parse_input():
	# The input is parsed into a list of dictionaries, one for each test case
	data = []
	input_dump = open("input.txt", "w")
	for line in sys.stdin:
		input_dump.write(line)
		d = dict()

		d = line.split("\n")[0]

		data.append(d)
	input_dump.close()
	return data


if __name__ == '__main__':
	data = parse_input()
	# Taking advantage of multi-core systems
	print '\n'.join(main(data))
