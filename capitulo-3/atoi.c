#include <stdio.h>
#include <ctype.h>

/* Allows to parse a char array representation of a deecimal number into a real number. */
int atoi(const char s[]);

/* Segunda version de programa atoi. Conversion de cadenas literales con representaciones numericas a numeros reales. */
int main()
{
  const char number[] = "    -1250  ";
  int n;

  n = atoi(number);

  printf("%d\n", n);

  return 0;
}

int atoi(const char str[])
{
  int n, s, i;

  n = 0;
  s = 1;

  for (i = 0; isspace(str[i]); i++)
    ;
  if ((str[i] == '+') || (str[i] == '-'))
    s = (str[i++] == '+') ? 1 : -1;
  for (; isdigit(str[i]); i++)
    n = n * 10 + (str[i] - '0');

  return n * s;
}