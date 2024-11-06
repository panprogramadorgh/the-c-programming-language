#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXLN 128
#define MAXLINES 1024

#define BLUE "\e[1;34m"

#define RESET "\e[0m"

// Permite obtene lineas de texto desde la entrada estandar
int getln(char *line, int max);

// Retorna != 0 si b se encuentra en a
int strindex(char *a, char *b);

int main(int argc, char *argv[])
{
  char line[MAXLN], before[MAXLN], after[MAXLN];
  int line_len, word_len, word_index;

  if (argc < 2)
  {
    errno = EINVAL;
    perror("error: first argument was not specified");
    return EXIT_FAILURE;
  }
  word_len = strlen(argv[1]);

  while ((line_len = getln(line, MAXLN)) > 0)
    if ((word_index = strindex(line, argv[1])) != -1)
    {
      memset(before, 0, MAXLN);
      memset(after, 0, MAXLN);
      strncpy(before, line, word_index);
      strcpy(after, line + word_index + word_len);
      printf("%s", before);
      printf(BLUE "%s" RESET, argv[1]);
      printf("%s\n", after);
    }

  return EXIT_SUCCESS;
}

int getln(char *line, int max)
{
  int c, i;
  for (i = 0; i < max && (c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;
  line[i] = '\0';
  return i;
}

int strindex(char *a, char *b)
{
  int b_len = strlen(b);
  int i;

  for (i = 0; *(a + i); i++)
    if (strncmp((a + i), b, b_len) == 0)
      return i;
  return -1;
}