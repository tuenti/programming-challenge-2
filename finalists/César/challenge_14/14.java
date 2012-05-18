import sys, itertools

def decode_block(block):
    p1, p2, d1, p3, d2, d3, d4 = bits = map(lambda c: ord(c) - ord("0"), block)
    p1 ^= d1 ^ d2 ^ d4
    p2 ^= d1 ^ d3 ^ d4
    p3 ^= d2 ^ d3 ^ d4
    if not (p1 == 0 and p2 == 0 and p3 == 0):
        bits[p1 + 2*p2 + 4*p3 - 1] ^= 1
        _, _, d1, _, d2, d3, d4 = bits
    return [d1, d2, d3, d4]


def decode(message):
    if len(message) % 14 != 0:
        return "Error!"
    else:
        nibbles  = [decode_block(message[i:i+7]) for i in range(0, len(message), 7)]
        bits = [b for n in nibbles for b in n]
        bytes = [int("".join(map(str, bits[i:i+8])), 2) for i in range(0, len(bits), 8)]
        if all(map(lambda b: 32 <= b < 128, bytes)):
            return "".join(map(chr, bytes))
        else:
            return "Error!"

if __name__ == "__main__":
    for line in sys.stdin:
        print decode(line.strip())
