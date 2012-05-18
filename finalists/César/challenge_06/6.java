import sys, math, re

def fits_in_piece(wct, hct, word_lengths, font_size):
    current_line, pos_in_line, i = 1, 0, 0
    while i < len(word_lengths):
        word_size = word_lengths[i] * font_size
        if pos_in_line == 0:
            # Check that the new line fits in the billboard.
            if word_size > wct or current_line * font_size > hct:
                return False
            else:
                pos_in_line += word_size
                i += 1
        else:
            # We are in the middle of the line: either insert the word or move to the next line.
            if pos_in_line + font_size + word_size > wct:
                current_line += 1
                pos_in_line = 0
            else:
                pos_in_line += font_size + word_size
                i += 1
    return True

def get_largest_font_size(wct, hct, text):
    word_lengths = map(len, re.split(r"\s+", text))
    if not fits_in_piece(wct, hct, word_lengths, 1):
        return 0
    else:
        # This is the largest size known to be valid.
        small_size = 1
        # One plus this is the smallest size known to be invalid.
        large_size = min(wct, hct)
        while small_size != large_size:
            # Add one in order to round up - critical in the case that medium_size + 1 == large_size.
            medium_size = (small_size + large_size + 1) / 2
            if fits_in_piece(wct, hct, word_lengths, medium_size):
                small_size = medium_size
            else:
                large_size = medium_size - 1
        return small_size

def calculate_thread_length(ct, text, font_size):
    char_count = sum(c != ' ' for c in text)
    return math.ceil(float(char_count * (font_size ** 2)) / (2 * ct))

if __name__ == "__main__":
    cases = int(sys.stdin.readline())
    for c in range(cases):
        W, H, ct = map(int, sys.stdin.readline().split())
        text = sys.stdin.readline().strip()
        font_size = get_largest_font_size(W * ct, H * ct, text)
        thread_length = calculate_thread_length(ct, text, font_size)
        print "Case #%d: %d" % (c + 1, thread_length)
