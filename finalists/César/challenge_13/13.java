import sys, itertools

def build_permutation(N, L):
    p = range(N)
    l = min(L, N - L)
    return [e for t in zip(reversed(p[L-l:L]), reversed(p[-l:])) for e in t] + \
           list(reversed(p[L:-l])) + list(reversed(p[0:L-l]))

def get_cycle_lengths(p):
    indices = set(xrange(len(p)))
    lengths = []
    while len(indices) > 0:
        i, cycle_length = p[indices.pop()], 1
        while i in indices:
            indices.remove(i)
            i, cycle_length = p[i], cycle_length + 1
        lengths.append(cycle_length)
    return lengths

def gcd(a, b):
    if a < b:
        a, b = b, a
    while b != 0:
        a, b = b, a % b
    return a

def lcm(a, b):
    return a + b if a == 0 or b == 0 else a / gcd(a, b) * b

def calculate_cycle_length(N, L):
    p = build_permutation(N, L)
    cycle_lengths =  get_cycle_lengths(p)
    return reduce(lcm, cycle_lengths)

if __name__ == "__main__":
    cases = int(sys.stdin.readline())
    for c in range(cases):
        N, L = map(int, sys.stdin.readline().split())
        print "Case #%d: %d" % (c + 1, calculate_cycle_length(N, L))
