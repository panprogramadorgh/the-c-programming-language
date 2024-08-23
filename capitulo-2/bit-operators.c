#include <stdio.h>
#include <ctype.h>

#define MAXLN 1024

/* Allows to get a line of
text from the standard input.
Retorna la longitud de la linea
de entrada sin contar el caracter
nulo. */
int gline(char line[]);

/* Allows to parse a binary number
inside a literal chain to a integer. */
unsigned int bintoint(const unsigned char bin[]);

/* Allows to grab from `x` a frame of `n` bits
starting from `p` position (assuming that the
most weight bit is the position 0) and ending
in the bit with position `p - n + 1'` */
unsigned int getbits(unsigned int x, unsigned char p, unsigned char n);

/* ### C binary operatods test. */
int main()
{
  // char line[MAXLN];
  char b1[] = "111000", b2[] = "101101";
  int n1, n2;

  // gline(line);
  n1 = bintoint(b1);
  n2 = bintoint(b2);

  printf("N. Format\tNumber\n");
  printf("Bin\t%s\t%s\n", b1, b2);
  printf("Dec\t%d\t%d\n", n1, n2);

  putchar('\n');

  printf("Op\tValor\n");
  printf("OR\t%d\n", n1 | n2);
  printf("AND\t%d\n", n1 & n2);
  printf("XOR\t%d\n", n1 ^ n2);
  printf("C. izq (1 pos)\t%d\n", n1 << 1);
  printf("C. der (1 pos)\t%d\n", n1 >> 1);
  printf("Com. a uno\t%d\n", ~n1);

  printf("%d\n", getbits(n1, 4, 2));

  return 0;
}

int gline(char line[])
{
  int i, c;

  for (i = 0; i < MAXLN - 1 && (c = getchar()) != '\n' && c != EOF; i++)
    line[i] = c;
  line[i] = '\0';

  return i;
}

unsigned int bintoint(const unsigned char bin[])
{
  int i, n, c, d;

  for (i = n = 0; (c = bin[i]) == '0' || c == '1'; i++)
  {
    d = bin[i] - '0';
    n = n * 2 + d;
  }

  return n;
}

unsigned int getbits(unsigned int x, unsigned char p, unsigned char n)
{
  return (x >> (p - n + 1) & ~(~0 << n));
}