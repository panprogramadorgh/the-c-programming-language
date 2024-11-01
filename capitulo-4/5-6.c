#include <stdio.h>
#include <string.h>
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
void itoa(long int n, char *dgt);

/* Converts a double number into its literal string representation. */
void ftoa(double n, char *dgt);

/* Reverses the literal string s. */
void reverse(char *s);

/* Returns the index of seq inside s.  */
int strindex(char *s, char *seq);

int main()
{
  char digit[100];

  ftoa(-3.1415, digit);
  printf("%s\n", digit);

  int foo = strindex(digit, "14");
  printf("%d\n", foo);

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

void itoa(long int n, char *dgt)
{
  static int index = 0;
  static int max = 0;

  if (n < 0)
  {
    *dgt++ = '-';
    n = -n;
  }

  if (n / 10)
  {
    max++;
    itoa(n / 10, dgt);
    index++;
  }
  *(dgt + index) = n % 10 + '0';
  if (index == max)
  {
    *(dgt + index + 1) = '\0';
    index = 0;
  }
}

void ftoa(double n, char *dgt)
{
  long int ipart = (long int)n * (n < 0 ? -1 : 1);
  long int fpart = (long int)((n - (ipart * (n < 0 ? -1 : 1))) * (n < 0 ? -1 : 1) * pow(10, __DBL_DIG__));

  if (n < 0)
    *dgt++ = '-';
  itoa(ipart, dgt);
  dgt += strlen(dgt);
  *dgt++ = '.';
  itoa(fpart, dgt);
}

void reverse(char *s)
{
  char *e = s, t;
  while (*e)
    e++;
  for (e--; s < e; s++, e--)
    t = *e, *e = *s, *s = t;
}

int strindex(char *s, char *seq)
{
  char *pivot = s;
  char *ch = seq;
  int seq_len;

  while (*ch)
    *ch++;
  seq_len = ch - seq;

  while (*pivot)
  {
    for (ch = pivot; (ch - pivot < seq_len) && *ch == *(seq + (ch - pivot)); ch++)
      ;
    if (ch - pivot > 0 && ch - pivot == seq_len)
      return pivot - s;
    pivot++;
  }
  return -1;
}