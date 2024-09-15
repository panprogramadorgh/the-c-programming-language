#include <stdio.h>

#define MAXLINE (1U << 10)

#define MAXLINES (1U << 10)

/* Allows to copy the literal strings. */
void copystr(const char from[], char to[]);

int main()
{
  char maxline[MAXLINE];
  char line[MAXLINE];
  int c, cindex, lindex, max;

  lindex = max = 0;

  while (lindex < MAXLINE)
  {
    for (cindex = 0; (cindex < MAXLINE - 1) && (c = getchar()) != '\n' && c != EOF; cindex++)
      line[cindex] = c;
    line[cindex] = '\0';

    if (cindex > max)
    {
      max = cindex;
      copystr(line, maxline);
    }

    if (c != '\n')
      break;
    else if (cindex > 0)
      lindex++;
  }
  if (max >= MAXLINE - 1)
    fprintf(stderr, "Line overflow.\n");
  else if (lindex >= MAXLINES)
    fprintf(stderr, "Max amount of lines exceded.\n");

  if ((lindex == 0 && cindex > 0) || (lindex > 0))
    printf("%s\n", maxline);

  return 0;
}

void copystr(const char from[], char to[])
{
  int i;
  for (i = 0; (to[i] = from[i]) != '\0'; i++)
    ;
}