#include <stdio.h>

/* Represents the maximum length for literal strings through the entire programm. */
#define MAX 1024

/* Allows to get a line of text from the stdin. */
unsigned int gline(char line[]);

/* Reverses the literal string `s`. */
void reverse(char s[]);

/* Searches `t` inside `s` starting from the end of the literal string. */
unsigned int strindex(char s[], char t[]);

/* Stores the text where the programm is goint to search ocurrenes in a reverse way. */
char text[MAX];
char target[] = "world";

/* Implementacion de funcion `strindex` reversa. */
int main()
{
  extern char text[MAX];
  extern char target[];
  int n;

  gline(text);
  n = strindex(text, target);

  printf("%s\t%d\n", text, n);
  return 0;
}

unsigned int gline(char line[])
{
  int i, c;

  for (i = 0; i < MAX - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;
  line[i] = '\0';
  return i;
}

void reverse(char s[])
{
  int c;
  int i, j;

  for (j = 0; s[j] != '\0'; j++)
    ;
  for (i = 0, j--; i < j; i++, j--)
    c = s[i], s[i] = s[j], s[j] = c;
}

unsigned int strindex(char s[], char t[])
{
  int i, j;
  int pos;

  pos = -1;
  reverse(s), reverse(t);
  for (i = 0; (pos == -1) && (s[i] != '\0'); i++)
  {
    for (j = 0; t[j] != '\0' && s[j + i] == t[j]; j++)
      ;
    if (t[j] == '\0')
      pos = i;
  }
  reverse(s), reverse(t);

  return pos;
}