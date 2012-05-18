#!/usr/bin/python
# I recommend using "PyPy" instead, it's a lot faster on algorithmic code

import sys, multiprocessing
import copy


# The real algorithm starts here:
def main(d):

	result = 0
	next_group = d['first_group']
	visited = [False for _ in d['groups']]
	visited[next_group] = {'race': -1, 'result': 0}
	for r in xrange(d['races']):
		free_karts = d['karts']
		first_group = next_group
		while free_karts >= d['groups'][next_group]:
			result += d['groups'][next_group]
			free_karts -= d['groups'][next_group]
			next_group = (next_group + 1) % d['n_groups']
			if next_group == first_group:
				break
		if visited[next_group]:
			period = r - visited[next_group]['race']
			# result -= (d['groups'][(next_group - 1) % d['n_groups']])
			#print visited[next_group]
			#print r, period, result
			result = visited[next_group]['result'] + (result - visited[next_group]['result']) * ((d['races']-1-visited[next_group]['race']) // period)
			d_copy = copy.copy(d)
			d_copy['races'] = ((d['races']-visited[next_group]['race']-1) % period)
			d_copy['first_group'] = next_group
			#print d_copy, main(d_copy)
			result += main(d_copy)
			break
		else:
			visited[next_group] = {'race':r, 'result':result}

	return result


def parse_input():
	# The input is parsed into a list of dictionaries, one for each test case
	data = []
	input_dump = open("input.txt", "w")
	n_tests = int(sys.stdin.readline())
	input_dump.write(str(n_tests)+"\n")
	for i in xrange(n_tests):
		line1 = sys.stdin.readline()
		line2 = sys.stdin.readline()
		input_dump.write(line1)
		input_dump.write(line2)
		d = dict()

		d['races'], d['karts'], d['n_groups'] = map(int, line1.split())
		d['groups'] = map(int, line2.split())
		d['first_group'] = 0

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
