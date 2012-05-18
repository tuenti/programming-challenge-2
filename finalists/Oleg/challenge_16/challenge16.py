import sys;

# Quadratic difference between two reports
def getQuadraticDiff(r1,r2):
	return sum([pow((r1[i]-r2[i]), 2) for i in range(len(r1))]);

def main():
	# Input data
	knownReports = int(sys.stdin.next().strip());
	unknownReports = int(sys.stdin.next().strip());
	systemCallsNumber = int(sys.stdin.next().strip());
	reportNumber = 0;
	S = [];
	M = [];
	U = [];
	while reportNumber < knownReports:
		report = sys.stdin.next().strip().split(' ');
		if (report[0] == 'S'):
			S.append([int(v) for v in report[1:]]);
		elif (report[0] == 'M'):
			M.append([int(v) for v in report[1:]]);
		else:
			raise BaseException('Unknown software type where known expected');
		reportNumber+=1;
	reportNumber = 0;
	while reportNumber < unknownReports:
		report = sys.stdin.next().strip().split(' ');
		U.append([int(v) for v in report]);
		reportNumber+=1;
	
	# Mean report for all safe software
	mean = [sum([r[i] for r in S])/float(len(S)) for i in range(systemCallsNumber)]

	# All differences between each report and software mean
	sdiffs = [getQuadraticDiff(mean,S[i]) for i in range(len(S))]
	mdiffs = [getQuadraticDiff(mean,M[i]) for i in range(len(M))]
	# Limit between maximum of safe differences and minimum of malware differences
	# We also could use maximum of sdiffs to be optimistic or minimum of
	# mdiffs to be pesimistic, it's just for your taste
	limit = (max(sdiffs)+min(mdiffs))/2;
	# System calls sum
	s = 0;
	for r in U:
		diff = getQuadraticDiff(mean,r);
		if (diff > limit):
			# If it's over the limit, sum system calls
			s += sum(r);
	print s;
	
if __name__ == '__main__':
	main();
