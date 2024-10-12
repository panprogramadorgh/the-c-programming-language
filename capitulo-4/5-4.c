#include <stdio.h>

/* Compares two literal strings. If returns 0 both strings are equal, any other value for return is the difference between the first not-equal character at strings. */
int strcompare(char *a, char *b);

/* Returns t if s ends with t.  */
char *strend(char *s, char *t);

/* Own implementation of strend funcion, which returns t if s ends with t. */
int main()
{
  char *endswith = strend("hello world", "world");

  if (endswith != NULL)
  {
    printf("%s\n", endswith);
  }
  else
  {
    printf("It does't end with.\n");
  }

  return 0;
}

int strcompare(char *a, char *b)
{
  for (; *a == *b && *a != '\0'; a++, b++)
    ;
  return *a - *b;
}

char *strend(char *s, char *t)
{
  char *tend = t;
  char *send = s;
  char *pivot;

  while (*tend)
    tend++;
  while (*send)
    send++;

  pivot = send - (tend - t);

  if (strcompare(pivot, t) == 0)
  {
    return t;
  }
  return NULL;
}