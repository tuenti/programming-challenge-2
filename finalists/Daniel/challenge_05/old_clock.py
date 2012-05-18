#/usr/bin/python
# I recommend using "PyPy" instead, it's a lot faster on algorithmic code

import sys, multiprocessing


def clock(n): # 00..59
    return leds[n//10] + leds[n%10]

#       0  1  2  3  4  5  6  7  8  9
leds = (6, 2, 5, 5, 4, 5, 6, 3, 7, 6)
leds_minute = sum([clock(n) for n in xrange(60)])
leds_hour = 60 * 2 * leds_minute
leds_day = 24 * leds_hour + 60*60*sum([clock(n) for n in xrange(24)])

# The real algorithm starts here:
def main(d):
    
    d += 1 # Count the 00:00:00
    result = 0
    days = d // (60*60*24)
    result += leds_day * days
    d -= days*60*60*24
    hours = d // (60*60)
    result += hours*leds_hour + sum([clock(n) for n in xrange(hours)])*60*60
    d -= hours*60*60
    result += clock(hours) * d
    minutes = d // 60
    result += minutes*leds_minute + sum([clock(n) for n in xrange(minutes)])*60
    d -= minutes*60
    result += clock(minutes) * d
    result += sum([clock(n) for n in xrange(d)])

    return result


def parse_input():
    # The input is parsed into a list of dictionaries, one for each test case
    data = []
    for line in sys.stdin:
        data.append(int(line))
    return data


if __name__ == '__main__':
    data = parse_input()
    # Taking advantage of multi-core systems
    pool = multiprocessing.Pool(processes=multiprocessing.cpu_count())
    for n, result in enumerate(pool.map(main, data)):
    #for n, d in enumerate(data):
    #    result = main(d)
        print(str(result))
