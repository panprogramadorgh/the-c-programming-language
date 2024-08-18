#include <stdio.h>

#define MAXLINE 1024

/* Permite obtener una linea
de la entrada estandar. Retorna
la longitud de la constante de
cadena sin el caracter nulo. */
int gline(char line[]);

int main()
{
  char line[MAXLINE];

  int foo = gline(line);

  printf("%d\t%s\n", foo, line);

  return 0;
}

int gline(char line[])
{
  int c;
  int i;
  int end;

  for (i = end = 0; end == 0; ++i)
  {
    if (!(i < MAXLINE - 1))
      end = 1;
    else if ((c = getchar()) == '\n')
      end = 1;
    else if (c == EOF)
      end = 1;
    else
      line[i] = c;
  }
  line[i - 1] = '\0';

  return i;
}