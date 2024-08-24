#include <stdio.h>
#include <limits.h>

#define INTS __WINT_WIDTH__

/* Allows to convert a decimal-based
number represented inside the character
array `bin` to a real integer. */
unsigned int bintoint(const char bin[]);

/* Allows to rotatet `n` positions
the unsigned integer `x`. */
unsigned int rightrot(unsigned int x, unsigned char n);

/* Returns the position of the first
bit with the value 1 in `x`. Important
to know that positions are reciprocal
to its bit weight. */
char firstbit(unsigned int x);

int main()
{
  char b[] = "10101010"; // 00010101 -> 01010101 -> 85
  unsigned int n;

  n = bintoint(b);
  n = rightrot(n, 3);

  printf("%u\n", n);

  return 0;
}

unsigned int bintoint(const char bin[])
{
  unsigned char i, c, offset;
  unsigned int n;

  offset = '0';

  for (i = n = 0; (c = bin[i]) != '\0' && (c == '0' || c == '1'); i++)
    n = n * 2 + c - offset;

  return n;
}

unsigned int rightrot(unsigned int x, unsigned char n)
{
  char fbit = firstbit(x);
  if (fbit == -1)
    return 0;

  unsigned int s1 = x >> n;

  unsigned ms2 = ~(~0U << n);
  unsigned s2 = (x & ms2) << (fbit - n + 1);

  return s1 | s2;
}

char firstbit(unsigned int x)
{
  unsigned int m, n;
  char pos, i;

  m = ~(~0U >> 1);

  pos = -1;

  for (i = INTS - 1; pos == -1 && i >= 0; i--)
  {
    n = x & m;
    if (n != 0)
      pos = i;

    m = m >> 1;
  }

  return pos;
}