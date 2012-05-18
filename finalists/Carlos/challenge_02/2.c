#include <stdio.h>

typedef unsigned long long int uint64_t;

int main (void)
{
  FILE * f;
  uint64_t n;
  uint64_t x;
  uint64_t y;
  int test_cases;
  int i;
  int m;
  int bit;
  
  // save input data, just for testing
  f = fopen("input_data.txt", "w");

  scanf("%d", &test_cases);
  fprintf(f, "%d\n", test_cases);

  // for each test
  for (i = 0; i < test_cases; i++)
  {
    scanf("%I64u", &n);
    fprintf(f, "%I64u\n", n);

    if (n == 0)
    {
      // no hazelnuts if n == 0
      m = 0;
    }
    else
    {
      // find the highest bit '1' in n (we know that there is at least one '1' in n)
      for (bit = 63; bit >= 0; bit--)
      {
        if (((1ULL << bit) & n) != 0)
        {
          break;
        }
      }

      // set x to 2**k - 1, to have the most ones possible; with k as big as possible (k is bit)
      x = (1ULL << bit) - 1ULL; // 'bit' bits set to '1' 
      y = n - x;

      m = bit; // we've got 'bit' bits already

      // and count the bits of y
      while (y != 0)
      {
        if ((y & 1) != 0)
        {
          m++;
        }

        y >>= 1;
      }
    }

    printf("Case #%d: %d\n", i + 1, m);
  }

  fclose(f);
  return 0;
}
