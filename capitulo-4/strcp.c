#include <stdio.h>

char *strcp(char *f, char *t);

int strcm(char *a, char *b);

int main()
{
  printf("%d\n", !strcm("hello world", "hello world"));

  return 0;
}

char *strcp(char *f, char *t)
{
  while (*t++ = *f++)
    ;
  return f;
}

int strcm(char *a, char *b)
{
  for (; *a == *b; a++, b++)
    if (*a == '\0')
      return 0;
  return *a - *b;
}