#/usr/bin/python
# I recommend using "PyPy" instead, it's a lot faster on algorithmic code

import sys, multiprocessing


def c(n1, n2): # 0..9
    if n1 == n2:
        return 0
    elif n2 == 0 and n1 != 9:
        return 2 # 5 to 0, 2 to 0 and 3 to 0 light exactly 2 leds
    else:
        return leds[n1]
    
def clock(n1, n2): # 00..99
    return c(n1//10, n2//10) + c(n1%10, n2%10)

# from # to #+1
#       0  1  2  3  4  5  6  7  8  9
leds = (0, 4, 1, 1, 2, 1, 1, 4, 0, 1)
leds_minute = sum([clock(n, n+1) for n in xrange(59)]) + clock(59, 0)
leds_hour = (60 * leds_minute) + leds_minute
leds_day = sum([clock(n, n+1) for n in xrange(23)]) + clock(23, 0) + (leds_hour * 24)


# The real algorithm starts here:
def main(d):
    
    result = 36 # Count the 00:00:00
    days = d // (60*60*24)
    result += leds_day * days
    d -= days*60*60*24
    hours = d // (60*60)
    result += hours*leds_hour + sum([clock(n, n+1) for n in xrange(hours)])
    d -= hours*60*60
    minutes = d // 60
    result += minutes*leds_minute + sum([clock(n, n+1) for n in xrange(minutes)])
    d -= minutes*60
    result += sum([clock(n, n+1) for n in xrange(d)])

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
