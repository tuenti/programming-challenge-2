/*  Tuenti Contest 2
    Challenge 2

    Compile with:
    gcc -o t2 -O3 t2.c
*/

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

/* Calculate Hamming Weight using the efficient method for machines with fast multiplication from:
   http://en.wikipedia.org/wiki/Hamming_weight
*/

const uint64_t m1  = 0x5555555555555555; /* binary: 0101... */
const uint64_t m2  = 0x3333333333333333; /* binary: 00110011.. */
const uint64_t m4  = 0x0f0f0f0f0f0f0f0f; /* binary:  4 zeros,  4 ones ... */
const uint64_t m8  = 0x00ff00ff00ff00ff; /* binary:  8 zeros,  8 ones ... */
const uint64_t m16 = 0x0000ffff0000ffff; /* binary: 16 zeros, 16 ones ... */
const uint64_t m32 = 0x00000000ffffffff; /* binary: 32 zeros, 32 ones */
const uint64_t hff = 0xffffffffffffffff; /* binary: all ones */
const uint64_t h01 = 0x0101010101010101; /* the sum of 256 to the power of 0,1,2,3... */
 
/* Count the numbers of 1 bits in a 64 bit integer */
int count_ones_fast(uint64_t x) {
    x -= (x >> 1) & m1;             /* put count of each 2 bits into those 2 bits */
    x = (x & m2) + ((x >> 2) & m2); /* put count of each 4 bits into those 4 bits */
    x = (x + (x >> 4)) & m4;        /* put count of each 8 bits into those 8 bits */
    return (x * h01)>>56;  /* returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ... */
}

/* Count the numbers of 1 bits in a 64 bit integer */
int count_ones_normal(uint64_t n) {
    int ones = 0;
    uint64_t i;

    for (i = 0; i < (sizeof(n) * 8); i++, n >>= 1) {
        if (n & 1)
            ones++;
    }
        
    return ones;
}


int main(void) {
    uint64_t count, N, half;
    uint64_t i, j;
    uint64_t max_hazelnuts, ones;

    if (fscanf(stdin, "%" PRIu64, &count) != 1)
        return 1;

    for(i = 0; i < count; i++) {
        if (fscanf(stdin, "%" PRIu64, &N) != 1)
            continue;
        
        max_hazelnuts = 0;
        
        half = N >> 1;

        if (N == 1) {
            half = 1;
        }
    
        for(j = 1; j <= half; j++) {
            ones = count_ones_fast(j);
            ones += count_ones_fast(N - j);

            if (ones > max_hazelnuts)
                max_hazelnuts = ones;
        }

        printf("Case #%" PRIu64 ": %" PRIu64 "\n", i + 1, max_hazelnuts);   
    }    

    return 0;
}

