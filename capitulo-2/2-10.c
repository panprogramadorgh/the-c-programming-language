#include <stdio.h>
#include <string.h>

/* Returns the lower version
of string literal `str`. */
void lower(const char from[], char to[]);

int main()
{
  char text[] = "TRES TRISTES COMUNISTAS\
  TRAGABAN PLOMO EN UN GULAG.";
  char new[1024];

  lower(text, new);

  printf("%s\n", new);

  return 0;
}

void lower(const char from[], char to[])
{
  int offset, strlgth;
  int i;

  offset = 'a' - 'A';
  strlgth = strlen(from);

  for (i = 0; i < strlgth; i++)
    to[i] = (from[i] >= 'A' && from[i] <= 'Z') ? from[i] + offset : from[i];
  to[i] = '\0';
}