"""  -*- mode: python; coding: utf-8; -*-
"""

import sys, time, datetime

def worst(days, hours, mins, secs):
    led=[6, 2, 5, 5, 4, 5, 6, 3, 7, 6]

    all_led=sum(led)
    six_led=sum(led[0:6])
    two_led=6*all_led + 10*six_led
    led_24 =2*all_led + 10*sum(led[0:2])   +  sum(led[0:4]) + led[2]*4

    # count
    n=0
    stay_hour=led[hours%10]+led[(hours/10)%10]
    stay_min= led[mins%10] +led[mins/10]
    stay_sec= led[secs%10] +led[secs/10]

    # days
    for i in xrange(days):      # hour                              # minute                    # second
        n+=                     led_24*3600+                        two_led*60*24+              two_led*60*24

    # hours
    for i in xrange(hours):
        n+=                     (led[i%10]+led[(i/10)%10])*3600+    two_led*60+                 two_led*60

    # minutes
    for i in xrange(mins):
        n+=                     stay_hour*60+                       (led[i%10]+led[i/10])*60+   two_led

    # seconds
    for i in xrange(secs):
        n+=                     stay_hour+                          stay_min+                   led[i%10]+led[i/10]

    return n+stay_hour+stay_min+stay_sec

def bad(days, hours, mins, secs):
    led_a=[0, 4, 1, 1, 2, 1, 1, 4, 0, 1]
    led_6=[0, 4, 1, 1, 2, 2]

    all_a=sum(led_a)
    all_6=sum(led_6)

    two_led=6*all_a + all_6

    led_24=2*all_a + 0+4+2  + 0+4+1+2

    # count
    n=36

    # days
    for i in xrange(days):     # hour                             # minute                    # second
        n+=                    led_24+                            two_led*24+                 two_led*60*24

    # hours
    for i in range(hours):
        if not ((i+1)%10):
            n+=                led_a[(i/10)%10]+led_a[i%10]+      two_led+                    two_led*60
        else:
            n+=                                 led_a[i%10]+      two_led+                    two_led*60

    # minutes
    for i in range(mins):
        if not ((i+1)%10):
            n+=                                               led_6[i/10]+led_a[i%10]+        two_led
        else:
            n+=                                                           led_a[i%10]+        two_led

    # seconds
    for i in range(secs):
        if not ((i+1)%10):
            n+=                                                                               led_6[i/10]+led_a[i%10]
        else:
            n+=                                                                                           led_a[i%10]

    return n

while True:
    line=sys.stdin.readline()
    if not line: break

    (start, end)=line.split(" - ")
    start=start.strip()
    end=end.strip()

    s=time.strptime(start.split()[0], "%Y-%m-%d")
    e=time.strptime(end.split()[0],   "%Y-%m-%d")

    diff=datetime.date(e.tm_year, e.tm_mon, e.tm_mday) - datetime.date(s.tm_year, s.tm_mon, s.tm_mday)

    he=end.split()[1].split(':')

    w=worst(diff.days, int(he[0]), int(he[1]), int(he[2]))
    b=bad(diff.days, int(he[0]), int(he[1]), int(he[2]))
    print w-b
