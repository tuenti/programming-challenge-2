#!/usr/bin/python
# I recommend using "PyPy" instead, it's a lot faster on algorithmic code

import sys, multiprocessing
from math import factorial

def binomial_naive(n,k):
	return factorial(n)/(factorial(k)*factorial(n-k))

# more efficient than the naive one. Got it from: http://userpages.umbc.edu/~rcampbel/Computers/Python/probstat.html
def binomial(n,k):
	accum = 1
	for m in xrange(1,k+1):
		accum = accum*(n-k+m)/m
	return accum

"""
The sheep code is quite similar to the orangutan one.
I don't know which are better programmers, though.

>	Ook. Ook?	Move the pointer to the right
<	Ook? Ook.	Move the pointer to the left
+	Ook. Ook.	Increment the memory cell under the pointer
-	Ook! Ook!	Decrement the memory cell under the pointer
.	Ook! Ook.	Output the character signified by the cell at the pointer
,	Ook. Ook!	Input a character and store it in the cell at the pointer
[	Ook! Ook?	Jump past the matching Ook? Ook! if the cell under the pointer is 0
]	Ook? Ook!	Jump back to the matching Ook! Ook?
"""
# Sorry, but I feel more natural working in brainfuck
translator = {'.?':'>', '?.':'<', '..':'+', '!!':'-', '!.':'.', '.!':',', '!?':'[', '?!':']'}

"""
Brainfuck code:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.+++++++++++++++++++++++++++++++++++++.++.+++++.-.>+[-]++++++++++++++++++++++++++++++++.<-----------.++++++++++.>+[-]++++++++++++++++++++++++++++++++.<+.------------.---.>+[-]++++++++++++++++++++++++++++++++.<+++++++++.+++++++.--------.-----------.+++.+++++++++++++.>+[-]++++++++++++++++++++++++++++++++.<---.---------.>+[-]++++++++++++++++++++++++++++++++.<+++++++++++++.+.--.-----------------.++++++++.--.+.++++++++++++.>+[-]++++++++++++++++++++++++++++++++.<-----------------.++++++++++++++++++.-.-.>+[-]++++++++++++++++++++++++++++++++.<------.------------.+++.+.>+[-]++++++++++++++++++++++++++++++++.<+++++++++++++++.------------.++++++++++.---.++++++.--------------.+.>+[-]++++++++++++++++++++++++++++++++.<-------.>+[-]++++++++++++++++++++++++++++++++.<+++++++++++++++++.---.++++++.-------.----------.>+[-]++++++++++++++++++++++++++++++++.<-.+++++.+++++++.------------.++++++++++++.---.-----------.+++++++++++++++++++.---------------.>+[-]++++++++++++++++++++++++++++++++.<--.--.++++++++++.------.>+[-]++++++++++++++++++++++++++++++++.<----.+++++++++++++.----------.>+[-]++++++++++++++++++++++++++++++++.<+++++++++++.++++++.-.----.+++++.-.>+[-]++++++++++++++++++++++++++++++++.<-----------.++++++++++.>+[-]++++++++++++++++++++++++++++++++.<+.------------.---.>+[-]++++++++++++++++++++++++++++++++.<++++++++.------------.+++++++++++++++++++++++.---------------.++++.++++++++.--------.>+[-]++++++++++++++++++++++++++++++++.<+.+++++++.--------.-----------.+++.+++++++++++++.>+[-]++++++++++++++++++++++++++++++++.<---.---------.>+[-]++++++++++++++++++++++++++++++++.<---.--.++++++++++.------.>+[-]++++++++++++++++++++++++++++++++.<+++++++++++.-------.----.--.++.++++++++++++++.>+[-]++++++++++++++++++++++++++++++++.<+.------------.-------.+++++++++++++++++++.>+[-]++++++++++++++++++++++++++++++++.<-----------------.--.+++++++++++++.>+[-]++++++++++++++++++++++++++++++++.<------------.+++.>+[-]++++++++++++++++++++++++++++++++.<+++++++++++.++.---.-----------.+++++++++++++++++.------------------.++.-.------------------------------------------------------.
Output of the program:
Input is the number of straight cuts made through a round chocolate cake and output is the maximum number of cake pieces that can be produced.
"""

def main(n):
	# got the clue from: http://www.murderousmaths.co.uk/teacher/pizza.htm
	# I guess that if it works for pizza, it does for chocolate cake too
	return binomial(n+1, 2) + 1


# The real algorithm starts here:
def get_brainfuck():
	data = []
	for line in open("program.bee.txt"):
		data += map(lambda x: x[3], line.split())
	commands = []
	for i in xrange(0, len(data), 2):
		commands.append(translator[data[i]+data[i+1]])
	print ''.join(commands)


def parse_input():
	data = []
	input_dump = open("input.txt", "w")
	line = sys.stdin.readline()
	input_dump.write(line)
	n = int(line)
	for _ in xrange(n):
		line = sys.stdin.readline()
		input_dump.write(line)
		d = int(line)
		data.append(d)
	input_dump.close()
	return data


if __name__ == '__main__':
	# get_brainfuck()
	data = parse_input()
	for n, d in enumerate(data):
		result = main(d)
		print("Case #" + str(n+1) + ": " + str(result))
	
