import sys;
import math;

def main():
	testCasesNumber = int(sys.stdin.next().strip());
	testCase = 0;
	while (testCase < testCasesNumber):
		W,H,ct = [int(s.strip()) for s in sys.stdin.next().strip().split(' ')]
		text = sys.stdin.next().strip();
		eachStich = 1.0/float(ct);
		# Width and height in stitches
		Hs = ct*H;
		Ws = ct*W;
		# Words descriptive variables
		# These are inmutables for the font size, so we calculate them here
		words = text.split(' ');
		wordsCount = len(words);
		wordLengths = [len(w) for w in words];
		wordsTotalLength = sum(wordLengths);
		maxWordLength = max(wordLengths);
		minWordLength = min(wordLengths);
		maxFontSize = min(Hs,Ws,Ws/maxWordLength);
		
		threadUsed = 0;
		fontSize = maxFontSize;
		while (fontSize > 0 and threadUsed == 0):
#			print
#			print "testing fontSize=",fontSize;
#			print "W=%d H=%d ct=%d Hs=%d Ws=%d"%(W,H,ct,Hs,Ws),text;

			lines = Hs/fontSize;
			# Tests to discard this solution:
			weHaveToTry = True;
			
			# Supposed all the words are of minimum length
			# Can they fit on the lines we have?
			# We don't mind about the spaces because they are very 
			# difficult to count
			maxWordsPerLine = Ws/(minWordLength);
			if (maxWordsPerLine*lines < wordsCount):
				weHaveToTry = False;
			# And the maximum length word fits a line with this fontSize?
			if (maxWordLength*fontSize > Ws):
				weHaveToTry = False;
			
			if weHaveToTry:
				line = 1;
				hPosition = 0;
				valid = True;
				for i,w in enumerate(words):
					if (not valid):
						# Break is very bad, but we mind much about speed
						break;
					# Length of this word
					wLength = len(w);
					# Length of this word and a space if there is one
					wLengthWithSpace = wLength if i == 0 else wLength+1;
					# We try to fit this word on this line
					if (wLengthWithSpace*fontSize+hPosition < Ws):
						# It fits, so we move our positon
						hPosition += wLengthWithSpace*fontSize;
					else:
						# It doesn't fit, so we go to the next line and hPosition= 0
						line += 1;
						hPosition = 0;
						if (line > lines):
							# No more lines. stop.
							valid = False;
						else:
							# This word fits this line
							hPosition = wLength*fontSize;
				if (valid):
					threadUsed = int(math.ceil((fontSize*fontSize/2.0)*wordsTotalLength*eachStich));
					# Break, very bad break... :(
					break;
					
			# Let's try with a smaller fontSize
			fontSize -= 1;
			
		print "Case #%d: %d" % (testCase+1,threadUsed);
		testCase += 1;


		
if __name__ == '__main__':
	main();
