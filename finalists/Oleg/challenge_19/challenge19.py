import sys;
import fileinput;
from base64 import b64decode,b64encode;
import binascii


def bin2hex(b):
	s = '';
	for i in xrange(len(b)/4):
		s+= hex(int(b[i*4:(i+1)*4],2))[2:];
	return s;

def hex2bin(h):
	s = '';
	for i in xrange(len(h)):
		s+= bin(int(h[i],16))[2:].zfill(4);
	return s;


def main():
	# Read input
	inputs = '';
	for line in sys.stdin:
		inputs+=line.strip();
	
	# Convert to binary
	ihex = b64decode(inputs);
	ibin = hex2bin(ihex);
	
	# You can change the diffsize for the optimal compression
	# (7 is optimal for test_input)
	diffSize = 6;
	bin10000 = pow(2,diffSize-2);		
	lastWord = ibin[:32];
	lastWordValue = int(lastWord,2);
	compressed = '1'+lastWord;
	for pos in xrange(1,len(ibin)/32):
		word = ibin[32*pos:32*(pos+1)];
		wordValue = int(word,2);
		intDiff = lastWordValue-wordValue;
		if (abs(intDiff) > bin10000 or -bin10000 == intDiff):
			compressed += '1'+word;
			lastWord = word;
			lastWordValue = wordValue;
		else:
			if (intDiff<=0):
				diff = bin(abs(intDiff))[2:];
				# 0 stands for "continue"
				# 0 stands for negative difference
				diffString = '00'+diff.zfill(diffSize-2);
				compressed+=diffString;
				lastWord = word;
				lastWordValue = wordValue;
			else:
				diff = bin(bin10000-intDiff)[2:];
				# 0 stands for "continue";
				# 1 stands for positive difference
				diffString = '01'+diff.zfill(diffSize-2);
				compressed+=diffString;		
				lastWord = word;
				lastWordValue = wordValue;
	# Fill with 0 to reach parity.
	final = compressed+'0'*(len(compressed)%4);	
	
	# Convert the result
	finalhex = bin2hex(final);
	finalb64 = b64encode(finalhex);
	print finalb64.replace('=','');
			
			
			
if __name__ == '__main__':
	main();
