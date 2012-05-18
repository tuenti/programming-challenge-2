#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <errno.h>





/////////////// AES Start {



// AES Implementation by X-N2O

// Started:  15:41:35 - 18 Nov 2009

// Finished: 20:03:59 - 21 Nov 2009

// Logarithm, S-Box, and RCON tables are not hardcoded

// Instead they are generated when the program starts

// All of the code below is based from the AES specification

// You can find it at http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf

// You may use this code as you wish, but do not remove this comment

// This is only a proof of concept, and should not be considered as the most efficient implementation



#ifndef __aes_h

#define __aes_h



#define AES_RPOL      0x011b // reduction polynomial (x^8 + x^4 + x^3 + x + 1)

#define AES_GEN       0x03   // gf(2^8) generator    (x^4 + 1)

#define AES_SBOX_CC   0x63   // S-Box C constant

#define AES_SBOX_MT   0x8f   // S-Box initial matrix row



#define KEY_128 (128/8)

#define KEY_192 (192/8)

#define KEY_256 (256/8)



#define aes_mul(a, b) ((a)&&(b)?g_aes_ilogt[(g_aes_logt[(a)]+g_aes_logt[(b)])%0xff]:0)

#define aes_inv(a)    ((a)?g_aes_ilogt[0xff-g_aes_logt[(a)]]:0)



extern unsigned char g_aes_logt[256], g_aes_ilogt[256];

extern unsigned char g_aes_sbox[256], g_aes_isbox[256];



typedef struct {

	unsigned char state[4][4];

	int kcol;

	unsigned long rounds;

	unsigned long keysched[0];

} aes_ctx_t;



void aes_init();

aes_ctx_t *aes_alloc_ctx(unsigned char *key, unsigned long keyLen);

inline unsigned long aes_subword(unsigned long w);

inline unsigned long aes_rotword(unsigned long w);

void aes_keyexpansion(aes_ctx_t *ctx);



inline unsigned char aes_mul_manual(unsigned char a, unsigned char b); // use aes_mul instead



void aes_subbytes(aes_ctx_t *ctx);

void aes_shiftrows(aes_ctx_t *ctx);

void aes_mixcolumns(aes_ctx_t *ctx);

void aes_addroundkey(aes_ctx_t *ctx, int round);

void aes_encrypt(aes_ctx_t *ctx, unsigned char input[16], unsigned char output[16]);



void aes_invsubbytes(aes_ctx_t *ctx);

void aes_invshiftrows(aes_ctx_t *ctx);

void aes_invmixcolumns(aes_ctx_t *ctx);

void aes_decrypt(aes_ctx_t *ctx, unsigned char input[16], unsigned char output[16]);



void aes_free_ctx(aes_ctx_t *ctx);



#endif //__aes_h





// AES Implementation by X-N2O

// Started:  15:41:35 - 18 Nov 2009

// Finished: 20:03:59 - 21 Nov 2009

// Logarithm, S-Box, and RCON tables are not hardcoded

// Instead they are generated when the program starts

// All of the code below is based from the AES specification

// You can find it at http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf

// You may use this code as you wish, but do not remove this comment

// This is only a proof of concept, and should not be considered as the most efficient implementation





unsigned char g_aes_logt[256], g_aes_ilogt[256];

unsigned char g_aes_sbox[256], g_aes_isbox[256];



void init_aes()

{

	int i;

	unsigned char gen;



	// build logarithm table and it's inverse

	gen = 1;

	for(i = 0; i < 0xff; i++) {

		g_aes_logt[gen]  = i;

		g_aes_ilogt[i]   = gen;

		gen = aes_mul_manual(gen, AES_GEN);

	}



	// build S-Box and it's inverse

	for(i = 0; i <= 0xff; i++) {

		char bi;

		unsigned char inv = aes_inv(i);



		g_aes_sbox[i] = 0;

		for(bi = 0; bi < 8; bi++) {

			// based on transformation 5.1

			// could also be done with a loop based on the matrix

			g_aes_sbox[i] |= ((inv & (1<<bi)?1:0)

						^ (inv & (1 << ((bi+4) & 7))?1:0)

						^ (inv & (1 << ((bi+5) & 7))?1:0) 

						^ (inv & (1 << ((bi+6) & 7))?1:0)

						^ (inv & (1 << ((bi+7) & 7))?1:0) 

						^ (AES_SBOX_CC & (1 << bi)?1:0)

			) << bi;

		}

		g_aes_isbox[g_aes_sbox[i]] = i;

	}

	// warning: quickhack

	g_aes_sbox[1] = 0x7c;

	g_aes_isbox[0x7c] = 1;

	g_aes_isbox[0x63] = 0;

}



aes_ctx_t *aes_alloc_ctx(unsigned char *key, unsigned long keyLen)

{

	aes_ctx_t *ctx;

	size_t rounds;

	size_t ks_size;



	switch(keyLen) {

		case 16: // 128-bit key

			rounds = 10;

			break;



		case 24: // 192-bit key

			rounds = 12;

			break;



		case 32: // 256-bit key

			rounds = 14;

			break;



		defaut:

			return NULL;

	}



	ks_size = 4*(rounds+1)*sizeof(unsigned long);

	ctx = malloc(sizeof(aes_ctx_t)+ks_size);

	if(ctx) {

		ctx->rounds = rounds;

		ctx->kcol = keyLen/4;

		memcpy(ctx->keysched, key, keyLen);

		ctx->keysched[43] = 0;

		aes_keyexpansion(ctx);

	}



	return ctx;

}



inline unsigned long aes_subword(unsigned long w)

