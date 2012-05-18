import sys;
from math import sqrt, atan2, pi, sin, cos, degrees;
from operator import itemgetter;

# Our pizza object
class Pizza:
	def __init__(self,center,radius):
		self.pizzaCenter = center;
		self.pizzaRadius = radius;
		self.used = [];
		self.ingredients = dict();
		self.edges = dict();
	
	# Add an ingredient to our pizza
	# Get vertices' angles, get min and max and set them as used
	def addIngredient(self,typeName,center,vertex):	
		self.ingredients[typeName].append(angle(self.pizzaCenter,center));
		allVertices = polyVertices(center, vertex, self.edges[typeName]);
		allAngles = [angle(self.pizzaCenter,V) for V in allVertices];
		alpha = angleMin(*allAngles);
		beta = angleMax(*allAngles);
		if (typeName == 'cheese'):
			pass;
		self.use(alpha,beta);
		
	# Add an ingredient type
	def addIngredientType(self,typeName,edges):
		self.ingredients[typeName] = [];
		self.edges[typeName] = edges;
	
	# Use alpha-beta angles space
	def use(self,alpha,beta):
		self.used.append([alpha,beta]);
		self.checkIntersections();
	
	# If two used space intersect, make them one
	def checkIntersections(self):
		if (len(self.used)>1):
			modified = False;
			self.used = sorted(self.used, key=itemgetter(0));
			i = 0;
			while (i<len(self.used) and not modified):
				if (smaller(self.used[i-1][0],self.used[i][0]) and smaller(self.used[i][0], self.used[i-1][1])):
					newrange = [angleMin(self.used[i-1][0],self.used[i][0]), angleMax(self.used[i-1][1],self.used[i][1])];
					range1 = self.used[i-1];
					range2 = self.used[i];
					self.used.remove(range1);
					self.used.remove(range2);
					self.used.append(newrange);
					modified = True;
				i+=1;
			if not modified:
				self.used = sorted(self.used, key=itemgetter(1));
				i = 0;
				while (i<len(self.used) and not modified):
					if (smaller(self.used[i-1][0],self.used[i][1]) and smaller(self.used[i][1], self.used[i-1][1])):
						newrange = [angleMin(self.used[i-1][0],self.used[i][0]), angleMax(self.used[i-1][1],self.used[i][1])];
						range1 = self.used[i-1];
						range2 = self.used[i];
						self.used.remove(range1);
						self.used.remove(range2);
						self.used.append(newrange);
						modified = True;
					i+=1;
			if modified:
				self.checkIntersections();
	
	# Get valid cuts. Basically where used space begins
	# Our knife has float precision!!
	def getValidCuts(self):
		validCuts = [];
		if (len(self.used) == 0):
			validCuts += [0.0];
		elif (len(self.used) == 1):
			validCuts += [self.used[0][0]];
		else:
			for u in self.used:
				validCuts += [u[0]];
		return validCuts;
	
	# Main method to ask whether the pizza is possible to cut
	def isPossibleToCut(self):
		for angle in self.getValidCuts():
			if self.tryToCut(angle):
				return True;
		return False;
	
	# Try to cut our pizza with an angle
	def tryToCut(self,cutAngle):
		for u in self.used:
			# Check if the other side of the pizza is used
			if (smaller(u[0],opposite(cutAngle)) and smaller(opposite(cutAngle),u[1])):
				return False;
		# Check ingredients
		for typeName in self.ingredients:
			items = [0,0];
			for angle in self.ingredients[typeName]:
				# If center vertex is on one side, all the ingredient will be there
				if smaller(angle,cutAngle):
					items[0]+=1;
				else:
					items[1]+=1;
			if (items[0] != items[1]):
				return False;
		return True;
			
		
				

# Opposite of an angle
def opposite(alpha):
	if (alpha>0):
		return alpha-pi;
	else:
		return alpha+pi;
# Max and min for angles
def angleMax(*args):
	return reduce(lambda a1,a2: a2 if smaller(a1,a2) else a1, args);
def angleMin(*args):
	return reduce(lambda a1,a2: a1 if smaller(a1,a2) else a2, args);

# Angle that forms point P respect to the center C
def angle(C,P):
	alpha = 0;
	if (P[0]-C[0] == 0.0):
		if (P[0]-C[0] > 0):
			alpha = pi/2;
		else:
			alpha = -pi/2;
	elif(P[1]-C[1] == 0.0):
		if (P[1]-C[1] > 0):
			alpha = 0.0;
		else:
			alpha = pi;
	else:
		alpha = atan2(P[1]-C[1],P[0]-C[0]);
	return alpha;

# Distance between two points
def distance(P1,P2):
	return sqrt(pow(P1[1]-P2[1], 2) +pow(P1[0]-P2[0], 2));

# Vertices of a polygon
def polyVertices(C,V,edges):
	alpha = angle(C,V);
	dist = distance(C,V);
	vertex = [];
	for k in range(edges):
		theta = alpha+2*pi*k/edges;
		vertex.append((dist*cos(theta)+C[0],dist*sin(theta)+C[1]));
	return vertex;

# Angle comparison
def smaller(a1,a2):
	if (a1 <= a2):
		if (a2-a1<pi):
			return True;
		else:
			return False;
	else:
		return not smaller(a2,a1);

def main():
	# No comments needed
	testCasesNumber = int(sys.stdin.next().strip());
	testCase = 1;
	while testCase <= testCasesNumber:
		Cx,Cy,R = [float(v) for v in sys.stdin.next().strip().split(' ')];
		C = (Cx,Cy);
		pizza = Pizza(C,R);
		typesOfIngridientsNumber = int(sys.stdin.next().strip());
		for i in xrange(typesOfIngridientsNumber):
			line = sys.stdin.next().strip().split();
			n = int(line[2]);
			typeId = line[0];
			pizza.addIngredientType(typeId,int(line[1]));
			for j in xrange(n):
				cijx,cijy,vijx,vijy = [float(v) for v in sys.stdin.next().strip().split(' ')]
				pizza.addIngredient(typeId, (cijx,cijy), (vijx,vijy));
				
		print "Case #%d: %s" %(testCase, str(pizza.isPossibleToCut()).upper());
		testCase+=1;
				
if __name__ == '__main__':
	main();
