#include <stdio.h>

#define MAX 1024

/* Allows to get input from the std input and returns the length of the resulting string literal. */
int getinput(char input[]);

/* Checks if any char of `s1` is included in `s2`. */
int matches(const char s1[], const char s2[]);

int main()
{
  char first[MAX];
  char seccond[MAX];
  int m;

  printf("First: ");
  getinput(first);

  printf("Seccond: ");
  getinput(seccond);

  m = matches(first, seccond);
  printf("%d\n", m);

  return 0;
}

int getinput(char input[])
{
  int c, i;

  for (i = 0; i < MAX - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    input[i] = c;
  input[i] = '\0';
  return i;
}

int matches(const char s1[], const char s2[])
{
  int i, j;

  for (i = 0; s1[i] != '\0'; i++)
    for (j = 0; s2[j] != '\0'; j++)
      if (s1[i] == s2[j])
        goto equal;
  return 0;
equal:
  return 1;
}