{

	return g_aes_sbox[w & 0x000000ff] |

		(g_aes_sbox[(w & 0x0000ff00) >> 8] << 8) |

		(g_aes_sbox[(w & 0x00ff0000) >> 16] << 16) |

		(g_aes_sbox[(w & 0xff000000) >> 24] << 24);

}



inline unsigned long aes_rotword(unsigned long w)

{

	// May seem a bit different from the spec

	// It was changed because unsigned long is represented with little-endian convention on x86

	// Should not depend on architecture, but this is only a POC

	return ((w & 0x000000ff) << 24) |

		((w & 0x0000ff00) >> 8) |

		((w & 0x00ff0000) >> 8) |

		((w & 0xff000000) >> 8);

}



void aes_keyexpansion(aes_ctx_t *ctx)

{

	unsigned long temp;

	unsigned long rcon;

	register int i;



	rcon = 0x00000001;

	for(i = ctx->kcol; i < (4*(ctx->rounds+1)); i++) {

		temp = ctx->keysched[i-1];

		if(!(i%ctx->kcol)) {

			temp = aes_subword(aes_rotword(temp)) ^ rcon;

			rcon = aes_mul(rcon, 2);

		} else if(ctx->kcol > 6 && i%ctx->kcol == 4)

			temp = aes_subword(temp);

		ctx->keysched[i] = ctx->keysched[i-ctx->kcol] ^ temp;

	}

}



inline unsigned char aes_mul_manual(unsigned char a, unsigned char b)

{

	register unsigned short ac;

	register unsigned char ret;



	ac = a;

	ret = 0;

	while(b) {

		if(b & 0x01)

			ret ^= ac;

		ac <<= 1;

		b >>= 1;

		if(ac & 0x0100)

			ac ^= AES_RPOL;

	}



	return ret;

}



void aes_subbytes(aes_ctx_t *ctx)

{

	int i;



	for(i = 0; i < 16; i++) {

		int x, y;



		x = i & 0x03;

		y = i >> 2;

		ctx->state[x][y] = g_aes_sbox[ctx->state[x][y]];

	}

}



void aes_shiftrows(aes_ctx_t *ctx)

{

	unsigned char nstate[4][4];

	int i;



	for(i = 0; i < 16; i++) {

		int x, y;



		x = i & 0x03;

		y = i >> 2;

		nstate[x][y] = ctx->state[x][(y+x) & 0x03];

	}



	memcpy(ctx->state, nstate, sizeof(ctx->state));

}



void aes_mixcolumns(aes_ctx_t *ctx)

{

	unsigned char nstate[4][4];

	int i;

	

	for(i = 0; i < 4; i++) {

		nstate[0][i] = aes_mul(0x02, ctx->state[0][i]) ^ 

				aes_mul(0x03, ctx->state[1][i]) ^

				ctx->state[2][i] ^

				ctx->state[3][i];

		nstate[1][i] = ctx->state[0][i] ^

				aes_mul(0x02, ctx->state[1][i]) ^

				aes_mul(0x03, ctx->state[2][i]) ^

				ctx->state[3][i];

		nstate[2][i] = ctx->state[0][i] ^

				ctx->state[1][i] ^

				aes_mul(0x02, ctx->state[2][i]) ^

				aes_mul(0x03, ctx->state[3][i]);

		nstate[3][i] = aes_mul(0x03, ctx->state[0][i]) ^

				ctx->state[1][i] ^

				ctx->state[2][i] ^

				aes_mul(0x02, ctx->state[3][i]);

	}



	memcpy(ctx->state, nstate, sizeof(ctx->state));

}



void aes_addroundkey(aes_ctx_t *ctx, int round)

{

	int i;



	for(i = 0; i < 16; i++) {

		int x, y;



		x = i & 0x03;

		y = i >> 2;

		ctx->state[x][y] = ctx->state[x][y] ^

			((ctx->keysched[round*4+y] & (0xff << (x*8))) >> (x*8));

	}

}



void aes_encrypt(aes_ctx_t *ctx, unsigned char input[16], unsigned char output[16])

{

	int i;



	// copy input to state

	for(i = 0; i < 16; i++)

		ctx->state[i & 0x03][i >> 2] = input[i];



	aes_addroundkey(ctx, 0);



	for(i = 1; i < ctx->rounds; i++) {

		aes_subbytes(ctx);

		aes_shiftrows(ctx);

		aes_mixcolumns(ctx);

		aes_addroundkey(ctx, i);

	}



	aes_subbytes(ctx);

	aes_shiftrows(ctx);

	aes_addroundkey(ctx, ctx->rounds);



	// copy state to output

	for(i = 0; i < 16; i++)

		output[i] = ctx->state[i & 0x03][i >> 2];

}



void aes_invshiftrows(aes_ctx_t *ctx)

{

	unsigned char nstate[4][4];

	int i;



	for(i = 0; i < 16; i++) {

		int x, y;



		x = i & 0x03;

		y = i >> 2;

		nstate[x][(y+x) & 0x03] = ctx->state[x][y];

	}



	memcpy(ctx->state, nstate, sizeof(ctx->state));

}



void aes_invsubbytes(aes_ctx_t *ctx)

{

	int i;



	for(i = 0; i < 16; i++) {

		int x, y;



		x = i & 0x03;

		y = i >> 2;

		ctx->state[x][y] = g_aes_isbox[ctx->state[x][y]];

	}

}



void aes_invmixcolumns(aes_ctx_t *ctx)

