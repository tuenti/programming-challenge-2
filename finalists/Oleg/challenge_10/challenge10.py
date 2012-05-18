import sys;

class Operation:
	def parse(self, terms, position):
		# Identify this operation, the arguments it needs and the arguments it returns
		if (terms[position] == '.'):
			self.type = 'root';
			self.argsn = 1;
			self.argsret = 1;
		elif (terms[position] == '$'):
			self.type = 'rest';
			self.argsn = 2;
			self.argsret = 1;
		elif (terms[position] == '@'):
			self.type = 'sum';
			self.argsn = 2;
			self.argsret = 1;
		elif (terms[position] == '&'):
			self.type = 'div';
			self.argsn = 2;
			self.argsret = 1;
		elif (terms[position] == 'conquer'):
			self.type = 'mod';
			self.argsn = 2;
			self.argsret = 1;
		elif (terms[position] == 'mirror'):
			self.type = 'mirror';
			self.argsn = 1;
			self.argsret = 1;
		elif (terms[position] == 'breadandfish'):
			self.type = 'duplicate';
			self.argsn = 1;
			self.argsret = 2;
		elif (terms[position] == '#'):
			self.type = 'mult';
			self.argsn = 2;
			self.argsret = 1;
		elif (terms[position] == 'fire'):
			self.type = 'first';
			self.argsn = 2;
			self.argsret = 1;
		elif (terms[position] == 'dance'):
			self.type = 'dance';
			self.argsn = 2;
			self.argsret = 2;
		# These are the arguments we have
		self.args = [];
		# How much arguments we will have (NOT the same as len(self.args) 
		# because some arguments may return more than one, for example)
		argsavailable = 0;
		while (argsavailable < self.argsn):
			if terms[position-1].isdigit():
				# If it's a number, just add it 
				self.args.append(Number(int(terms[position-1])));
				argsavailable+=1;
				position-=1;
			else:
				# It is not a number, it is an operation, so parse it
				op = Operation();
				(position,argsret) = op.parse(terms, position-1);
				# Now we are at the last parsed position and we have 
				# counted all the arguments returned
				argsavailable+=argsret;
				self.args.append(op);
		# Return the position, arguments we return, and the excess of arguments we have
		return (position,self.argsret+argsavailable-self.argsn);
	
	def value(self):
		self.argv = [];
		# Get our arguments values
		for arg in self.args:
			self.argv += arg.value();
			
		# Return the value, and the excess of arguments
		if (self.type=='root'):
			retval = self.argv[0];
		elif (self.type=='sum'):
			retval = [self.argv[1]+self.argv[0]]+self.argv[2:];
		elif (self.type=='rest'):
			retval = [self.argv[1]-self.argv[0]]+self.argv[2:];
		elif (self.type=='div'):
			retval = [self.argv[1]/self.argv[0]]+self.argv[2:];
		elif (self.type=='mod'):
			retval = [self.argv[1]%self.argv[0]]+self.argv[2:];
		elif (self.type=='mirror'):
			retval = [self.argv[0]*-1];
		elif (self.type=='mult'):
			retval = [self.argv[1]*self.argv[0]]+self.argv[2:];
		elif (self.type=='duplicate'):
			retval = [self.argv[0],self.argv[0]]+self.argv[1:];
		elif (self.type=='first'):
			retval = [self.argv[1]]+self.argv[2:];
		elif (self.type=='dance'):
			retval = [self.argv[1],self.argv[0]]+self.argv[2:];
		else:
			retval = [0];
		return retval;		
		
				
class Number:
	# Just a number
	def __init__(self, number):
		self.number = number;
	def value(self):
		return [self.number];
	
def main():
	for line in sys.stdin:
		terms = line.strip().split(' ');
		# Each operation must end with "."
		if (terms[-1]) != '.':
			raise BaseException('Invalid operation');
		# Parse operation
		root = Operation();
		root.parse(terms,len(terms)-1);
		print root.value();
			
if __name__ == '__main__':
	main();
