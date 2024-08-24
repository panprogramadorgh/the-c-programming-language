#include <stdio.h>

/* Allows to parse a binary based
number represented inside the
character array `bin` to a integer
number. */
unsigned int bintoint(const char bin[]);

/* Allows to invert a sequence of
`n` bits inside `x` starting from `p`
and ending at `p - n + 1`. Important
to say that positions always are
reciprocal to its bit weight. */
unsigned int invert(unsigned int x, unsigned char p, unsigned char n);

int main()
{
  char b[] = "101010";
  unsigned int n;

  n = bintoint(b);
  n = invert(n, 3, 3);
  printf("%u\n", n);

  return 0;
}

unsigned int bintoint(const char bin[])
{
  int i, c;
  unsigned int n;

  for (i = n = 0; (c = bin[i]) != '\0'; i++)
    n = n * 2 + c - '0';

  return n;
}

unsigned int invert(unsigned int x, unsigned char p, unsigned char n)
{
  unsigned int ms1 = ~0U << (p + 1);
  unsigned int s1 = x & ms1;

  unsigned int ms3 = ~(~0U << (p - n + 1));
  unsigned int s3 = x & ms3;

  unsigned int ms2 = ~(ms1 | ms3);
  unsigned int s2 = ~x & ms2;

  return s1 | s2 | s3; // no local var return
}