{

	unsigned char nstate[4][4];

	int i;

	

	for(i = 0; i < 4; i++) {

		nstate[0][i] = aes_mul(0x0e, ctx->state[0][i]) ^ 

				aes_mul(0x0b, ctx->state[1][i]) ^

				aes_mul(0x0d, ctx->state[2][i]) ^

				aes_mul(0x09, ctx->state[3][i]);

		nstate[1][i] = aes_mul(0x09, ctx->state[0][i]) ^

				aes_mul(0x0e, ctx->state[1][i]) ^

				aes_mul(0x0b, ctx->state[2][i]) ^

				aes_mul(0x0d, ctx->state[3][i]);

		nstate[2][i] = aes_mul(0x0d, ctx->state[0][i]) ^

				aes_mul(0x09, ctx->state[1][i]) ^

				aes_mul(0x0e, ctx->state[2][i]) ^

				aes_mul(0x0b, ctx->state[3][i]);

		nstate[3][i] = aes_mul(0x0b, ctx->state[0][i]) ^

				aes_mul(0x0d, ctx->state[1][i]) ^

				aes_mul(0x09, ctx->state[2][i]) ^

				aes_mul(0x0e, ctx->state[3][i]);

	}



	memcpy(ctx->state, nstate, sizeof(ctx->state));

}



void aes_decrypt(aes_ctx_t *ctx, unsigned char input[16], unsigned char output[16])

{

	int i, j;



	// copy input to state

	for(i = 0; i < 16; i++)

		ctx->state[i & 0x03][i >> 2] = input[i];



	aes_addroundkey(ctx, ctx->rounds);

	for(i = ctx->rounds-1; i >= 1; i--) {

		aes_invshiftrows(ctx);

		aes_invsubbytes(ctx);

		aes_addroundkey(ctx, i);

		aes_invmixcolumns(ctx);

	}



	aes_invshiftrows(ctx);

	aes_invsubbytes(ctx);

	aes_addroundkey(ctx, 0);



	// copy state to output

	for(i = 0; i < 16; i++)

		output[i] = ctx->state[i & 0x03][i >> 2];

}



void aes_free_ctx(aes_ctx_t *ctx)

{

	free(ctx);

}













#if 0 // AES example



#include <stdlib.h>

#include "aes.h"



int main(int argc, char *argv[])

{

	unsigned char key[KEY_128] = "uber strong key!";

	unsigned char ptext[16] = "Attack at dawn!";

	unsigned char ctext[16];

	unsigned char decptext[16];

	aes_ctx_t *ctx;



	init_aes();

	ctx = aes_alloc_ctx(key, sizeof(key));

	if(!ctx) {

		perror("aes_alloc_ctx");

		return EXIT_FAILURE;

	}

	aes_encrypt(ctx, ptext, ctext);

	aes_decrypt(ctx, ctext, decptext);

	puts(decptext);



	aes_free_ctx(ctx);

	return EXIT_SUCCESS;

}



#endif





/////////////// AES END }





#define DEBUG 0



typedef unsigned long long int uint64_t;

typedef unsigned int uint32_t;



typedef const uint32_t sbox_t[64];









static inline uint64_t do_doubleLeftRotate (const int rot, const uint64_t in)

{

  uint64_t l;

  uint64_t h;



#if DEBUG

  //fprintf(stderr, "\n\tdoubleLeftRotate(%d, %014I64x)\n", rot, in);

#endif



  l = in & 0xFFFFFFFULL;

  h = in & 0xFFFFFFF0000000ULL;



#if DEBUG

  //fprintf(stderr, "\t\t h = %016I64x ; l = %016I64x\n", h, l);

#endif



  l <<= rot;

  h <<= rot;



#if DEBUG

  //fprintf(stderr, "\t\t h = %016I64x ; l = %016I64x\n", h, l);

#endif



  if (rot == 1)

  {

    l = (l & 0xFFFFFFEULL) | (l >> 28);

    h = (h & 0xFFFFFFE0000000ULL) | ((h >> 28) & 0x10000000ULL);

#if DEBUG

  //fprintf(stderr, "\t\t h = %016I64x ; l = %016I64x\n", h, l);

#endif



  }

  else // rot == 2

  {

    l = (l & 0xFFFFFFCULL) | (l >> 28);

    h = (h & 0xFFFFFFC0000000ULL) | ((h >> 28) & 0x30000000ULL);

#if DEBUG

  //fprintf(stderr, "\t\t h = %016I64x ; l = %016I64x\n", h, l);

#endif



  }



#if DEBUG

  //fprintf(stderr, "\t\t l | h = %016I64x\n", l | h);

#endif





  return l | h;

}



// Initial permutation

static const int IP[64] = {

  58, 50, 42, 34, 26, 18, 10, 2,

  60, 52, 44, 36, 28, 20, 12, 4,

  62, 54, 46, 38, 30, 22, 14, 6,

  64, 56, 48, 40, 32, 24, 16, 8,

  57, 49, 41, 33, 25, 17, 9, 1,

  59, 51, 43, 35, 27, 19, 11, 3,

  61, 53, 45, 37, 29, 21, 13, 5,

  63, 55, 47, 39, 31, 23, 15, 7

};

static inline uint64_t do_IP (const uint64_t in)

{

  uint64_t ret = 0ULL;

  int i;

  for (i = 0; i < 64; i++)

  {

    ret |= ((in >> (64 - IP[i])) & 1ULL) << (63 - i);

  }

  return ret;

}



// Final permutation

static const int IP_1[64] = {

  40, 8, 48, 16, 56, 24, 64, 32,

  39, 7, 47, 15, 55, 23, 63, 31,

  38, 6, 46, 14, 54, 22, 62, 30,

  37, 5, 45, 13, 53, 21, 61, 29,

  36, 4, 44, 12, 52, 20, 60, 28,

  35, 3, 43, 11, 51, 19, 59, 27,

  34, 2, 42, 10, 50, 18, 58, 26,

  33, 1, 41, 9, 49, 17, 57, 25

};

