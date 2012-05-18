import sys;
from time import time;

# Calculates where each card goes
def cardPermutation(nCards, firstSetSize, card, firstLess):
	if (firstLess):
		if (card < firstSetSize):
			return (firstSetSize-1-card)*2;
		elif (card >= nCards-firstSetSize):
			return (nCards-1-card)*2+1;
		else:
			return 2*firstSetSize+(nCards-firstSetSize-1-card);
	else:
		if (card >= firstSetSize):
			return (nCards-card-1)*2+1;
		elif (card >= nCards-(nCards-firstSetSize)*2):
			return (firstSetSize-1-card)*2;
		else:
			return 2*firstSetSize+(nCards-firstSetSize*2-card)-1;
		
		

# GCD algorithm
def gcd(a, b):
    while b:      
        a, b = b, a % b
    return a
# LCM of two numbers
def lcm(a, b):
    return a * b // gcd(a, b)

# LCM of arbitrary number of numbers
def lcmm(*args):
    return reduce(lcm, args)

def main():		
	testCasesNumber = int(sys.stdin.next().strip());
	testCase = 1;
	while testCase <= testCasesNumber:
		n,j = [int(v) for v in sys.stdin.next().strip().split(' ')];
		# Magic!!!
		# We have:
		#  [ j ]   [ n-j ]  decks
		# Or the same:
		# [ j ]   [ j  - j  - unimportant part modulo 2  - j ]
		# So we reduce the problem into a smaller one
		# And the same with n-j
		firstLess = j < n/2.0;
		if (firstLess):
			if (n-j*4 > 0):
				n = j*4+(n%2);
		else:
			if (n-(n-j)*4 > 0):
				newn = (n-j)*4+(n%2);
				j = j-(n-newn);
				n = newn;			
		# Our cards
		cards = range(n);
		# Permutations
		# (Where does each card goes, it's always the same)
#		permutations = shuffledPermutations(cards,j);
#		print permutations;
#		print n,j,firstLess;
#		for p in permutations:
#			print p,permutations[p],cardPermutation(n,j,p,firstLess),cardPermutation(n,j,permutations[p],firstLess);
#			if (p != cardPermutation(n,j,permutations[p],firstLess)):
#				exit();
		# Cards to analyze for cycles
		cards = set(range(n));
		# Cycles we have found, it's a set because we don't want
		# to calculate later lcm(2,2,2,...)
		lengths = set();
		# Continue until all elements are explored
		while (0 < len(cards)):
			# Already explored permutations
			used = [];
			# A new empty cycle
			cycleLength = 0;
			# Initialize the cycle with the first pertmutation
			# Here we get a random position from that we have not explored
			firstpos = cards.pop();
			lastpos = cardPermutation(n,j,firstpos, firstLess);
			cycleLength+=1;
			# Append the used position
			used.append(lastpos);
			while (firstpos!=lastpos):
				# Same again and again till it's a cycle
				lastpos = cardPermutation(n,j,lastpos,firstLess);
				cycleLength+=1;
				used.append(lastpos);
			# Remove used cards
			cards = cards.difference(used);
			# We only care about this cycle's length
			lengths.add(cycleLength);
			
		# The solution is the lower common multiple of cycle lengths
		# that make the permutation
		solution = lcmm(*lengths);
		
		print "Case #%d: %d" % (testCase, solution);
		testCase+=1;
	
	
	
	
if __name__ == '__main__':
	main();
