#include <stdio.h>

#define MAXLN 1024

/* Allows to get a line of
text from the std input. */
int gline(char line[]);

/* Returns the first position of any
ocurrence between the character
array `s1` and `s2. */
int any(char s1[], char s2[]);

int main()
{
  char line[MAXLN];
  int pos;

  gline(line);
  pos = any(line, "aeiou");

  printf("%s\t%d\n", line, pos);

  return 0;
}

int any(char s1[], char s2[])
{
  int ocupos;
  int c1, c2, eq;
  int i, k;

  /* Inicialization */
  ocupos = i = k = -1;

  while (ocupos == -1 && (c1 = s1[++i]) != '\0')
  {
    k = -1;
    while (ocupos == -1 && (c2 = s2[++k]) != '\0')
    {
      eq = c1 == c2;
      if (eq)
        ocupos = i;
    }
  }

  return ocupos;
}

int gline(char line[])
{
  int i, c;

  for (i = 0; i < MAXLN - 1 && (c = getchar()) != '\n' && c != EOF; i++)
    line[i] = c;
  line[i] = '\0';

  return i;
}