static inline uint64_t do_IP_1 (const uint64_t in)

{

  uint64_t ret = 0ULL;

  int i;

  for (i = 0; i < 64; i++)

  {

    ret |= ((in >> (64 - IP_1[i])) & 1ULL) << (63 - i);

  }

  return ret;

}



// Expansion

static const int E[48] = {

  32, 1, 2, 3, 4, 5,

  4, 5, 6, 7, 8, 9,

  8, 9, 10, 11, 12, 13,

  12, 13, 14, 15, 16, 17,

  16, 17, 18, 19, 20, 21,

  20, 21, 22, 23, 24, 25,

  24, 25, 26, 27, 28, 29,

  28, 29, 30, 31, 32, 1

};

static inline uint64_t do_E (const uint32_t in)

{

  uint64_t ret = 0ULL;

  int i;

  for (i = 0; i < 48; i++)

  {

    ret |= ((uint64_t)((in >> (32 - E[i])) & 1)) << (47 - i);

  }

  return ret;

}



// Permutation

static const int P[32] = {

  16, 7, 20, 21, 29, 12, 28, 17,

  1, 15, 23, 26, 5, 18, 31, 10,

  2, 8, 24, 14, 32, 27, 3, 9,

  19, 13, 30, 6, 22, 11, 4, 25

};

static inline uint32_t do_P (const uint32_t in)

{

  uint32_t ret = 0;

  int i;

  for (i = 0; i < 32; i++)

  {

    ret |= ((in >> (32 - P[i])) & 1) << (31 - i);

  }

  return ret;

}



// Permuted choice 1

/*

static const int PC1L[28] = {

  57, 49, 41, 33, 25, 17, 9,

  1, 58, 50, 42, 34, 26, 18,

  10, 2, 59, 51, 43, 35, 27,

  19, 11, 3, 60, 52, 44, 36

};

static const int PC1R[28] = {

  63, 55, 47, 39, 31, 23, 15,

  7, 62, 54, 46, 38, 30, 22,

  14, 6, 61, 53, 45, 37, 29,

  21, 13, 5, 28, 20, 12, 4

};

*/

static const int PC1[56] = {

  57, 49, 41, 33, 25, 17, 9,

  1, 58, 50, 42, 34, 26, 18,

  10, 2, 59, 51, 43, 35, 27,

  19, 11, 3, 60, 52, 44, 36,

  63, 55, 47, 39, 31, 23, 15,

  7, 62, 54, 46, 38, 30, 22,

  14, 6, 61, 53, 45, 37, 29,

  21, 13, 5, 28, 20, 12, 4

};

static inline uint64_t do_PC1 (const uint64_t in)

{

  uint64_t ret = 0ULL;

  int i;

#if DEBUG

  //fprintf(stderr, "do_PC1(%016I64x)\n", in);

#endif

  for (i = 0; i < 56; i++)

  {

    ret |= ((in >> (64 - PC1[i])) & 1ULL) << (55 - i);

#if DEBUG

    //fprintf(stderr, "\t%d: %014I64x\n", i, ret);

#endif

  }

  return ret;

/*

  int i;

  for (i = 0; i < 28; i++)

  {

    out[i] = in[PC1L[i] - 1]; 

  }

  for (i = 28; i < 56; i++)

  {

    out[i] = in[PC1R[i - 28] - 1]; 

  }

*/

}



// Permuted choice 2

static const int PC2[48] = {

#if 1

  14, 17, 11, 24, 1, 5,

  3, 28, 15, 6, 21, 10,

  23, 19, 12, 4, 26, 8,

  16, 7, 27, 20, 13, 2,

  41, 52, 31, 37, 47, 55,

  30, 40, 51, 45, 33, 48,

  44, 49, 39, 56, 34, 53,

  46, 42, 50, 36, 29, 32

#else

  14, 17, 11, 24, 1, 5, 3, 28,

  15, 6, 21, 10, 23, 19, 12, 4,

  26, 8, 16, 7, 27, 20, 13, 2,

  41, 52, 31, 37, 47, 55, 30, 40,

  51, 45, 33, 48, 44, 49, 39, 56,

  34, 53, 46, 42, 50, 36, 29, 32

#endif

};

static inline uint64_t do_PC2 (const uint64_t in)

{

  uint64_t ret = 0ULL;

  int i;

#if DEBUG

  //fprintf(stderr, "\n\tdo_PC2(%016I64x (56bits))\n", in);

#endif

  for (i = 0; i < 48; i++)

  {

    ret |= ((in >> (56 - PC2[i])) & 1ULL) << (47 - i);

#if DEBUG

    //fprintf(stderr, "\t\tret = %016I64x (48 bits) :: %d (%012I64x)\n", ret, i, ((in >> (56 - PC1[i])) & 1ULL) << (47 - i));

#endif

  }

  return ret;

}



// S boxes

static const sbox_t S1 = {

  14, 0, 4, 15, 13, 7, 1, 4, 2, 14, 15, 2, 11, 13, 8, 1,

  3, 10, 10, 6, 6, 12, 12, 11, 5, 9, 9, 5, 0, 3, 7, 8,

  4, 15, 1, 12, 14, 8, 8, 2, 13, 4, 6, 9, 2, 1, 11, 7,

  15, 5, 12, 11, 9, 3, 7, 14, 3, 10, 10, 0, 5, 6, 0, 13

};

