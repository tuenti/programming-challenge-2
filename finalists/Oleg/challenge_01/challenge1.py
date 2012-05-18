import sys

# Debug mode
debug = False;

# Buttons list
buttons = range(10);

# Characters for each button (numbers ommited)
characters = ['',' ','ABC','DEF','GHI','JKL','MNO','PQRS','TUV','WXYZ'];

# Dictionary of tuples for each button, each tuple is calculated later and it will be (button, number of presses needed to type)
characterButtons = dict();

# Distance dictionary. It's easier to just write it down here as to calculate it each time
distances = {0: {1:950,2:900,3:950,4:650,5:600,6:650,7:350,8:300,9:350,-1:200}, \
			1: {0:950,2:200,3:400,4:300,5:350,6:550,7:600,8:650,9:700,-1:1000}, \
			2: {1:200,3:200,4:350,5:300,6:350,7:650,8:600,9:650,0:900,-1:950}, \
			3: {1:400,2:200,4:550,5:350,6:300,7:700,8:650,9:600,0:950,-1:900}, \
			4: {1:300,2:350,3:550,5:200,6:400,7:300,8:350,9:550,0:650,-1:700}, \
			5: {1:350,2:300,3:350,4:200,6:200,7:350,8:300,9:350,0:600,-1:650}, \
			6: {1:550,2:350,3:300,4:400,5:200,7:550,8:350,9:300,0:650,-1:600}, \
			7: {1:600,2:650,3:700,4:300,5:350,6:550,8:200,9:400,0:350,-1:550}, \
			8: {1:650,2:600,3:650,4:350,5:300,6:350,7:200,9:200,0:300,-1:350}, \
			9: {1:700,2:650,3:600,4:550,5:350,6:300,7:400,8:200,0:350,-1:300}, \
			-1: {1:1000,2:950,3:900,4:700,5:650,6:600,7:550,8:350,9:300,0:200} \
	}

# Prints a debug message if debug mode is True
def debugMsg(s):
	if debug:
		print s;

# Check that the distances dictionary is symmetric (ignores the diagonal)
def checkDistances():
	for i in range(-1,10):
		for j in range(-1,10):
			if (i != j):
				if (distances[i][j] != distances[j][i]):
					raise BaseException("Distance error at %d,%d" % (i,j));

# Calculates character button for each character and the number of times needed to be pressed
def calculateCharacterButtons():			
	for i,chars in enumerate(characters):
		j = 1;
		for k,char in enumerate(chars):
			characterButtons[char] = (i,j+k);
			characterButtons[char.lower()] = (i,j+k);
		characterButtons[str(i)] = (i, len(chars)+1);

# Main function that calculates the time
def calculateStringTime(s):
	# Current button under the finger
	currentButton = 0;
	# Current time
	t = 0;
	# If it's the first button and we want to press 0, we don't need to wait 500ms
	firstButton = True;
	# Caps lock initial state
	capsLock = False;
	# Main loop for chars
	for char in s:
		debugMsg("Time is %d" % t)
		# Check if we have to toggle caps lock
		if (not char.isdigit() and not char.isspace() and capsLock != char.isupper()):
			t += distances[currentButton][-1];
			debugMsg("Moving from %d to CAPSLOCK" % (currentButton));
			capsLock = not capsLock;
			debugMsg("Pressing CAPSLOCK and its now going to "+str(capsLock));
			t += 100;
			currentButton = -1;
			firstButton = False;
		
		button = characterButtons[char];
		# Check if we have to move our finger
		if (button[0] == currentButton):
			if not firstButton:
				debugMsg("Waiting because it's the same button");
				t += 500;
			t += button[1]*100;
			debugMsg("Pressing button '%d' %d times" % button);
		else:
			t += distances[currentButton][button[0]];
			debugMsg("Moving from %d to %d" % (currentButton,button[0]));
			currentButton = button[0];
			t += button[1]*100;
			debugMsg("Pressing button '%d' %d times" % button);
		firstButton = False;
	return t;
		
		
def main():
	# Don't lose time with this
	# checkDistances();
	calculateCharacterButtons();
	testCasesNumber = int(sys.stdin.next());
	testCaseNumber = 0;
	while testCaseNumber < testCasesNumber:
		testCase = sys.stdin.next().strip();
		print calculateStringTime(testCase);
		testCaseNumber += 1;
	
if __name__ == '__main__':
	main();
