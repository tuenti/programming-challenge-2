import sys;			

# This function calculates the number of groups that can run in race
# when starting at group i, and returns the gasoline used;
def raceGasoline(k,G,groups):
	restk = k;
	gasolinePerRace = [0]*G;
	groupsPerRace = [0]*G;
	for i in range(len(groups)):
		j = 0;
		while(restk >= groups[(i+j) % G] and j < G):
			gasolinePerRace[i] += groups[(i+j) % G];
			restk -= groups[(i+j) % G];
			j += 1;
		groupsPerRace[i] = j;
		restk = k;
	return (gasolinePerRace, groupsPerRace);


def main():
	testCasesNumber = int(sys.stdin.next().strip());
	testCase = 0;
	while (testCase < testCasesNumber):
		R,k,G = [int(v) for v in sys.stdin.next().strip().split(' ')];
		groups = [int(v) for v in sys.stdin.next().strip().split(' ')];
		
		usedGasoline = 0;
		gasolinePerRace,groupsPerRace = raceGasoline(k,G,groups);
		
		# We will search for a period in the group cycling
		startPoints = [];
		periodGasoline = 0;
		i = 0;
		while (i%G not in startPoints):
			startPoints += [i%G];
			periodGasoline += gasolinePerRace[i%G];	
			i += groupsPerRace[i%G];		
		
		# The group where the period starts is periodGroup
		periodGroup = i%G;	
		currentRace = 1;
		currentGroup = 0;
		
		# Remove the first elements till the period start
		# Do not forget to remove the gasoline from that elements too
		while (startPoints[0] != periodGroup):
			periodGasoline -= gasolinePerRace[startPoints[0]];
			startPoints = startPoints[1:];
		periodLength = len(startPoints);
		
		
		# Start the races until the period starts
		while (currentRace <= R and currentGroup != periodGroup):
			usedGasoline += gasolinePerRace[currentGroup%G];
			currentGroup += groupsPerRace[currentGroup%G];
			currentRace += 1;
		
		# Use the period gasoline
		usedGasoline += (R-currentRace) / periodLength * periodGasoline;
		currentRace = R- ((R-currentRace) % periodLength)-1;
		
		# Finish the modulus races
		while (currentRace <= R):
			usedGasoline += gasolinePerRace[currentGroup%G];
			currentGroup += groupsPerRace[currentGroup%G];
			currentRace += 1;
		
		print usedGasoline;
		
		testCase += 1;
		
if __name__ == '__main__':
	main();