static const sbox_t S2 = {

  15, 3, 1, 13, 8, 4, 14, 7, 6, 15, 11, 2, 3, 8, 4, 14,

  9, 12, 7, 0, 2, 1, 13, 10, 12, 6, 0, 9, 5, 11, 10, 5,

  0, 13, 14, 8, 7, 10, 11, 1, 10, 3, 4, 15, 13, 4, 1, 2,

  5, 11, 8, 6, 12, 7, 6, 12, 9, 0, 3, 5, 2, 14, 15, 9

};

static const sbox_t S3 = {

  10, 13, 0, 7, 9, 0, 14, 9, 6, 3, 3, 4, 15, 6, 5, 10,

  1, 2, 13, 8, 12, 5, 7, 14, 11, 12, 4, 11, 2, 15, 8, 1,

  13, 1, 6, 10, 4, 13, 9, 0, 8, 6, 15, 9, 3, 8, 0, 7,

  11, 4, 1, 15, 2, 14, 12, 3, 5, 11, 10, 5, 14, 2, 7, 12

};

static const sbox_t S4 = {

  7, 13, 13, 8, 14, 11, 3, 5, 0, 6, 6, 15, 9, 0, 10, 3,

  1, 4, 2, 7, 8, 2, 5, 12, 11, 1, 12, 10, 4, 14, 15, 9,

  10, 3, 6, 15, 9, 0, 0, 6, 12, 10, 11, 1, 7, 13, 13, 8,

  15, 9, 1, 4, 3, 5, 14, 11, 5, 12, 2, 7, 8, 2, 4, 14

};

static const sbox_t S5 = {

  2, 14, 12, 11, 4, 2, 1, 12, 7, 4, 10, 7, 11, 13, 6, 1,

  8, 5, 5, 0, 3, 15, 15, 10, 13, 3, 0, 9, 14, 8, 9, 6,

  4, 11, 2, 8, 1, 12, 11, 7, 10, 1, 13, 14, 7, 2, 8, 13,

  15, 6, 9, 15, 12, 0, 5, 9, 6, 10, 3, 4, 0, 5, 14, 3

};

static const sbox_t S6 = {

  12, 10, 1, 15, 10, 4, 15, 2, 9, 7, 2, 12, 6, 9, 8, 5,

  0, 6, 13, 1, 3, 13, 4, 14, 14, 0, 7, 11, 5, 3, 11, 8,

  9, 4, 14, 3, 15, 2, 5, 12, 2, 9, 8, 5, 12, 15, 3, 10,

  7, 11, 0, 14, 4, 1, 10, 7, 1, 6, 13, 0, 11, 8, 6, 13

};

static const sbox_t S7 = {

  4, 13, 11, 0, 2, 11, 14, 7, 15, 4, 0, 9, 8, 1, 13, 10,

  3, 14, 12, 3, 9, 5, 7, 12, 5, 2, 10, 15, 6, 8, 1, 6,

  1, 6, 4, 11, 11, 13, 13, 8, 12, 1, 3, 4, 7, 10, 14, 7,

  10, 9, 15, 5, 6, 0, 8, 15, 0, 14, 5, 2, 9, 3, 2, 12

};

static const sbox_t S8 = {

  13, 1, 2, 15, 8, 13, 4, 8, 6, 10, 15, 3, 11, 7, 1, 4,

  10, 12, 9, 5, 3, 6, 14, 11, 5, 0, 0, 14, 12, 9, 7, 2,

  7, 2, 11, 1, 4, 14, 1, 7, 9, 4, 12, 10, 14, 8, 2, 13,

  0, 15, 6, 12, 10, 9, 13, 0, 15, 3, 3, 5, 5, 6, 8, 11

};



// Feistel function

static inline uint32_t do_F (const uint32_t block, const uint64_t key)

{

  uint64_t temp;

  uint32_t temp_out;



  temp = do_E(block) ^ key;



  temp_out = S1[(temp >> 42) & 0x3F] << 28;

  temp_out |= S2[(temp >> 36) & 0x3F] << 24;

  temp_out |= S3[(temp >> 30) & 0x3F] << 20;

  temp_out |= S4[(temp >> 24) & 0x3F] << 16;

  temp_out |= S5[(temp >> 18) & 0x3F] << 12;

  temp_out |= S6[(temp >> 12) & 0x3F] << 8;

  temp_out |= S7[(temp >> 6) & 0x3F] << 4;

  temp_out |= S8[temp & 0x3F];



#if DEBUG

  fprintf(stderr, "f(%08x, %012I64x) = %08x\n", block, key, do_P(temp_out));

#endif



  return do_P(temp_out);

}



static const int leftRotations[16] = {

  1,

  1,

  2,

  2,

  2,

  2,

  2,

  2,

  1,

  2,

  2,

  2,

  2,

  2,

  2,

  1

};



// The whole thing together

static inline uint64_t do_DES (const uint64_t in, const uint64_t key)

{

  uint32_t left;

  uint32_t right;

  uint32_t lr;

  uint64_t temp;

  uint64_t afterkey;

  uint64_t subk;

  int i;



  temp = do_IP(in);

  left = (uint32_t)(temp >> 32);

  right = (uint32_t)(temp & 0xFFFFFFFF);



  afterkey = do_PC1(key);



#if DEBUG

  fprintf(stderr, "left: %08x right: %08x afterkey: %014I64x\n", left, right, afterkey);

#endif



  for (i = 0; i < 16; i++)

  {

    afterkey = do_doubleLeftRotate(leftRotations[i], afterkey);

#if DEBUG

    fprintf(stderr, "R%d: afterkeyRotated: %014I64x ", i, afterkey);

#endif

    subk = do_PC2(afterkey);



    if (i != 0)

    {

      lr = left;

      left = right;

      right = lr;

    }



    left ^= do_F(right, subk);

  }



  temp = ((uint64_t)left << 32) | (uint64_t)right;



  return do_IP_1(temp);

}



