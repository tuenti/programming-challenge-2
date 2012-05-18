import sys;
import fileinput;
from operator import itemgetter;

# Character scores constants
charScore = dict();
for char in ["A", "E", "I", "L", "N", "O", "R", "S", "T", "U"]:
	charScore[char] = 1;
for char in ["D", "G"]:
	charScore[char] = 2;
for char in ["B", "C", "M", "P"]:
	charScore[char] = 3;
for char in ["F", "H", "V", "W", "Y"]:
	charScore[char] = 4;
for char in ["K"]:
	charScore[char] = 5;
for char in ["J", "X"]:
	charScore[char] = 8;
for char in ["Q", "Z"]:
	charScore[char] = 10;

# Make a set of chars, where char repetitions are numbered
# PAPA => P1,A1,P2,A2
def makeCharSet(word):
	charSet = set()
	charDict = dict();
	for char in word:
		try:
			charDict[char]+=1;
		except:
			charDict[char]=1;
	for char in charDict:
		for i in xrange(charDict[char]):
			charSet.add(char+str(i));
	return charSet;

def main():
	# Words structure, it's a dictionary of scores
	words = {};
	# Process each word
	for line in fileinput.input('descrambler_wordlist.txt'):
		word = line.strip();
		# Calculate word score
		wordScore = 0;
		for char in word:
			wordScore += charScore[char];
		# Save this word, and it's length
		try:
			words[wordScore].append([word,len(word)]);
		except:
			words[wordScore] = [[word,len(word)]]
	# Sort each score's words alphabetically
	for word in words:
		words[word] = sorted(words[word],key=itemgetter(0));
	
	# Scores we have
	scores = sorted(words.keys(), reverse=True);
	
	# Test cases
	testCasesNumber = int(sys.stdin.next().strip());
	testCaseNumber = 0;
	while testCaseNumber < testCasesNumber:
		rack,board = sys.stdin.next().strip().split(' ');
		# Options are the best results we found for each char of the word on the board
		options = []
		for char in board:
			# Charset of what we have on the board
			charSet = makeCharSet(rack+char);
			# Length of it
			charSetLen = len(charSet);
			# Score index
			s = 0;
			# If we found one, it's the best (in our order)
			found = False;
			while (not found and s<len(scores)):
				score = scores[s];
				i = 0;
				while (not found and i<len(words[score])):
					# Only try if we have sufficent chars for this word
					if (charSetLen >= words[score][i][1]):
						# Calculate this word's charset on the fly.
						try:
							# If we rest from words chars our chars,
							# and we don't have more chars, we can make this word
							if (not words[score][i][2].difference(charSet)):
								options+=[(words[score][i][0], 100-score)];
								found = True;
						except:
							words[score][i].append(makeCharSet(words[score][i][0]));
							if (not words[score][i][2].difference(charSet)):
								options+=[(words[score][i][0], 100-score)];
								found = True;
					# Next word in this scores
					i+=1;
				# Next score
				s+=1;
		# Sort the best options and print the first.
		options = sorted(options, key=itemgetter(1,0));
		print "%s %d"%(options[0][0],100-options[0][1]);
		
		# Next test case
		testCaseNumber+=1;

if __name__ == "__main__":
	main();
