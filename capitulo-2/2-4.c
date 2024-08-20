#include <stdio.h>

/* Determines wheter the program
is running on developing-mode. */
#define DEV 0

/* Max length for std line input. */
#define MAXLN 1024

/* Determines the chars that
will be removed from the line. */
#define RM "aeiou"

/* Allows to get a line of text
from the std input. The function
returns the amount of the characters
inserted inside the character array
`line` (without counting the last
null character) */
int gline(char line[]);

/* Removes the character ocurrences
of the character array `s2` from the
character array  `s1`. */
void squeeze(char s1[], char s2[]);

int main()
{
  char line[MAXLN];

  gline(line);
  squeeze(line, RM);

  printf("%s\n", line);

  return 0;
}

int gline(char line[])
{
  int i, c;

  for (i = 0; i < MAXLN - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
    line[i] = c;
  line[i] = '\0';

  return i;
}

void squeeze(char s1[], char s2[])
{
  int c1, c2;
  int eq;
  int i, k, j;

  i = k = j = 0;

  while ((c1 = s1[i]) != '\0')
  {
    eq = 0;
    j = 0;
    while (eq == 0 && (c2 = s2[j]) != '\0')
    {
      if (DEV)
        printf("%c\t%c\n", c1, c2);
      if (c1 == c2)
        eq = 1;

      j++;
    }
    if (!eq)
      s1[k++] = s1[i];

    i++;
  }
  s1[k] = '\0';
}