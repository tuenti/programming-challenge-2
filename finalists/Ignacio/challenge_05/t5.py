#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import re
import datetime

# Segments in numbers:
#
#   --        0
#  |  |     1   2
#   --        3
#  |  |     4   5
#   --        6
#
# Each segment is represented by an active bit

segments = [ 0b1110111, # 0
             0b0010010, # 1
             0b1011101, # 2
             0b1011011, # 3
             0b0111010, # 4
             0b1101011, # 5
             0b1101111, # 6
             0b1010010, # 7
             0b1111111, # 8
             0b1111011  # 9
            ]

# How many segments are lit in each digit
segment_count = [ 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 ];


total_seconds_in_a_day = 24 * 60 * 60

def precalculate_delta_segments():
    """ Precompute a 2-dimensional array with the new leds lit from any digit to any digit """
    delta_segments = [[0 for i in range(10)] for j in range(10)]
    
    for i in range(10):
        seg_i = segments[i]
        for j in range(10):
            seg_j = segments[j]
       
            dif = (seg_i ^ seg_j) & seg_j

            # Count the 1 bits       
            new_segments = 0
            while dif > 0:
                if (dif & 1) == 1:
                    new_segments += 1
                dif >>= 1

            delta_segments[i][j] = new_segments

    return delta_segments


def number_of_leds_on(h):
    """ Return the numbers of leds on in the old clock

    h - string representing the hour in format "HHMMSS"
    """
    leds_on = 0
    for digit in h:
        leds_on += segment_count[int(digit)]

    return leds_on


def precalculate_differences_in_a_day():
    """ Precompute differences between a second and the next one in a day 

    Return:
    - An array of 86400, each element represent the difference in leds 
      lit between the old clock and the new one in one second to the next one.
      The position 0 correspond to the hour 00:00:00, the 86399 to the 23:59:59

    - The number of differences between the old clock and the new one in a full
      day starting from 00:00:00
    """

    difference_between_seconds = []
    difference_in_a_day = 0

    time_current = datetime.datetime.strptime("000000", "%H%M%S")
    text_time = "000000"
    
    delta_1seg = datetime.timedelta(seconds=1)

    for i in range(total_seconds_in_a_day):
        time_next = time_current + delta_1seg

        text_time_next = time_next.strftime("%H%M%S")
        leds_on_old = number_of_leds_on(text_time_next)

        # For the new clock we have to compare the last time with the new one    
        leds_on_new = 0
        for x,y in zip(text_time, text_time_next):
            leds_on_new += delta_segments[int(x)][int(y)]

        dif = leds_on_old - leds_on_new
        difference_between_seconds.append(dif)
        difference_in_a_day += dif

        time_current = time_next
        text_time = text_time_next

    return difference_between_seconds, difference_in_a_day


if __name__ == '__main__':

    # Precomputes the tables
    delta_segments = precalculate_delta_segments()
    difference_seconds, difference_in_a_day = precalculate_differences_in_a_day()

    for line in sys.stdin:
        m = re.match(r"(\d+-\d{2}-\d{2} \d{2}:\d{2}:\d{2})\s+-\s+(\d+-\d{2}-\d{2} \d{2}:\d{2}:\d{2})", line)
        if m is None:
            continue

        date_start = datetime.datetime.strptime(m.group(1), "%Y-%m-%d %H:%M:%S")
        date_end = datetime.datetime.strptime(m.group(2), "%Y-%m-%d %H:%M:%S")

        dif = 0

        # Get the second in within a day, so we can use our precomputed table
        second_in_day = (date_start.hour * 60 * 60) + (date_start.minute * 60) + date_start.second

        seconds_left = int((date_end - date_start).total_seconds())

        while seconds_left > 0:
            
            if second_in_day == 0 and seconds_left >= total_seconds_in_a_day:
                # We can skip full days starting at 00:00:00 in one time
                days_until_end = (seconds_left / total_seconds_in_a_day)
                dif += days_until_end * difference_in_a_day
                seconds_left -= days_until_end * total_seconds_in_a_day
            else:               
                dif += difference_seconds[second_in_day]
                second_in_day += 1
                second_in_day %= total_seconds_in_a_day
                seconds_left -= 1

        print dif
                


