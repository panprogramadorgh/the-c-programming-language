#include <stdio.h>
#include <stdlib.h>

#define MAXLN (1U << 10)

int gline(char line[], int max);

/* Reverses the literal string `s`. */
void reverse(char s[], int f, int t);

int main()
{
  char *text = (char *)malloc(sizeof(char) * MAXLN);

  int start = 0;
  int end = gline(text, MAXLN) - 1; // Last index position.
  if (end < 0)
    end = 0;

  reverse(text, start, end);
  printf("%s\n", text);

  free(text);

  return 0;
}

int gline(char line[], int max)
{
  int i, c;

  for (i = 0; (i < max - 1) && (c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;
  line[i] = '\0';

  return i;
}

void reverse(char s[], int f, int t)
{
  if (f >= t)
    return;

  int c;
  c = s[t], s[t] = s[f], s[f] = c;
  reverse(s, ++f, --t);
}