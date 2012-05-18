import sys;
from Hamming import Hamming;
def bit(data,i):
	return int(data[i]);

# Just hamming 7,4
def hamming(data):
	b = [int(v) for v in list(data)]
	d1 = (b[0]+b[2]+b[4]+b[6]) & 1;
	d2 = (b[1]+b[2]+b[5]+b[6]) & 1;
	d3 = (b[3]+b[4]+b[5]+b[6]) & 1;
	# Error correction
	if (d1 and d2 and not d3):
		b[2] = 1-b[2];
	elif (d1 and not  d2 and d3):
		b[4] = 1-b[4];
	elif (not d1 and d2 and d3):
		b[5] = 1-b[5];
	elif (d1 and d2 and d3):
		b[6] = 1-b[6];
	s = [str(v) for v in b]
	return s[2]+s[4]+s[5]+s[6]

def main():		
	s = 0;
	for line in sys.stdin:
		d = line.strip();
		bits = '';
		s = '';
		# Incorrect length
		if (len(d) % 7 != 0):
			print "Error!";
		elif (len(d) / 7 * 4 % 8 != 0):
			print "Error!";
		else:
			error = False;
			# Get hamming data
			for i in range(len(d)/7):
				bits += hamming(d[i*7:(i+1)*7]);
			for i in range(len(bits)/8):
				n = int(bits[i*8:(i+1)*8],2);
				# Incorrect char
				if (n>127 or n<32):
					error = True;
				s +=chr(n);
			if error:
				print "Error!";
			else:
				print s;
	
	
if __name__ == '__main__':
	main();
