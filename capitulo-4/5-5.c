#include <stdio.h>

/* Compares the first n characters of a and b. */
int strncomp(char *a, char *b, unsigned n);

/* Copies the first n characters of f in t. */
char *strncopy(char *f, char *t, unsigned n);

int main()
{
  char to[1024];
  printf("%s\n", strncopy("hello world", to, 5));
  return 0;
}

int strncomp(char *a, char *b, unsigned n)
{
  for (int i = 1;
       i < n && *a == *b && *a;
       i++, a++, b++)
    ;
  return *a - *b;
}

char *strncopy(char *f, char *t, unsigned n)
{
  char *tch = t;
  int i = 0;
  while (i < n + 1 && (*tch++ = *f++))
    i++;
  *--tch = '\0';
  return t;
}