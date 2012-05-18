import sys;
from operator import itemgetter
from itertools import groupby

# Prints passwords for given combinations
def printPasswords(combinations, rm, s=''):
	# Base case
	if (not combinations or (not combinations[0] and len(combinations) == 1)):
		print s;
	else:
		# Recursive.
		# If first element is [] remove it
		if not combinations[0]:
			combinations = combinations[1:];
		# Sort alphabetically our options
		options = sorted(combinations[0]);
		# For each option..
		for chara in options:
			# These are the other options
			otherOptions = options[:];
			otherOptions.remove(chara);
			# Check if this option is valid (may be there are other restrictions)
			validOption = True;
			for charb in otherOptions:
				if (rm[chara][charb]>0):
					validOption = False;
			# If it valid, make recursive call
			if validOption:
				printPasswords([otherOptions]+combinations[1:],rm,s+chara);

# Aux: prints relation matrix
def printRelationMatrix(rm,charSet):
	s = '   ';
	for char in charSet:
		s+= "  %s" % char;
	s+='\n';
	for i,row in enumerate(rm):
		first = True;
		s+= " %s "%charSet[i];
		for rel in rm[row]:
			s+= '%3d'%rm[row][rel];
		s+='\n';
	print s;
			

def main():
	data = [];
	charSet = set();
	for line in sys.stdin:
		data += [line.strip()];
		for char in line.strip():
			charSet.add(char);
	# We need a list of chars, because we don't know if set() retreives
	# the element in the same order each time
	charSet = list(charSet);
	# This will be the matrix of order
	rm = dict();
	charSetLength = len(charSet);
	for char in charSet:
		rmRow = dict();
		for rowchar in charSet:
			rmRow[rowchar] = 0;
		rm[char] = rmRow;
	
	# Now we read relations
	for relation in data:
		for i,rela in enumerate(relation[:-1]):
			for j,relb in enumerate(relation[i+1]):
				rm[rela][relb] = -1;
				rm[relb][rela] = 1;
				
	#
	# Applying the transitive rule to the matrix, a<b, b<c => a<c
	# I don't really know if it's the most efficent way
	# Probably it is not...
	counter = 0;
	for i,chara in enumerate(charSet):
		for j,charb in enumerate(charSet):
			if (chara != charb):
				# a < b
				if (rm[chara][charb] < 0):
					for k,charc in enumerate(charSet):
						counter += 1;
						# c < a < b
						if (rm[charc][chara] < 0):
							rm[charc][charb] = -1;
							rm[charb][charc] = 1;
						elif(rm[chara][charc] > 0):
							rm[charc][charb] = -1;
							rm[charb][charc] = 1;
						# a < b < c
						elif(rm[charc][charb] > 0):
							rm[chara][charc] = -1;
							rm[charc][chara] = 1;
						elif(rm[charb][charc] < 0):
							rm[chara][charc] = -1;
							rm[charc][chara] = 1;
				# a > b
				elif (rm[chara][charb] > 0):
					for charc in charSet:
						counter += 1;
						# c > a > b
						if (rm[charc][chara] > 0):
							rm[charc][charb] = 1;
							rm[charb][charc] = -1;
						elif (rm[chara][charc] < 0):
							rm[charc][charb] = 1;
							rm[charb][charc] = -1;
						# a > b > c
						elif (rm[charc][charb] < 0):
							rm[chara][charc] = 1;
							rm[charc][chara] = -1;
						elif (rm[charb][charc] > 0):
							rm[chara][charc] = 1;
							rm[charc][chara] = -1;
	
	# Now we look for elements that do not have relations				
	minDistances = dict();
	for chara in charSet:
		m = 1000000000;
		for charb in charSet:
			if (chara != charb and abs(rm[chara][charb])<m):
				m = abs(rm[chara][charb])
		minDistances[chara] = m;
	
	# Each element with it's weight...	
	relationOrder = [];
	for i,char in enumerate(charSet):
		relationOrder  += [[sum(list(rm[char].values())),char]];
	# ...sorted by weight
	relationOrder = sorted(relationOrder, key=itemgetter(0));
	
	# This is needed to equalize weights 
	# (because first elements have more negative elements in their 
	# relation matrix column)
	for i in range(len(relationOrder)):
		relationOrder[i][0]-=i;
		
	# Group elements finding where we can have various options
	combinations = [[char for weight,char in group]
		   			for k,group in  groupby(relationOrder,key=lambda q: True if minDistances[q[1]] == 0 else q[1] )]

	# Print the passwords
	printPasswords(combinations,rm);
			
if __name__ == '__main__':
	main();
