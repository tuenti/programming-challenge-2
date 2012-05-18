import sys;
import fileinput;

def main():
#	Translation of Bee to Ook.
#	Compiled and executed result says:
#
#	Input is the number of straight cuts made through a round chocolate 
#	cake and output is the maximum number of cake pieces that can be produced.
#
#	s = '';
#	for line in fileinput.input('program.bee'):
#		s+= line;
#	s =  s.replace('Bee','Ook')
#	f  = open('test.ook', 'w');
#	f.write(s);
#	f.close();
	testCasesNumber = int(sys.stdin.next().strip());
	testCase = 1;
	while testCase <= testCasesNumber:
		n = int(sys.stdin.next().strip());
#       http://en.wikipedia.org/wiki/Lazy_caterer%27s_sequence
		print "Case #%d: %d" % (testCase,((n*n+n+2)/2))
		testCase +=1;
		
		
if __name__ == '__main__':
	main();
