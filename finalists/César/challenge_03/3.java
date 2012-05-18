import sys, re

def efficient_solution():
    t, min_sample, current_min_t, min_t, max_t, max_gain = 0, float("Inf"), -1, 0, 0, 0
    for line in sys.stdin:
        sample = int(line.strip())
        if sample < min_sample:
            min_sample = sample
            current_min_t = t
        elif sample - min_sample > max_gain:
            min_t = current_min_t
            max_t = t
            max_gain = sample - min_sample
        t += 100
    return min_t, max_t, max_gain

if __name__ == "__main__":
    print "%d %d %d" % efficient_solution()
