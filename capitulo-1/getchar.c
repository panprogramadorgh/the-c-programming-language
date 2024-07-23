#include <stdio.h>
#include <stdlib.h>

char *input(char *message)
{
  printf("%s", message);

  int index, c;
  char *buffer = (char *)malloc(sizeof(char));

  for (index = 0; (c = getchar()) != '\n'; ++index)
  {
    if (index == 0)
    {
      *buffer = c;
      continue;
    }
    buffer = (char *)realloc(buffer, (index + 1) * sizeof(char));
    *(buffer + index) = c;
  }

  return buffer;
}

void char_counter()
{
  int tabs = 0, spaces = 0, lines = 0;
  int c;
  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
      ++tabs;
    else if (c == ' ')
      ++spaces;
    else if (c == '\n')
      ++lines;
  }
  printf("\nChar\tCount\n");
  printf("tab\t%5d\n", tabs);
  printf("space\t%5d\n", spaces);
  printf("line\t%5d\n", lines);
}

int main()
{
  char_counter();

  return 0;
}