#!/usr/bin/python
# I recommend using "PyPy" instead, it's a lot faster on algorithmic code

import sys, multiprocessing
import old_clock, new_clock
from datetime import datetime


# The real algorithm starts here:
def main(d):
	#print old_clock.main(d), new_clock.main(d)
	return old_clock.main(d) - new_clock.main(d)


def parse_input():
	data = []
	input_dump = open("input.txt", "w")
	for line in sys.stdin:
		input_dump.write(line)
		d = dict()
		init_timestamp, end_timestamp = line.split(" - ")
		init_date_string, init_time_string = init_timestamp.split(" ")[:2]
		init_year, init_month, init_day = map(int, init_date_string.split("-"))
		init_hour, init_min, init_sec = map(int, init_time_string.split(":"))
		end_date_string, end_time_string = end_timestamp.split(" ")[:2]
		end_year, end_month, end_day = map(int, end_date_string.split("-"))
		end_hour, end_min, end_sec = map(int, end_time_string.split(":"))
		
		init_date = datetime(init_year, init_month, init_day, init_hour, init_min, init_sec)
		end_date = datetime(end_year, end_month, end_day, end_hour, end_min, end_sec)
		delta = end_date - init_date
		
		d = delta.seconds + (86400*delta.days)
		#print d

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
