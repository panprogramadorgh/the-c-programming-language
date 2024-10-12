#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLN 1024
#define MAXBUF 1024

/* Allows to get a line of text from stdinput .*/
int getln(char *line, int max);

/* Allows to parse a literal string representation of a interger to a real one. */
int atoi(char *s);

/* Allows t parse a literal string representation of a floating point number to a real one. */
double atof(char *s);

/* Converts a integer number into its literal string representation.  */
void itoa(int n, char *dgt);

int main()
{
  char digit[MAXLN];
  itoa(-123, digit);
  printf("%s\n", digit);

  return 0;
}

/* --------- */
static char buffer[MAXBUF];
static char *buffpos = buffer;

int getch(void)
{
  if (buffpos - buffer > 0)
    return *--buffpos;
  return getchar();
}

void ungetch(int c)
{
  if (buffpos - buffer < MAXBUF)
    *buffpos++ = c;
}

void clrbuff(void)
{
  buffpos = buffer;
}
/* --------- */

int getln(char *line, int max)
{
  char *ch = line;
  int c;
  clrbuff(); // Cleans the input buffer.
  while ((ch - line) < max - 1 && (c = getch()) && c != '\n')
    *ch++ = c;
  *ch = '\0';
  return ch - line;
}

int atoi(char *s)
{
  int r = 0, sign;

  while (isspace(*s))
    s++;
  sign = *s == '-' ? -1 : 1;
  if (*s == '+' || *s == '-')
    s++;

  while (isdigit(*s))
  {
    r = r * 10 + (*s - '0');
    s++;
  }

  return r * sign;
}

double atof(char *s)
{
  int ipart, sign;
  double fpart;

  while (isspace(*s))
    s++;
  sign = *s == '-' ? -1 : 1;
  if (*s == '+' || *s == '-')
    s++;
  for (ipart = 0; isdigit(*s); s++)
    ipart = ipart * 10 + (*s - '0');
  if (*s == '.')
    s++;
  int fpartlen;
  for (fpart = fpartlen = 0; isdigit(*s); s++, fpartlen++)
    fpart = fpart * 10 + (*s - '0');
  fpart /= pow(10, fpartlen);

  return (ipart + fpart) * sign;
}

void itoa(int n, char *dgt)
{
  if (n < 0)
  {
    *dgt++ = '-';
    n = -n;
  }
  if (n / 10)
    itoa(n / 10, dgt + 1);
  *dgt++ = n % 10 + '0';
  *dgt = '\0';
}