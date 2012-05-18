import sys;
import time;
import datetime;

# LEDs turning ON on a digit
ledsPerDigit = [6, 2, 5, 5, 4, 5, 6, 3, 7, 6];
# LEDs turning ON on a 2 digit number
ledsPerNumber = [ledsPerDigit[i/10]+ledsPerDigit[i%10] for i in range(60)];
# LEDs turning on in a 0-23 and 0-59 intervals
ledsTo24 = sum(ledsPerNumber[:24]);
ledsTo60 = sum(ledsPerNumber);

# LEDs turning ON in a day (not counting the next 00:00:00)
ledsPerDay = ledsTo24*3600 + ledsTo60*60*24 + ledsTo60*60*24;

# LEDs turning ON in numbers till N
partialSums = [ledsPerNumber[0]];
for i,v in enumerate(range(1,60)):
	partialSums.append(partialSums[-1]+ledsPerNumber[v]);
	
# Just to remember how much seconds a day has
secondsInADay = 86400;

# Different deltas for different positions
deltasPerDigit0to9 = [1,0,4,1,1,2,1,1,4,0]
deltasPerDigit0to5 = [2,0,4,1,1,2]
deltasPerDigit0to3 = [2,0,4,1]
deltasPerDigit0to2 = [2,0,4]
# Deltas for the numbers that are going from 0 to 60
# When going from 01 to 02 we don't need to apply deltas to 0
deltasPerSecondNumber = [];
for i in range(6):
	for j in range(10):
		if (j==0):
			deltasPerSecondNumber += [deltasPerDigit0to5[i]+deltasPerDigit0to9[j]];
		else:
			deltasPerSecondNumber += [deltasPerDigit0to9[j]];
		
# Deltas for 0-23
deltasPerHourNumber = [];
for i in range(2):
	for j in range(10):
		if (j==0):
			if (i == 0):
				deltasPerHourNumber += [deltasPerDigit0to2[i]+deltasPerDigit0to3[j]];
			else:				
				deltasPerHourNumber += [deltasPerDigit0to2[i]+deltasPerDigit0to9[j]];
		else:
			deltasPerHourNumber += [deltasPerDigit0to9[j]];
i = 2;
for j in range(4):
	if (j==0):
		deltasPerHourNumber += [deltasPerDigit0to2[i]+deltasPerDigit0to9[j]];
	else:
		deltasPerHourNumber += [deltasPerDigit0to3[j]];


# So how much deltas we do in a day?
secondDeltasInAMinute = sum(deltasPerSecondNumber);
deltasPerDay = secondDeltasInAMinute*60*24 + secondDeltasInAMinute*24 + sum(deltasPerHourNumber);

# Partial deltas
# Note that for 0 is 0, because we suppose that 0 is already turned ON when we start
partialSecondDeltas = [0]
for i,v in enumerate(deltasPerSecondNumber[1:]):
	partialSecondDeltas += [partialSecondDeltas[-1]+v];

# Partial deltas for hours (same thing)
partialHourDeltas = [0];
for i,v in enumerate(deltasPerHourNumber[1:]):
	partialHourDeltas += [partialHourDeltas[-1]+v];

def main():
	for line in sys.stdin:
		splittedLine = line.strip().split(' - ')
		startDate,endDate = [time.strptime(dateStr.strip(), '%Y-%m-%d %H:%M:%S') for dateStr in splittedLine[:2]];
		
		diff = int(time.mktime(endDate) - time.mktime(startDate));
		
		# oldLeds are turning ON leds
		oldLeds = 0;
		# We sum all the full days, so now we only have to calculate
		# The sum of 00:00:00 - hh:mm:ss on the same days
		# The new seconds are saved in tmpDiff
		# 1284
		
		oldLeds += (diff / secondsInADay) * ledsPerDay;
		tmpDiff = diff % secondsInADay;
		hh = tmpDiff/3600;
		tmpDiff = tmpDiff%3600;
		mm = tmpDiff/60;
		ss = tmpDiff%60;
		
		# print "Now the clock shows %d:%d:%d"%(hh,mm,ss);
		
		# So how much times the hour leds illuminate till hh:mm:ss?
		# 3600 times each number for the full hours (full hours are hh-1)
		if (hh > 0):
			oldLeds += partialSums[hh-1]*3600;
		# 60 the hh number for each full minute
		oldLeds += ledsPerNumber[hh]*mm*60;
		# one hh number per each second on the clock
		# plus one for 00
		oldLeds += ledsPerNumber[hh]*(ss+1);
		
		# How much much times the minutes leds illuminate?
		# 60 times each one per each full hour on the clock
		oldLeds += ledsTo60*60*hh;
		# 60 times each number to mm per each full minute on the clock
		if (mm > 0):
			oldLeds += partialSums[mm-1]*60;
		# mm number shows the same number as seconds and one for 00
		oldLeds += ledsPerNumber[mm]*(ss+1);
		
		# How much times the seconds leds illuminate?
		# 60 times each number per each full hour on the clock
		oldLeds += ledsTo60*60*hh;
		# each number per each full minute on the clock
		oldLeds += ledsTo60*mm;
		# each number to ss
		oldLeds += partialSums[ss];
		
		
		#
		# Now the new leds
		#
		
		newLeds = 36;
		# First we look for full days
		newLeds += (diff / secondsInADay) * deltasPerDay;
		# Same thing as before
		tmpDiff = diff % secondsInADay;
		hh = tmpDiff/3600;
		tmpDiff = tmpDiff%3600;
		mm = tmpDiff/60;
		ss = tmpDiff%60;
		
		# Now we sum partial deltas to the hours we are showing on the clock:
		newLeds += partialHourDeltas[hh];
		
		# Minute deltas: 60 per each hours
		newLeds += secondDeltasInAMinute*hh;
		# And the minutes
		newLeds += partialSecondDeltas[mm];
		
		# And the second deltas, we have 60 full minutes per each hour
		newLeds += secondDeltasInAMinute*hh*60;
		# And for each full minute
		newLeds += secondDeltasInAMinute*mm;
		# And the time the clock shows now:
		newLeds += partialSecondDeltas[ss];
			
		print oldLeds-newLeds
		
if __name__ == '__main__':
	main();