static inline uint64_t do_DES_incomplete (const uint64_t in, const uint64_t key)

{

  uint32_t left;

  uint32_t right;

  uint32_t lr;

  uint64_t temp;

  uint64_t afterkey;

  uint64_t subk;

  int i;



  left = (uint32_t)(in >> 32);

  right = (uint32_t)(in & 0xFFFFFFFF);



  afterkey = do_PC1(key);



#if DEBUG

  fprintf(stderr, "left: %08x right: %08x afterkey: %014I64x\n", left, right, afterkey);

#endif



  for (i = 0; i < 16; i++)

  {

    afterkey = do_doubleLeftRotate(leftRotations[i], afterkey);

#if DEBUG

    fprintf(stderr, "R%d: afterkeyRotated: %014I64x ", i, afterkey);

#endif

    subk = do_PC2(afterkey);



    if (i != 0)

    {

      lr = left;

      left = right;

      right = lr;

    }



    left ^= do_F(right, subk);

  }



  temp = ((uint64_t)left << 32) | (uint64_t)right;



  return temp;

}



static inline uint64_t do_DES_1 (const uint64_t in, const uint64_t key)

{

  uint32_t left;

  uint32_t right;

  uint32_t lr;

  uint64_t temp;

  uint64_t afterkey;

  uint64_t subk[16];

  int i;



  afterkey = do_PC1(key);

  for (i = 0; i < 16; i++)

  {

    afterkey = do_doubleLeftRotate(leftRotations[i], afterkey);

    subk[15 - i] = do_PC2(afterkey);

  }  

  

  temp = do_IP(in);

  left = (uint32_t)(temp >> 32);

  right = (uint32_t)(temp & 0xFFFFFFFF);

  for (i = 0; i < 16; i++)

  {

    if (i != 0)

    {

      lr = left;

      left = right;

      right = lr;

    }



    left ^= do_F(right, subk[i]);

  }

  

  temp = ((uint64_t)left << 32) | (uint64_t)right;



  return do_IP_1(temp);

}



static inline uint64_t do_DES_1_incomplete (const uint64_t in, const uint64_t key)

{

  uint32_t left;

  uint32_t right;

  uint32_t lr;

  uint64_t temp;

  uint64_t afterkey;

  uint64_t subk[16];

  int i;



  afterkey = do_PC1(key);

  for (i = 0; i < 16; i++)

  {

    afterkey = do_doubleLeftRotate(leftRotations[i], afterkey);

    subk[15 - i] = do_PC2(afterkey);

  }  

  

  left = (uint32_t)(in >> 32);

  right = (uint32_t)(in & 0xFFFFFFFF);

  for (i = 0; i < 16; i++)

  {

    if (i != 0)

    {

      lr = left;

      left = right;

      right = lr;

    }



    left ^= do_F(right, subk[i]);

  }

  

  temp = ((uint64_t)left << 32) | (uint64_t)right;



  return temp;

}



static inline uint64_t extractPartialMesage (const char * in)

{

  int i;

  uint64_t ret = 0ULL;

  char c;

  for (i = 0; i < 16; i++)

  {

    c = in[i];

    if (c <= '9')

    {

      ret |= (uint64_t)(c - '0') << (60 - 4 * i);

    }

    else if (c <= 'F')

    {

      ret |= (uint64_t)(c + 10 - 'A') << (60 - 4 * i);

    }

    else

    {

      ret |= (uint64_t)(c + 10 - 'a') << (60 - 4 * i);

    }

  }

  return ret;

}



/*

 * MinGW does not provide getline.

 * This is my own implementation, behaving like the standard says, except with the following:

 * - When a newline is found, only '\n' is written at the end of the returned string, even if

 *   a Windows-like newline ("\r\n") is found.

 * - Carriage return characters ('\r') are only supported if they come just before line feed ones ('\n'),

 *   ie: only in Windows-like newlines. Otherwise, they are silenty omitted.

 */

#define GETLINE_INITIAL_SIZE 32

static inline ssize_t getline (char ** lineptr, size_t * n, FILE * stream)

{

  ssize_t ret;

  int c;

  int finish_loop;



  if ((lineptr == NULL) || (n == NULL) || (stream == NULL))

  {

    ret = -1;

    errno = EINVAL;

  }

  else

  {

    if (*lineptr == NULL)

    {

      *n = GETLINE_INITIAL_SIZE;

      *lineptr = (char *)malloc(GETLINE_INITIAL_SIZE);

    }

    else if (*n == 0)

    {

      *n = GETLINE_INITIAL_SIZE;

      *lineptr = (char *)realloc(*lineptr, GETLINE_INITIAL_SIZE);

    }



    ret = 0;



    finish_loop = 0;

    while (!finish_loop && (c = fgetc(stream)) != EOF)

    {

      if (c == '\n')

      {

        finish_loop = 1;

      }



      if (c != '\r')

      {

        /* write char */

        

        if (ret == (ssize_t)*n)

        {

          *n *= 2;

          *lineptr = (char *)realloc(*lineptr, *n);

        }



        (*lineptr)[ret] = (char)c;

        ret++;

      }

    }



    if (ret == 0)

    {

      /* EOF at the start of the reading */

      ret = -1;

    }

    else

    {

      if (ret == (ssize_t)*n)

      {

        (*n)++;

        *lineptr = (char *)realloc(*lineptr, *n);

      }

      (*lineptr)[ret] = '\0';

    }

  }



  return ret;

}



