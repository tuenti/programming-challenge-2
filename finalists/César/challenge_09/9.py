import sys, os, re
# Using mxBeeBase from http://www.egenix.com/products/python/mxBase/mxBeeBase/
from mx.BeeBase import BeeDict

document_path = "documents"
word_file_path = "words"
word_file_name = "words_"
index_path = "indices"
index_base_name = "index"

class Index:
    def __init__(self):
        if not os.path.exists(word_file_path):
            os.mkdir(word_file_path)
            self._build_word_files()
        self._translate_word_files()

    def find_word(self, word, app):
        word = word.lower()
        index = BeeDict.BeeDict(os.path.join(index_path, index_base_name + word[0]))
        info = index[word][app - 1]
        index.close()
        return info

    def _build_word_files(self):
        print "Compiling word files..."
        regex = re.compile("[a-z0-9]+", flags=re.IGNORECASE)
        word_files = {}
        for filename in os.listdir(document_path):
            print filename
            file_index = int(filename)
            f, line_number = open(os.path.join(document_path, filename), "r"), 1
            for line in f:
                word_pos = 1
                for m in re.finditer(regex, line):
                    word = m.group(0).lower()
                    if word[0] in word_files:
                        word_file = word_files[word[0]]
                    else:
                        word_file = open(os.path.join(word_file_path, word_file_name + word[0]), "w")
                        word_files[word[0]] = word_file
                    word_file.write("%s %d-%d-%d\n" % (word, file_index, line_number, word_pos))
                    word_pos += 1
                line_number += 1
            f.close()
            exit()

        for f in word_files.values():
            f.close()

    def _translate_word_files(self):
        for filename in os.listdir(word_file_path):
            index_name = os.path.join(index_path, index_base_name + filename[-1])
            if not os.path.exists(index_name + ".dat"):
                print "Building index for %s..." % (filename,)
                exit()
                index = BeeDict.BeeDict(index_name, autocommit=True)
                f = open(os.path.join(word_file_path, filename), "r")
                for line in f:
                    line = line.strip()
                    word, word_info = line.split(" ")
                    info = index[word] if index.has_key(word) else []
                    info.append(word_info)
                    index[word] = info
                f.close()
                index.commit()
                index.close()

if __name__ == "__main__":
    index = Index()
    cases = int(sys.stdin.readline())
    for c in range(cases):
        word, app = sys.stdin.readline().split()
        print index.find_word(word, int(app))
