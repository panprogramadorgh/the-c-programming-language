#include <stdio.h>

/* Determines the maximum length for literal strings through the entire programm. */
#define MAX 1024 // 1.0 KiB

/* Converts a integer into its correspondig character array representation respecting the minimum width. The function asumes that `s` has `MAX` length. */
void itoa(int n, char s[], int w);

/* Reverses de the literal string `s`. */
void reverse(char s[]);

int main()
{
  char digit[MAX];
  itoa(~0U >> 1, digit, 1U << 4);

  printf("%s\n", digit);

  return 0;
}

void itoa(int n, char s[], int w)
{
  int rspaces;
  int digit, sign;
  int i, j;

  sign = 1;
  if (n < 0)
    sign = -1;
  i = 0;
  do
  {
    digit = n % 10 * sign + '0';
    s[i++] = digit;
  } while (i < MAX - ((sign == -1 ? 1 : 0) + 1) && (n /= 10) != 0);
  if (sign == -1)
    s[i++] = '-';

  for (rspaces = w - i - 1; i < MAX - 1 && rspaces >= 0; rspaces--, i++)
    s[i] = ' ';
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