all: breakkey

breakkey: breakkey.o desexample.o
	gcc -O4 -o breakkey breakkey.o desexample.o -lcrypt
#	gcc -O4 -o breakkey breakkey.o ../fastDES/des-ka9q-1.0-portable/deskey.o ../fastDES/des-ka9q-1.0-portable/desport.o ../fastDES/des-ka9q-1.0-portable/dessp.o

breakkey.o: breakkey.c 
	gcc -O4 -c breakkey.c

desexample.o: desexample.c
	gcc -O4 -c desexample.c
