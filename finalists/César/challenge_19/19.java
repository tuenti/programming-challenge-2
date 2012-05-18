import sys, base64

class BitStream:
    def __init__(self):
        self.bits = []

    def add(self, n, b=32):
        mask = 1 << (b - 1)
        while mask != 0:
            self.bits.append((n & mask) != 0)
            mask >>= 1

    def as_hex_string(self):
        padded_bits = self.bits + [0] * (7 - (len(self.bits) - 1) % 8)
        return "".join([self._convert_nibble(*padded_bits[i:i+4]) for i in range(0, len(padded_bits), 4)])

    def _convert_nibble(self, b3, b2, b1, b0):
        return "0123456789abcdef"[b3*8 + b2*4 + b1*2 + b0]

if __name__ == "__main__":
    # Extract the 32-bit elements from the input...
    text = sys.stdin.readline().strip()
    decoded_text = base64.b64decode(text)
    elements = [int(decoded_text[i:i+8], 16) for i in range(0, len(decoded_text), 8)]
    # ... encode into the bit stream...
    last = None
    bits = BitStream()
    for e in elements:
        if last != None and last - 16 <= e <= last + 15:
            bits.add(0, 1)
            bits.add(e - last, 5)
        else:
            bits.add(1, 1)
            bits.add(e)
        last = e
    # ... and print in base64.
    print base64.b64encode(bits.as_hex_string()).rstrip('=')
