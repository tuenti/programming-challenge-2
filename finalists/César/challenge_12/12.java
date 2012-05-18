import sys

def get_image_key():
    from PIL import Image
    im = Image.open("CANTTF.png")
    pix = im.load()
    bits = []
    for col in range(86):
        r, g, b = pix[col, 0]
        bits.append(r & 1)
        bits.append(g & 1)
        bits.append(b & 1)
    bin_bytes = ["".join(map(lambda b: chr(b + ord("0")), bits[i:i+8])) for i in range(0, 256, 8)]
    return "".join(map(lambda b: chr(int(b, 2)), bin_bytes))

def from_hex(c):
    return ord(c.lower()) - ord('a') + 10 if 'a' <= c.lower() <= 'f' else ord(c) - ord('0')

def to_hex(d):
    return chr(ord('0') + d) if d < 10 else chr(ord('a') + d - 10)

def sum_keys(keys):
    hex_keys = [map(from_hex, k) for k in keys]
    key_sum = map(lambda d: d % 16, map(sum, zip(*hex_keys)))
    return "".join(map(to_hex, key_sum))

if __name__ == "__main__":
    k1 = "62cd275989e78ee56a81f0265a87562e" # get_image_key()
    k2 = "ed8ce15da9b7b5e2ee70634cc235e363" # QR-code
    k3 = "a541714a17804ac281e6ddda5b707952" # Comments
    n = sys.stdin.readline().strip()
    print sum_keys([n, k1, k2, k3])
