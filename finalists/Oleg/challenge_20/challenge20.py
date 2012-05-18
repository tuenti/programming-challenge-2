import sys;
import fileinput;
import binascii
from multiprocessing import Process, Queue
from Crypto.Cipher import DES,AES

# Checking if it's an ASCII string with characters under 128
def isCorrect(s):
	for c in s[:20]:
		if (ord(c) > 127):
			return False;
	return True;

# Remove padding as in RFC 1423 (thanks for the tip, but it just made me the things more difficult)
def removePadding(ts):
	i = 0;
	ns = '';
	while i < len(ts):
		if (ord(ts[i])>=32):
			ns+=ts[i];
			i+=1;
		else:
			i+=ord(ts[i]);
	return ns;

# Function for processes. Makes brute force over DES with "weak" keys
# By the way, "weak" keys has a special meaning
def keysFinder(games, queue):
	chars = range(48, 58, 2)  + range(97, 123,2);
	keys = [];
	for game in games:
		found = False;
		bingame = binascii.unhexlify(game);
		for i in chars:
			for j in chars:
				for k in chars:
					for l in chars:
						key = chr(i)+chr(j)+chr(k)+chr(l);
						x = DES.new(key+'0000');
						dec = x.decrypt(bingame);
						# If it starts with Key= search for Puzzle
						if (dec[:4] == 'Key='):
							if (dec.count('Puzzle')>0):
								found = True;
								splitted = dec.split(' & ');
								puzzlekey = splitted[0].split('=')[1];
								keys += [puzzlekey];
					if found:
						break;
				if found:
					break;
			if found: 
				break;
		if not found:
			raise BaseException("Key not found");
	# Put found keys in the queue
	queue.put(keys);

def main():
	# Threads we will use, don't change this because each thread calculates keys for 100 games exactly
	# (You can change this if you know how, I'm too euphoric now to do more flexibility)
	threads = 10;
	for line in sys.stdin:
		# Parsing the stdin
		encryptedMessage,encryptedGames = line.strip().split(':');
		encryptedGames = encryptedGames.split('~');
		# Queue with keys
		q = Queue();
		# Threads
		for i in range(10):
			p = Process(target=keysFinder, args=(encryptedGames[i*100:(i+1)*100],q));
			p.start();
		# Number of threads already finished
		finished = 0;
		keys = [];
		while finished < threads:
			keys += q.get();
			finished+=1;
#
#		f = open('keys'+str(count),'w');
#		for k in keys:
#			f.write(k+'\n');
#		f.close();
#		print "keys written";
#		f = open('message'+str(count), 'w');
#		f.write(encryptedMessage);
#		f.close();
#		print "message too";
#		count+=1;
#
		# From all keys, try which one decrypts a valid message
		em = binascii.unhexlify(encryptedMessage);
		found = False;
		for key in keys:
			x = AES.new(key);
			dec = x.decrypt(em);
			if (isCorrect(dec)):
				found = True;
				# Make unpadding and print. Voila!
				print removePadding(dec.strip());

#	for i in range(5):		
#		em = '';
#		for line in fileinput.input('message'+str(i)):
#			em+=line.strip();
#		em = binascii.unhexlify(em);
#		keys = [];
#		for line in fileinput.input('keys'+str(i)):
#			keys+=[line.strip()]
#			
		
				
if __name__ == '__main__':
	main();
