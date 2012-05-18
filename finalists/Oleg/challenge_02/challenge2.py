import sys
import math

# Brute force method
def calculateMaxBruteForce(n):	
	maximum = (0,0,0);
	for i in range (n):
		value = bin(i)[2:].count('1') + bin(n-i)[2:].count('1');
		if (value > maximum[0]):
			maximum = (value,i,n-i);
	return maximum

# Intelligent method:
# The maximum will be setting one of numbers as 1111..1
def calculateMaxIntelligent(n):
	logOnes = int(math.floor(math.log(n,2)));
	i = int(pow(2,logOnes)-1);
	ones = logOnes + bin(n-i)[2:].count('1');
	return (ones, i,n-i);
		
def main():
	testCasesNumber = int(sys.stdin.next());
	testCaseNumber = 0;
	while testCaseNumber < testCasesNumber:
		testCase = int(sys.stdin.next().strip());
		result = calculateMaxIntelligent(testCase);
		print "Case #%d: %d" % (testCaseNumber+1, result[0]);		
		testCaseNumber += 1;

if __name__ == '__main__':
	main();
