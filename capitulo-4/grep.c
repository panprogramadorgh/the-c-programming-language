#include <stdio.h>

/* References to the maximum length for the lines in the entire programm.  */
#define MAXLINE (1U << 10)

/* Allows to get a line of text from the stdinput. */
unsigned int gline(char line[]);

/* Returns the posicion of `t` inside `s`. */
int strindex(const char s[], const char t[]);

/* Returns the length of `s`. */
unsigned int strlength(const char s[]);

const char seq[] = "itoa.c";

/* Programa imitacion del clsico grep de UNIX. */
int main()
{
  char line[MAXLINE];
  extern const char seq[];
  int seqpos;

  while (gline(line) > 0)
  {
    seqpos = strindex(line, seq);
    if (seqpos != -1)
      printf("%s\n", line);
  }

  return 0;
}

/* Definiciones: */

unsigned int gline(char line[])
{
  int i, c;

  for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;
  line[i] = '\0';

  return i;
}

int strindex(const char s[], const char t[])
{
  int i, j;
  int slength, tlength;
  int eq, pos;

  slength = strlength(s);
  tlength = strlength(t);
  pos = -1;

  for (i = 0; (pos == -1) && (i < slength - tlength + 1); i++)
  {
    eq = 1;
    for (j = 0; eq && (j < tlength); j++)
    {
      if (s[i + j] != t[j])
        eq = 0;
    }
    if (eq == 1)
      pos = i;
  }

  return pos;
}

unsigned int strlength(const char s[])
{
  int i;
  for (i = 0; s[i] != '\0'; i++)
    ;
  return i;
}