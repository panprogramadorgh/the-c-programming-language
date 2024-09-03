#include <stdio.h>
#include <limits.h>
#include <string.h>

/* Determines the maxiumum length for literal strings throughout the programm. */
#define MAX 1024

/* Converts a interger number into a literal string. */
void itoa(int n, char result[]);

/* Reverses a literal string. */
void reverse(char s1[]);

int main()
{
  char digit[MAX];

  itoa(-153, digit);

  printf("%s\n", digit);

  return 0;
}

void itoa(int n, char result[])
{
  int digit, sign;
  int i;

  sign = 1;
  if (n < 0)
  {
    sign = -1;
    n *= -1;
  }

  i = 0;
  do
  {
    digit = n % 10 + '0';
    result[i++] = digit;
  } while ((n /= 10) > 0);

  if (sign < 0)
    result[i++] = '-';

  reverse(result);

  result[i] = '\0';
}

void reverse(char s[])
{
  int c;
  int i, j;

  for (i = 0, strlen(s) - 1; i < j; i++, j--)
    c = s[i], s[i] = s[j], s[j] = c;
}