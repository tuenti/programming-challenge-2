#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//defined in desexample.c
int decryptblock(char *key_in, char *txt_in, char *txt_out);

void hexstr2bytes(char *buffer, char *src) {
  int len=strlen(src);
  int num_bytes=len/2;

  char *dst = buffer;
  char *end = buffer + len;
  unsigned int u;

  while (dst < end && sscanf(src, "%2x", &u) == 1) {
    *dst++ = u;
    src += 2;
  }
}

int main(int argc, char *argv[]) {
  
  if (argc!= 4 || strlen(argv[1])!=16 || strlen(argv[2]) !=8 || strlen(argv[3]) != 8) {
    printf("Usage: %s <8 first encrypted bytes in (16 hex chars)> <4 first plaintext bytes in (8 hex chars)> <4 key padding bytes (8 hex chars)\n",argv[0]);
    exit(1);
  }
  char *encrypted_hex= argv[1];
  char *clear_hex = argv[2];
  char *padding_hex = argv[3];
    
  //printf("Encrypted (hex) %s\n",encrypted_hex);
  //printf("Clear (hex) %s\n",clear_hex);

  //Convert to bytes array
  char encrypted[8];
  char clear[4];
  hexstr2bytes(encrypted, encrypted_hex);
  hexstr2bytes(clear, clear_hex);



  //try keys
  char decoded[8];
  unsigned char key[9] ="????pppp\0";
  hexstr2bytes(&key[4], padding_hex);
  

  int c1,c2,c3,c4;

  #define MIN_CHAR 32
  #define MAX_CHAR 127
  //#define MIN_CHAR 0
  //#define MAX_CHAR 255

  for(c1 = MIN_CHAR ; c1 <= MAX_CHAR; c1 += 2) {
    key[0] = c1;
    //printf ("%d\n",key[0]);
    for(c2 = MIN_CHAR ; c2 <= MAX_CHAR; c2 += 2) {
      key[1] = c2;
      for(c3 = MIN_CHAR ; c3 <= MAX_CHAR; c3 += 2) {
	key[2] = c3;
	for(c4 = MIN_CHAR ; c4 <= MAX_CHAR; c4 += 2) {
	  key[3] = c4;
	  decryptblock(key, encrypted, decoded);
	  //if( !memcmp(decoded,clear,4) ) {

	  // get rid of parity bits
	  *(int *)decoded &= 0x7F7F7F7F;

	  if( *(int *)decoded == *(int *)clear) {
	    int k;
	    for(k = 0 ; k < 8 ; k++) {
	      printf("%02x",key[k]);
 	    }
	    //may be more than one!!
	    //exit(0);
	  }
	}
      }
    }
  }  
}
