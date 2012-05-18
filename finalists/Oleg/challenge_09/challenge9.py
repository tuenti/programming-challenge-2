import sys;
import fileinput;

def main():
	# Number of words to search
	searchWordsNumber = int(sys.stdin.next().strip());
	# Word processing index
	searchWord = 0;
	# Dictionary of words that contains lists with needed numbers
	searchWords = dict();
	# List to know what words we are still searching
	searchWordsList = [];
	# Number of found occurrences of each word
	wordNumbers = dict();
	# List to print the solutions
	searchWordsOrder = [];
	while searchWord < searchWordsNumber:
		word,number = sys.stdin.next().strip().split(' ');
		number = int(number.strip());
		word = word.strip();
		
		wordNumbers[word] = 0;
		
		try:
			searchWords[word] += [number];
		except:
			searchWords[word] = [number];
			
		if word not in searchWordsList:
			searchWordsList += [word];
			
		searchWordsOrder += [(word,number)];
		
		searchWord+=1;
	
	# Positions of the found words
	foundWords = dict();
	
	filenum = 1;
	# Stop if we found all the words
	while (filenum <= 800 and searchWordsList):
		# For each file, for each line, for each word, look if we are searching it
		for linenum,line in enumerate(fileinput.input('documents/0'+str('%03d'%filenum))):
			wordList = line.lower().split(' ');
			for wordnum,w in enumerate(wordList):
				word = w.strip();
				if word in searchWordsList:
					# counter++1 and check if we are searching this position
					wordNumbers[word]+=1;
					if wordNumbers[word] in searchWords[word]:
						foundWords[(word,wordNumbers[word])] = (filenum,linenum+1,wordnum+1);
						# Remove this search number from this word
						searchWords[word].remove(wordNumbers[word]);
						# Remove from the list if no more search numbers
						if not searchWords[word]:
							searchWordsList.remove(word);
		filenum += 1;
		
	# Print the result
	for word in searchWordsOrder:
		print "%d-%d-%d" % foundWords[word];
		
if __name__ == '__main__':
	main();
