#include <stdio.h>

#define MAXSTR 1024

/* Concatenates a and b literal strings. */
char *strconcat(char *a, char *b);

/* Own implementacion of strcat from <string.h> */
int main()
{
  char greet[MAXSTR] = "hello world";
  printf("%s\n", strconcat(greet, " adios"));
  return 0;
}

char *strconcat(char *a, char *b)
{
  char *aend = a;

  while (*aend++)
    ;
  for (aend--; *aend++ = *b++;)
    ;
  return a;
}