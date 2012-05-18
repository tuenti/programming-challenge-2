import sys
from operator import itemgetter, attrgetter

# Find minimums and maximums in the data
def findExtremes(data):
	data += [(float("inf"), len(data))];
	mins = [];
	lastVal = float("inf"); # infinity
	for i,v in enumerate(data[:-1]):
		if (v[0]<=lastVal and v[0]<=data[i+1][0]):
			mins += [v];
		lastVal = v[0];
		
	data[-1] = [(-float("inf"), len(data)-1)];
	maxs = [];
	lastVal = -float("inf"); # infinity
	for i,v in enumerate(data[:-1]):
		if (v[0]>=lastVal and v[0]>=data[i+1][0]):
			maxs += [v];
		lastVal = v[0];
	return (mins,maxs);

# Find the best moments to buy and sell
# We order maximums and minimums and remove elements that minimize the
# loss until it's a valid option (buy before sell)
def findBestOption(mins,maxs):
	mins = sorted(mins,key=itemgetter(0));
	maxs = sorted(maxs,key=itemgetter(0),reverse=True);
	while mins[0][1]>maxs[0][1]:
		if (len(mins)>1 and len(maxs)>1):
			if (mins[1][0]-mins[0][0] > maxs[0][0] - maxs[1][0]):
				maxs.remove(maxs[0]);
			else:
				mins.remove(mins[0]);
		elif (len(mins)==1):
			maxs.remove(maxs[0]);
		# Always remove something, so there will be no infinite loop
		else:
			mins.remove(mins[0]);
	return (mins[0],maxs[0], maxs[0][0]-mins[0][0]);
			
			

def main():
	data = [];
	i = 0;
	# All the data is treated as (data, position)
	for line in sys.stdin:
		data += [(int(line.strip()), i)];
		i+=1;
		
	mins,maxs = findExtremes(data);
	
	buy,sell,win = findBestOption(mins,maxs);
	
	print str(buy[1]*100)+' '+str(sell[1]*100)+' '+str(win);

if __name__ == '__main__':
	main();
