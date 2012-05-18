#!/usr/bin/python
# I recommend using "PyPy" instead, it's a lot faster on algorithmic code

import sys, multiprocessing
import string

pad = [[   " 1",  "abc2",  "def3"],
		["ghi4",  "jkl5",  "mno6"],
		["pqrs7", "tuv8", "wxyz9"],
		[    "",    "0",      ""]]
dict_pad = dict()
for ch in string.ascii_lowercase + string.digits + " ":
	for row in xrange(len(pad)):
		for col in xrange(len(pad[row])):
			if ch in pad[row][col]:
				dict_pad[ch] = (row, col)

diagonal = 350
lateral = 200
updown = 300
press = 100
wait = 500
init = (3, 1)
caps_lock_location = (3, 2)
init_caps_lock = False

def cost_move(start, end):
	if start == end:
		return 500
	diff = (abs(end[0] - start[0]), abs(end[1] - start[1]))
	cost = diagonal * min(diff)
	if diff[0] > diff[1]: # more rows than columns
		cost += updown * (diff[0] - diff[1])
	else: # more columns than rows
		cost += lateral * (diff[1] - diff[0])
	return cost

# The real algorithm starts here:
def main(d):
	result = 0
	caps_lock = init_caps_lock
	position = init
	for ch in d["line"]:
		if (caps_lock and ch.islower()) or (not caps_lock and ch.isupper()):
			result += cost_move(position, caps_lock_location)
			result += press
			position = caps_lock_location
			caps_lock = not caps_lock
		key = dict_pad[ch.lower()]
		letters = pad[key[0]][key[1]]
		result += cost_move(position, key)
		result += press * (letters.index(ch.lower()) + 1)
		position = key
	return result


def parse_input():
	# The input is parsed into a list of dictionaries, one for each test case
	data = []
	input_dump = open("input.txt", "w")
	n = raw_input()
	
	for line in sys.stdin:
		input_dump.write(line)
		d = dict()

		d['line'] = line.split("\n")[0]

		data.append(d)
	input_dump.close()
	return data


if __name__ == '__main__':
	data = parse_input()
	# Taking advantage of multi-core systems
	pool = multiprocessing.Pool(processes=multiprocessing.cpu_count())
	for n, result in enumerate(pool.map(main, data)):
	#for n, d in enumerate(data):
	#	 result = main(d)
		print(str(result))
