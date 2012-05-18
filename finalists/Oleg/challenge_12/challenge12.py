import sys;
from PIL import Image;

def result(a,b,c,d):
	x = '';
	for i in range(len(a)):
		x += hex(int(a[i],16)+int(b[i],16)+int(c[i],16)+int(d[i],16)%16)[-1]
	return x;
	
def main():
	inputstring = sys.stdin.next().strip();
	# From the exif
	comment = 'a541714a17804ac281e6ddda5b707952';
	# From the QR code with inverted colours
	qr =      'ed8ce15da9b7b5e2ee70634cc235e363';
	
	# Steganography
	img = Image.open('CANTTF.png');
	pix = img.load();
	
	bits = '';
	# Read last bit of each colour channel
	for i in xrange(0,128):
		r,g,b = pix[i,0];
		bits += str(r&1)+str(g&1)+str(b&1);
	# Convert each 8 bits to a char
	bitscode = '';
	for i in range(32):
		bitscode += chr(int(bits[i*8:(i+1)*8], 2))
	# Calculate the result
	print result(comment, qr, bitscode, inputstring);
	
		
if __name__ == '__main__':
	main();
