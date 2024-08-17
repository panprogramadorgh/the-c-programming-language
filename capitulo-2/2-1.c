#include <stdio.h>

#define CHAR_BITS 8

#define SHORT_BITS 16

#define INT_BITS 32

#define LONG_BITS 64

/* Funcion de exponenciacion
de numeros naturales. */
unsigned long long int powto(unsigned long long int m, unsigned short int n);

/* Imprime el rango de valores sin signo. */
void print_unsigned_range(int unsigned long long to);

/* Imprime el rango de valores con signo. */
void print_signed_range(int signed long long from, int signed long long to);

int main()
{
  /* Unsigned max values for each type. */
  unsigned char max_unsigned_char = powto(2, CHAR_BITS) - 1;
  unsigned short int max_unsigned_short = powto(2, SHORT_BITS) - 1;
  unsigned int max_unsigned_int = powto(2, INT_BITS) - 1;
  unsigned long int max_unsigned_long = powto(2, LONG_BITS) - 1;

  /* Signed min and max values for each type. */
  signed char min_signed_char = -powto(2, CHAR_BITS - 1);
  signed char max_signed_char = powto(2, CHAR_BITS - 1) - 1;
  signed short int min_signed_short = -powto(2, SHORT_BITS - 1);
  signed short int max_signed_short = powto(2, SHORT_BITS - 1) - 1;
  signed int min_signed_int = -powto(2, INT_BITS - 1);
  signed int max_signed_int = powto(2, INT_BITS - 1) - 1;
  signed long int min_signed_long = -powto(2, LONG_BITS - 1);
  signed long int max_signed_long = powto(2, LONG_BITS - 1) - 1;

  print_signed_range(min_signed_char, max_signed_char);

  return 0;
}

unsigned long long int powto(unsigned long long int m, unsigned short int n)
{
  unsigned long long int p = 1U;
  unsigned short int i;

  for (i = 0; i < n; ++i)
    p *= m;

  return p;
}

void print_unsigned_range(int unsigned long long to)
{
  unsigned long long int i;
  unsigned char min_unsigned = 0;

  for (i = min_unsigned; i <= to; ++i)
    printf("%llu\t", i);
  putchar('\n');
}

void print_signed_range(signed long long int from, int signed long long to)
{
  signed long long i;

  for (i = from; i <= to; ++i)
    printf("%lld\t", i);
  putchar('\n');
}