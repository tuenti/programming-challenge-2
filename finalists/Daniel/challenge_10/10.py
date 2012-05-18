#!/usr/bin/python
# I recommend using "PyPy" instead, it's a lot faster on algorithmic code

import sys, multiprocessing


# The real algorithm starts here:
def main(d):
	stack = []
	for chunk in d['chunks']:
		try:
			op = int(chunk)
			stack.append(op)
		except:
			if chunk == "mirror":
				stack[-1] = -stack[-1]
			elif chunk == "#":
				stack[-2] *= stack[-1]
				stack.pop()
			elif chunk == "breadandfish":
				stack.append(stack[-1])
			elif chunk == "fire":
				stack.pop()
			elif chunk == "$":
				stack[-2] -= stack[-1]
				stack.pop()
			elif chunk == "dance":
				tmp = stack[-2]
				stack[-2] = stack[-1]
				stack[-1] = tmp
			elif chunk == "conquer":
				stack[-2] %= stack[-1]
				stack.pop()
			elif chunk == "&":
				stack[-2] /= stack[-1]
				stack.pop()
			elif chunk == "@":
				stack[-2] += stack[-1]
				stack.pop()
			elif chunk == ".":
				pass
	return stack[0]


def parse_input():
	# The input is parsed into a list of dictionaries, one for each test case
	data = []
	input_dump = open("input.txt", "w")
	for line in sys.stdin:
		input_dump.write(line)
		d = dict()

		d['chunks'] = line.split("\n")[0].split()

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
