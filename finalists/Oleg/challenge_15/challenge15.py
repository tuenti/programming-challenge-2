from PIL import Image
from math import sqrt


def prime(number):
	if number == 2:
		return True
	elif (number % 2 == 0):
		return False;
	f = round(sqrt(number))
	for n in range(3,int(f)+1,2):
		if number % n == 0:
			return False
	return True

def main():	
	emirp = 0; # 2 is emirp
	for n in range(13,100000,2):
		if prime(n):
			if (prime(int(str(n)[::-1])) and int(str(n)[::-1]) != n):
				emirp += 1;
				if (emirp == 20):
					print n;
					break;

	
if __name__ == '__main__':
	main();
