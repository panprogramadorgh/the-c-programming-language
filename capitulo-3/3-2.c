#include <stdio.h>
#include <string.h>

/* Determines the maximum length for literal strings in the programm.  */
#define MAX 1024

/* Allows to convert spaced characters like \t and \n from `s` while copies the new string literal into `t`.  */
void scape(const char s[], char t[]);

/* Allows to convert literal scaped character sequences from `s` into real scaped characters and copies the new literal string into `t`. */
void unscape(const char s[], char t[]);

int main()
{
  char from[MAX] = "hola-\\t-adios-\\n-hola";
  char to[MAX];

  unscape(from, to);

  printf("%s\n", to);

  return 0;
}

void scape(const char s[], char t[])
{
  int c, i, k;

  k = i = 0;

  while (i < MAX - 1 && (c = s[i]) != '\0')
  {
    switch (c)
    {
    case '\n':
      t[k++] = '\\';
      t[k] = 'n';
      break;
    case '\t':
      t[k++] = '\\';
      t[k] = 't';
      break;
    case '\b':
      t[k++] = '\\';
      t[k] = 'b';
      break;
    case '\r':
      t[k++] = '\\';
      t[k] = 'r';
      break;
    case '\'':
      t[k++] = '\\';
      t[k] = '\'';
      break;
    case '\"':
      t[k++] = '\\';
      t[k] = '\"';
      break;
    case '\?':
      t[k++] = '\\';
      t[k] = '\?';
      break;
    case '\\':
      t[k++] = '\\';
      t[k] = '\\';
      break;
    default:
      t[k] = c;
      break;
    }

    i++;
    k++;
  }
  t[k] = '\0';
}

void unscape(const char s[], char t[])
{
  int cur_char, next_char;
  int i, k;

  i = k = 0;

  while ((i < MAX - 1) && ((cur_char = s[i]) != '\0'))
  {
    if (cur_char == '\\')
    {
      next_char = s[i + 1];
      switch (next_char)
      {
      case 't':
        t[k] = '\t';
        i++;
        break;
      case 'n':
        t[k] = '\n';
        i++;
        break;
      }
    }
    else
    {
      t[k] = cur_char;
    }

    k++;
    i++;
  }
  t[k] = '\0';
}