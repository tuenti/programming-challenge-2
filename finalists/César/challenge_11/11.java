import sys, itertools

letter_scores = {
    'A':1, 'E':1, 'I':1, 'L':1, 'N':1, 'O':1, 'R':1, 'S':1, 'T':1, 'U':1,
    'D':2, 'G':2,
    'B':3, 'C':3, 'M':3, 'P':3,
    'F':4, 'H':4, 'V':4, 'W':4, 'Y':4,
    'K':5,
    'J':8, 'X':8,
    'Q':10, 'Z':10
}

class WordIndex:
    def __init__(self, wordfile):
        self._build_index(wordfile)
        pass

    def get_word_for_letters(self, letters):
        sorted_letters = "".join(sorted(letters))
        if sorted_letters in self.word_index:
            return (self.word_index[sorted_letters], self.get_word_score(letters))
        else:
            return (None, 0)

    def get_word_score(self, word):
        return sum(map(letter_scores.get, word.upper()))

    def _build_index(self, wordfile):
        self.word_index = {}
        f = open(wordfile, "r")
        for line in f:
            word = line.strip().upper()
            sorted_word = "".join(sorted(word))
            if sorted_word in self.word_index:
                if self.word_index[sorted_word] > word:
                    self.word_index[sorted_word] = word
            else:
                self.word_index[sorted_word] = word
        f.close()

if __name__ == "__main__":
    index = WordIndex("descrambler_wordlist.txt")
    cases = int(sys.stdin.readline())
    for c in range(cases):
        rack, hword = sys.stdin.readline().split()
        candidates = ("".join(ls) + l for n in range(1, len(rack) + 1) for ls in itertools.combinations(rack, n) for l in hword)
        vword, score = min((index.get_word_for_letters(c) for c in candidates), key=lambda r: (-r[1], r[0]))
        print "%s %d" % (vword, score)
