#!/usr/bin/python

# Hard one, I didn't remember that PNG allowed comments.
# 1. lsb of first pixels:
# 0011011000110010011000110110010000110010001101110011010100111001001110000011100101100101001101110011100001100101011001010011010100110110011000010011100000110001011001100011000000110010001101100011010101100001001110000011011100110101001101100011001001100101
# decoded: 62cd275989e78ee56a81f0265a87562e
#
# 2. QR code: ed8ce15da9b7b5e2ee70634cc235e363
#
# 3. PNG comment: a541714a17804ac281e6ddda5b707952


if __name__ == '__main__':
	last_key = raw_input()[:32]
	# fix temporal, por jorge@tuenti.com :
	last_key = "1ee7453658914cd7463B77032fdbb623"
	
	keys = ["62cd275989e78ee56a81f0265a87562e", "ed8ce15da9b7b5e2ee70634cc235e363", "a541714a17804ac281e6ddda5b707952", last_key.lower()]
	#keys = ("a182", "1357", "23f1", "2353")
	digits = "0123456789abcdef"
	res = ""
	for i in xrange(len(keys[0])):
		d = 0
		for k in keys:
			d += digits.index(k[i])
		d %= 16
		res += digits[d]
	print res