int main (int argc, char ** argv)

{

  char * line;

  size_t size;

  FILE * input_data_file;

  char * startMsgs[1000];

  int i;

  int j;

  char * p;

  uint64_t message;

  uint64_t ip;

  uint64_t out;

  uint64_t key;

  uint64_t max_k;

  unsigned char ka;

  unsigned char kb;

  unsigned char kc;

  unsigned char kd;

  unsigned char * aes_encoded;

  unsigned char * aes_decoded;

  int aes_encoded_len;



#if 0

  printf("%016I64x\n", do_IP(extractPartialMesage("FFFFFFFF00000000")));

  printf("%016I64x\n", do_IP(extractPartialMesage("4B65793D00000000"))); return 0;

#endif



  // save input data, just for review

  input_data_file = fopen("input_data.txt", "w");



  line = NULL;

  size = 0;



  init_aes();



#if 1

  while (getline(&line, &size, stdin) > 1000 /* just to say something */)

  {

#if DEBUG

    fprintf(stderr, "New line...\n");

    fflush(stderr);

#endif

    fprintf(input_data_file, "%s", line);



    p = line;

    for (i = 0; i < 1000; i++)

    {

      while ((*p != ':') && (*p != '~'))

      {

        p++;

      }

      *p = '\0';

      p++;

      startMsgs[i] = p;

    }

    while ((*p != '\n') && (*p != '\r') && (*p != '\0'))

    {

      p++;

    }

    *p = '\0';



    /* Start the party! */



    aes_encoded_len = strlen(line) / 2;

    aes_encoded = (unsigned char *)malloc(strlen(line) * sizeof(unsigned char) / 2);

    aes_decoded = (unsigned char *)malloc(strlen(line) * sizeof(unsigned char) / 2);



    /*

    fprintf(stderr, "aes_len = %d (%p) (%p)\n", aes_encoded_len, aes_encoded, aes_decoded);

    fflush(stderr);

    */



    for (i = 0; line[i] != '\0'; i++)

    {

      int v;

      if (line[i] <= '9')

      {

        v = line[i] - '0';

      }

      else if (line[i] <= 'F')

      {

        v = line[i] + 10 - 'A';

      }

      else

      {

        v = line[i] + 10 - 'a';

      }



      if (i % 2 == 0)

      {

        aes_encoded[i / 2] = (v << 4) & 0xF0;

      }

      else

      {

        aes_encoded[i / 2] |= v & 0xF;

      }

    }





#if 0

    {

#include "keys_for_c.txt"

	unsigned char key[KEY_128] = "\x69\x64\x6F\x6F\x37\x32\x72\x6F\x69\x37\x6D\x36\x75\x39\x76\x73";

	unsigned char ptext[16] = "\x07\xbd\x9c\x28\x26\xb9\x1e\x90\x6c\xd0\x08\xcc\xbb\xa2\x94\x87";

	unsigned char ctext[16];

	unsigned char decptext[16];

	aes_ctx_t *ctx;



        ctx = aes_alloc_ctx("jevot86fc268s4oo", KEY_128);

  for (i = 0; i < 96; i+=32)

      {



        char asdf[16];

        for (j = 0; j < 16; j++) asdf[j] = ((char *)/* "\x07\xbd\x9c\x28\x26\xb9\x1e\x90\x6c\xd0\x08\xcc\xbb\xa2\x94\x87*/ "\x5f\xe3\x38\x4d\xa9\x9c\x3f\x08\xb0\xeb\x7c\xe9\xfc\x13\x2a\xdd\x76\xca\xa6\x82\x96\xdd\x34\xfb\xda\x47\x4c\x3c\x08\xc9\xc7\x87")[i / 32 + j];



        	aes_decrypt(ctx, asdf, ctext);

  for (j = 0; j < 16; j++)

  {

    fprintf(stderr, "%02x", ctext[j]);

  }

  fprintf(stderr, "\n");





      }



        aes_free_ctx(ctx);

    }

#endif





#if 1 // descrifrado de los 1000 msgs

    {

      int this_msg;

      for (this_msg = 0; this_msg < 1000; this_msg++)

      {



        /*

        fprintf(stderr, "Procesando msg %d\n", this_msg);

        fflush(stderr);

        */

    message = extractPartialMesage(startMsgs[this_msg]);

    ip = do_IP(message);

    ka = kb = kc = kd = '0';

    key = ((uint64_t)ka << 56) | ((uint64_t)kb << 48) | ((uint64_t)kc << 40) | ((uint64_t)kd << 32) | 0x30303030ULL;

    max_k = ((uint64_t)('z' + 1) << 56) | ((uint64_t)kb << 48) | ((uint64_t)kc << 40) | ((uint64_t)kd << 32) | 0x30303030ULL;

    while (key != max_k /*; key += 0x100000000ULL*/)

    {

      if ((key & 0x0101010101010101ULL) == 0) // don't repeat keys that only differ in parity bits

      {

        //if ((key & 0xffffffffffffULL) == 0x30303030ULL)

        //{

        //  fprintf(stderr, "Key %016I64x\n", key);

        //}

        //key = extractPartialMesage("C3CCF1EDB0000000"); // 6432746430303030

        out = do_DES_1_incomplete(ip, key);



        if ((out & 0x0f0f0f0f0f0f0f0fULL) == 0x070c0a0f000e0d01ULL) // output is "Key=...."

        {

          // DES key found!



          //fprintf(stderr, "DES key found %016I64x msg %d\n", key, this_msg);

          //fflush(stderr);



          //fprintf(stderr, "Msg: %3d: Found key %016I64x: ", this_msg, key);

          //for (i = 0; startMsgs[this_msg][i] != '\0'; i += 16)

          //{

          //  fprintf(stderr, "%016I64x", do_DES_1(extractPartialMesage(startMsgs[this_msg] + i), key));

          //}

          //fprintf(stderr, "\n");

          break;

        }

      }



      kd++;

      if (kd == '9' + 1)

      {

        kd = '`';

      }

      if (kd > 'z')

      {

        kd = '0';

        kc++;

        if (kc == '9' + 1)

        {

          kc = '`';

        }

        if (kc > 'z')

        {

          kc = '0';

          kb++;

          if (kb == '9' + 1)

          {

            kb = '`';

          }

          if (kb > 'z')

          {

            kb = '0';

            ka++;

            if (ka == '9')

            {

              ka = '`';

            }

          }

        }

      }

      key = ((uint64_t)ka << 56) | ((uint64_t)kb << 48) | ((uint64_t)kc << 40) | ((uint64_t)kd << 32) | 0x30303030ULL;

    } // searching all the possible DES keys



    if (key != max_k)

    {

      unsigned char * game_msg_decoded = (unsigned char *)malloc(strlen(startMsgs[this_msg]) * sizeof(unsigned char));

      aes_ctx_t *ctx;

      int is_good;

      

      int pos;



      /*

      fprintf(stderr, "game_msg_decoded = %p (len = %d)\n", game_msg_decoded, strlen(startMsgs[this_msg]));

      fflush(stderr);

      */

      pos = 0;

      for (i = 0; startMsgs[this_msg][i] != '\0'; i += 16)

      {

        uint64_t decoded_chunk = do_DES_1(extractPartialMesage(startMsgs[this_msg] + i), key);

        game_msg_decoded[pos + 0] = (unsigned char)((decoded_chunk >> 56) & 0xFF);

        game_msg_decoded[pos + 1] = (unsigned char)((decoded_chunk >> 48) & 0xFF);

        game_msg_decoded[pos + 2] = (unsigned char)((decoded_chunk >> 40) & 0xFF);

        game_msg_decoded[pos + 3] = (unsigned char)((decoded_chunk >> 32) & 0xFF);

        game_msg_decoded[pos + 4] = (unsigned char)((decoded_chunk >> 24) & 0xFF);

        game_msg_decoded[pos + 5] = (unsigned char)((decoded_chunk >> 16) & 0xFF);

        game_msg_decoded[pos + 6] = (unsigned char)((decoded_chunk >> 8) & 0xFF);

        game_msg_decoded[pos + 7] = (unsigned char)(decoded_chunk & 0xFF);

        pos += 8;

      }



      /*

      fprintf(stderr, "Posible AES key: ");

      for (i = 0; i < 16; i++)

      {

        fprintf(stderr, "%c", game_msg_decoded[i + 4]);

      }

      fprintf(stderr, "\n");

      fflush(stderr);

      */



      // Try to decode with AES



      // AES key

      ctx = aes_alloc_ctx(game_msg_decoded + 4, KEY_128);



      /*

      fprintf(stderr, "ctx = %p\n", ctx);

      fflush(stderr);

      */



      /*

      fprintf(stderr, "Aes encoded: ");

      for (i = 0; i < 16; i++)

      {

        fprintf(stderr, "%02x", aes_encoded[i]);

      }

      fprintf(stderr, "\n");

      */



      aes_decrypt(ctx, aes_encoded, aes_decoded);



      /*

      fprintf(stderr, "decripted\n", ctx);

      fflush(stderr);

      */



      /*

      fprintf(stderr, "aes_decoded: ");

      for (i = 0; i < 16; i++)

      {

        fprintf(stderr, "%c(%d) ", aes_decoded[i], aes_decoded[i]);

      }

      fprintf(stderr, "\n");

      */



      for (i = 0; i < 16; i++)

      {

        if ((aes_decoded[i] < ' ') || (aes_decoded[i] > 127))

        {

          break;

        }

      }



      if (aes_encoded_len <= 16)

      {

        is_good = 1;

        for (j = i; j < 16; j++)

        {

          if (aes_decoded[j] != 16 - i)

          {

            is_good = 0;

            break;

          }

        }

      }

      else

      {

        is_good = (i == 16);

      }



      //fprintf(stderr, "is-good: %d\n", is_good);

      //fflush(stderr);



      if (is_good)

      {

        // Good AES key found



        for (i = 16; i < aes_encoded_len; i+= 16)

        {

          aes_decrypt(ctx, aes_encoded + i, aes_decoded + i);

        }



        for (i = 0; i < aes_encoded_len; i++)

        {

          if ((aes_decoded[i] >= ' ') && (aes_decoded[i] <= 127))

          {

            printf("%c", aes_decoded[i]);

          }

          else

          {

            break;

          }

        }

        printf("\n");

        fflush(stdout);

        

        aes_free_ctx(ctx);

        free(game_msg_decoded);



        break; // next 1000 msgs

      }





      aes_free_ctx(ctx);

      free(game_msg_decoded);

    }

  //  else

   // {

    //  // DES key NOT found... what to do here?

     // fprintf(stderr, "Msg: %3d: ####### ******** No key found!!!\n", this_msg);

   // }



    //fprintf(stderr, "\n\n\n");





      } // for all 1000 msgs

    }

#endif



    free(aes_encoded);

    free(aes_decoded);



  } // while there are lines in the input

#endif



#if 0

  // http://www.unsw.adfa.edu.au/~lpb/src/DEScalc/DEScalc.html

#endif



  free(line);



  fclose(input_data_file);



  return 0;

}