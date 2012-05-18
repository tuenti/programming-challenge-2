import sys, re

def largest_power_of_2(n):
    m = 0
    while (2*m + 1 <= n):
        m = 2*m + 1
    return m

def count_bits(n):
    count = 0
    while (n != 0):
        count += 1
        n &= n - 1
    return count

def brute_force_solution(n):
    return max(count_bits(m) + count_bits(n - m) for m in range(n/2 + 1))

def efficient_solution(n):
    m = largest_power_of_2(n)
    return count_bits(m) + count_bits(n - m)

def test():
    for n in range(10000):
        assert brute_force_solution(n) == efficient_solution(n)

if __name__ == "__main__":
    cases = int(sys.stdin.readline())
    for c in range(cases):
        n = int(sys.stdin.readline())
        print "Case #%d: %d" % (c + 1, efficient_solution(n))
