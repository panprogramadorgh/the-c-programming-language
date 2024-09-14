#include <stdio.h>

/* Determines the maximum length for input lines. */
#define MAXLINE (1U << 10)

/* Determines the maximum amount of lines to be analized. */
#define MAXLINES (1U << 7)

/* Compruba si la linea actual esta duplicada comprobando cada una de las empezando desde la actual hasta la primera. */
int chcurline(const unsigned int curline, const unsigned int limit);

/* Almacena todas las lineas de entrada. */
char lines[MAXLINES][MAXLINE];

/* Programa para verificar la existencia de lineas duplicadas. */
int main()
{
  /* caracter, linea actual, indice dentro de linea, salir. */
  int c, line, cindex, out = 0;

  line = 0;
  while (!out && line < MAXLINES)
  {
    for (cindex = 0;
         !out &&
         (c = getchar()) != '\n';
         cindex++)
    {
      if (c == EOF || cindex >= MAXLINE - 1)
      {
        out = 1;
        continue;
      }
      lines[line][cindex] = c;
    }
    lines[line][cindex] = '\0';
    if (chcurline(line, MAXLINES))
    {
      printf("%s\n", lines[line]);
      return 0;
    }

    if (cindex > 0)
      line++;
  }

  if (out)
  {
    fprintf(stderr, "Program exit caused for an EOF character or line overflow.\n");
  }
  else
  {
    fprintf(stderr, "Program exit caused for max amount of lines reached.\n");
  }

  return 1;
}

int chcurline(const unsigned int curline, const unsigned int limit)
{
  int line, i;

  if (curline >= limit || curline == 0)
    return 0;

  for (line = curline - 1; line >= 0; line--)
  {
    for (i = 0; (lines[curline][i] != '\0') && (lines[curline][i] == lines[line][i]); i++)
      ;
    // Si es el fin de linea de curline asi como de la linea actual, quiere decir que son iguales y por lo tanto si esta duplicada la linea.
    if (i > 0 && lines[curline][i] == '\0' && lines[line][i] == '\0')
      return 1;
  }
  return 0;
}