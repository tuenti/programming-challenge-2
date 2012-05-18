import sys, re

def solution(R, k, group_sizes):
    assert max(group_sizes) <= k
    race_sizes, g, group_positions = [], 0, {}
    while len(race_sizes) < R and not g in group_positions:
        group_positions[g] = len(race_sizes)
        race_size, taken_group_count = 0, 0
        while race_size + group_sizes[g] <= k and taken_group_count != len(group_sizes):
            race_size += group_sizes[g]
            g = (g + 1) % len(group_sizes)
            taken_group_count += 1
        race_sizes.append(race_size)
    #print race_sizes
    if len(race_sizes) == R:
        return sum(race_sizes)
    else:
        cycle_start = group_positions[g]
        #print cycle_start
        cycle_length = len(race_sizes) - cycle_start
        cycle_count = (R - cycle_start) / cycle_length
        cycle_remainder = (R - cycle_start) % cycle_length
        return sum(race_sizes[0:cycle_start]) + \
               sum(race_sizes[cycle_start:]) * cycle_count + \
               sum(race_sizes[cycle_start:cycle_start + cycle_remainder])

if __name__ == "__main__":
    cases = int(sys.stdin.readline())
    for c in range(cases):
        R, k, G = map(int, sys.stdin.readline().split())
        group_sizes = map(int, sys.stdin.readline().split())
        print solution(R, k, group_sizes)
