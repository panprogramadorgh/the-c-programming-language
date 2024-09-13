#include <stdio.h>

/* Determines the maximum length for input lines. */
#define MAXLINE 1024

/* Determines the maximum amount of lines to be analized. */
#define MAXLINES 128

/* Allows to get a line of text from the stdinput and returns the length of the string literal introduced. */
unsigned int ginput(char line[], unsigned int limit);

/* Divides `s` into different lines inside `lines`. */
int split_lines(const char s[], char lines[][MAXLINE], unsigned int mlns);

/* Returns the position of `t` inside `s` starting from `beg`. */
int strindex(const char s[], const char t[], unsigned int beg);

/* Returns the lenght of `s`. */
int strlength(const char s[]);

/*
FIXME: Programa mal planetado.

Es totalmente preferible manejar la logica del programa al mismo tiempo que se van introduciendo nuevas lineas. La razon de ello es que el programa se vuelve incrementalmente mas complicado manejar los limites de maxima cantidad de linas asi como de maxima cantida de caracteres por linea.
En estos momentos `strindex` esta buscando, y encontrando con exito en ocasiones, secuencias de caracteres fuera del limite de caracteres por linea asi como de cantidad de linas.
Fuera de eso la logica es limpia y esta bien manejada.

*/

/* Programa para verificar si existen lineas duplicadas. */
int main()
{
  char text[MAXLINE];
  char lines[MAXLINES][MAXLINE];
  /* Relacinado con el manejo de ocurrencias. */
  int pos, ocu;
  /* Relacionado con el manejo de las lineas. */
  int l, lnlen, lns;

  ginput(text, MAXLINE);                    // Extrae la entrada.
  lns = split_lines(text, lines, MAXLINES); // Extrae lineas de la entrada.

  for (l = 0; l < lns; l++)
  {
    lnlen = strlength(lines[l]);

    for (ocu = 0, pos = -1; (ocu < 2) && (pos = strindex(text, lines[l], pos + 1)) >= 0;)
      if ((text[pos + lnlen] == '\n') || (text[pos + lnlen] == '\0'))
        ocu++;

    if (ocu > 1)
    {
      printf("%s\n", lines[l]); // La linea duplicada se imprime
      goto error;
    }
  }
  return 0;

error:
  return 1;
}

unsigned int ginput(char line[], unsigned int limit)
{
  int i, c;
  for (i = 0; i < limit - 1 && (c = getchar()) != EOF; i++)
    line[i] = c;
  line[i] = '\0';
  return i;
}

int split_lines(const char s[], char lines[][MAXLINE], unsigned int mlns)
{
  int pos;
  int i, line;

  pos = -1;
  line = 0;
  do
  {
    for (i = pos + 1; ((i - pos + 1) < MAXLINE - 1) && (s[i] != '\0' && s[i] != '\n'); i++)
      lines[line][i - (pos + 1)] = s[i];
    lines[line][i] = '\0';

    line++;
  } while ((line < mlns) && (pos = strindex(s, "\n", pos + 1)) >= 0);

  return line;
}

int strindex(const char s[], const char t[], unsigned int beg)
{
  int pos, slen;
  int i, j;

  for (slen = 0; s[slen] != '\0'; slen++)
    ;
  for (i = beg, pos = -1; pos == -1 && i < slen; i++)
  {
    for (j = 0; t[j] != '\0' && s[i + j] == t[j]; j++)
      ;
    if (j > 0 && t[j] == '\0')
      pos = i;
  }
  return pos;
}

int strlength(const char s[])
{
  int i;
  for (i = 0; s[i] != '\0'; i++)
    ;
  return i;
}