
/*
 * des.c
 *
 * Example code to use the unix encypt() function.
 *
 * 2004 Chris Nystrom ()
 *
 * Public Domain
 *
 * Thank you to Wayne C. Morris for assistance.
 *
 * $ gcc -lcrypt des.c
 * $ ./a.out
 *
 */

#include <stdio.h>
#include <crypt.h>

#define ENCODE (0)
#define DECODE (1)

int
power(int base, int n)
{
  int p;

  for (p = 1; n > 0; --n)
    p = p * base;

  return p;
}

void
byte2bin(char *s, unsigned char b)
{
  int i;
  unsigned char mask = 0x80;

  for (i = 0; i < 8; ++i) {
    if (b & mask)
      *(s + i) = '\1';
    else
      *(s + i) = '\0';

    mask >>= 1;
  }
}

int
bin2byte(char *s)
{
  int i, j, ret = 0;

  for (i = 0; i < 8; i++) {
    if (*(s + i) == '\1') {
      j = 7 - i;
      ret += power(2, j);
    }
  }

  return(ret);
}

void
encode(char *s_out, char *s_in)
{
  int i, j = 0;
  char tmp[9];

  for (i = 0; i < 8; i++) {
    j = (i * 8);
    byte2bin(s_out + j, *(s_in + i));
  }
}

void
decode(char *s_out, char *s_in)
{
  int i, j = 0;

  for (i = 0; i < 8; i++) {
    j = (i * 8);
    *(s_out + i) = bin2byte(s_in + j);
  }
}

void display_bitmap(char *msg)
{
  int i;

  for (i = 0; i < 64; i++) {
    printf( "%1d", (msg[i] ? 1 : 0) );
  }

  printf("\n");
}


int example()
{
  char key_in[9] = "12345678";
  char txt_in[9] = "abcdefgh";
  char txt_out[9];
  char key[64]; // bit pattern for key
  char txt[64]; // bit pattern for message

  printf("txt_in = |%s|\n", txt_in);

  encode(key, key_in);
  encode(txt, txt_in);

  setkey(key);

  // display_bitmap(txt);

  encrypt(txt, ENCODE);

  // display_bitmap(txt);

  decode(txt_out, txt);
  txt_out[8] = '\0';
  printf("txt_out (encoded) = |%s|\n", txt_out);

  encrypt(txt, DECODE);

  // display_bitmap(txt);

  decode(txt_out, txt);
  txt_out[8] = '\0';
  printf("txt_out (decoded) = |%s|\n", txt_out);
}


int decryptblock(char *key_in, char *txt_in, char *txt_out) {
  char key[64]; // bit pattern for key
  char txt[64]; // bit pattern for message

  encode(key, key_in);
  encode(txt, txt_in);
  setkey(key);
  encrypt(txt, DECODE);
  decode(txt_out, txt);
}


