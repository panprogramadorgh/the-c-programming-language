#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 1024
#define MAXLINE 127

/* Prints program usage and exists the process  */
void prtusage(const char **argv);

/* Obtains a line of text from stdin */
int gline(char *line, int maxln);

int main(int argc, const char **argv)
{
  char line[MAXLINE + 1];
  unsigned long int nlines = 0, found = 0;
  int except = 0, number = 0;
  int c;

  while (--argc > 0 && (*++argv)[0] == '-')
  {
    while ((c = *++argv[0]))
    {
      switch (c)
      {
      case 'x':
        except = 1;
        break;
      case 'n':
        number = 1;
        break;
      default:
        argc = -1;
        break;
      }
    }
  }
  if (argc != 1)
    prtusage(argv);
  while (gline(line, MAXLINE))
  {
    nlines++;
    if ((strstr(line, *argv) != NULL) != except)
    {
      found++;
      if (number)
        printf("%lu. %s\n", nlines, line);
      else
        printf("%s\n", line);
    }
  }

  return found;
}

void prtusage(const char **argv)
{
  const char *frst = argv[0];
  fprintf(stderr, "Usage: %s -nx <pattern>\n", frst);
  exit(1);
}

int gline(char *line, const int maxln)
{
  int c, m = maxln;
  while ((c = getchar()) != EOF && c != '\n' && m-- > 0)
    *line++ = c;
  *line = '\0';
  return maxln - m;
}
