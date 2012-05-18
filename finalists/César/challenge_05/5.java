import sys, re
from datetime import datetime

def cumsum(seq):
    prev = 0
    yield prev
    for e in seq:
        prev += e
        yield prev

# Description of the segments required for the old clock.
segment_count = [6, 2, 5, 5, 4, 5, 6, 3, 7, 6]
cum_segment_count = list(cumsum(segment_count))

# Description of the segments required for the new clock.
segment_diff = {10: [0, 4, 1, 1, 2, 1, 1, 4, 0, 1], 6: [0, 4, 1, 1, 2, 2], 3: [0, 4, 2]}
cum_segment_diff = {f: list(cumsum(sd)) for f, sd in segment_diff.items()}

def solve_old_clock(s):
    cost = 0
    left, digit, right, ticks, prev_f = s, 0, 0, 1, 1
    for f in [10, 6, 10, 6, 10, 3]:
        left, digit, right, ticks, prev_f = left / f, left % f, digit * ticks + right, ticks * prev_f, f
        cost += ticks * (left * cum_segment_count[f] + cum_segment_count[digit]) + segment_count[digit] * (right + 1)
    return cost

def solve_new_clock(s):
    cost = 6 * segment_count[0]
    left, digit = s, 0
    for f in [10, 6, 10, 6, 10, 3]:
        left, digit = left / f, left % f
        cost += left * cum_segment_diff[f][-1] + cum_segment_diff[f][digit]
    return cost

if __name__ == "__main__":
    day_seconds = 24 * 60 * 60
    # Calculate the base cost of a day considering that the new clock wraps around.
    day_cost = solve_old_clock(day_seconds - 1) - (solve_new_clock(day_seconds - 1) - 6 * segment_count[0] + 10)
    for line in sys.stdin:
        stimes = map(lambda s: s.strip(), line.split(" - "))
        from_time, to_time = map(lambda t: datetime.strptime(t, "%Y-%m-%d %H:%M:%S"), stimes)
        elapsed = to_time - from_time
        print day_cost * elapsed.days + solve_old_clock(elapsed.seconds) - solve_new_clock(elapsed.seconds)
