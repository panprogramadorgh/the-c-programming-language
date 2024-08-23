#include <stdio.h>
#include <ctype.h>

#define INTS 32

/* Allows to convert a string constant
`bin` with character representation of
a binary number into a real integer number. */
unsigned int bintoint(const char bin[]);

/* Grabs the last `n` bits of `y` and
sets those bits in `x` starting in `p`
and ending in `p - n + 1`. */
unsigned int setbits(unsigned int x, unsigned char p, unsigned char n, unsigned int y);

int main()
{
  char b1[] = "101010"; // 100100
  char b2[] = "1010";
  int n;

  n = setbits(bintoint(b1), 3, 3, bintoint(b2));

  printf("%u\n", n);

  return 0;
}

unsigned int bintoint(const char bin[])
{
  int i, c, n;

  for (i = n = 0; (c = bin[i]) != '\0' && isdigit(c) && c <= '1'; ++i)
    n = n * 2 + (c - '0');

  return n;
}

unsigned int setbits(unsigned int x, unsigned char p, unsigned char n, unsigned int y)
{
  unsigned int ms1 = ~0U << (p + 1);
  unsigned int s1 = ms1 & x;

  unsigned int ms2 = ~(~0U << n);
  unsigned int s2 = (ms2 & y) << (p - n + 1);

  unsigned ms3 = ~(~0U << (p - n + 1));
  unsigned s3 = ms3 & x;

  return s1 | s2 | s3;
}