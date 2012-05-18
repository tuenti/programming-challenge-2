import sys;
import md5;
import time;

def main():
	# Original queue
	queueString = sys.stdin.next().strip();
	# Adjustments
	adjustments = [];
	for line in sys.stdin:
		parsed = line.strip().split(',');
		transformations = dict();
		# Transformations
		for transformation in parsed:
			splitted = transformation.split('=>');
			transformations[splitted[0]] = splitted[1];
		adjustments.append(transformations);
	
	# Hasher
	hasher = md5.new();
	# Buffer to save in which persons clones a person after all adjustments
	buf = dict();
	# For each person...
	for i,c in enumerate(queueString):
		# Try if it's already in the buffer
		try:
			hasher.update(buf[c]);
		except:
			# Calculate in other case. q is the queue
			q = c;
			la = len(adjustments);
			level = 0;
			while level < la:
					nq = '';
					# For each person try to apply adjustment, if doesn't
					# exist, person goes to the queue end
					for s in q:
						try:
							nq+=adjustments[level][s]
						except:
							nq+=s;
					# nq is the new queue;
					q = nq;
					# next level
					level+=1;
			# Save the buffer and hash it
			buf[c] = q;
			hasher.update(buf[c]);
	# Print the hash
	print hasher.hexdigest();
		
		
if __name__ == '__main__':
	main();
