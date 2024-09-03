#include <stdio.h>

enum Conf
{
  /* Determines the maxiumum length for literal strings throughout the programm. */
  MAXS = 1024,
  /* Determines the biggest numerical format for itob to work. */
  MAXB = 16
};

/* Creates a character array representation of `n` in `b` numerical format and saves the result in `s`. */
void itob(unsigned n, char s[], unsigned b);

/* Reverses a literal string. */
void reverse(char s1[]);

/* Programa para cambiar la base numerica de un numero guardando el resultado en forma de representacion literal. */
int main()
{
  char digit[MAXS];

  itob(-127, digit, 16);
  printf("%s\n", digit);

  return 0;
}

void itob(unsigned n, char s[], unsigned b)
{
  char digits[MAXB + 1];
  int digit, sign;
  int i, c;

  if (n < 2)
    return;

  sign = 1;
  if (n < 0)
    sign = -1;

  for (i = 0, c = '0'; i < MAXB && i <= 9; i++, c++)
    digits[i] = c;
  for (c = 'a'; i < MAXB && c <= 'z'; c++, i++)
    digits[i] = c;
  digits[i] = '\0';

  i = 0;
  do
  {
    digit = digits[n % b];
    s[i++] = digit;
  } while ((n /= b) > 0);

  s[i] = '\0';

  reverse(s);
}

void reverse(char s[])
{
  int c;
  int i, j;

  for (j = 0; s[j] != '\0'; j++)
    ;
  for (i = 0, j--; i < j; i++, j--)
    c = s[i], s[i] = s[j], s[j] = c;
}