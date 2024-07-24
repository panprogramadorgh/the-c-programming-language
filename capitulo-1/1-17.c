#include <stdio.h>

#define MAXLINES 100
#define MAXLENGTH 1000
#define MINLENGTH 10

/*
  Permite obtener una linea de entrada de stdin y guardarla en el arreglo pasado como primer argumento.
*/
int inputline(char line[], int maxlength);

/*
  Permite copiar los datos de las posiciones de la memoria del array `from` al array `to`.
*/
void copy_char_arr(char from[], char to[]);

int main()
{
  char line[MAXLENGTH];
  char lines[MAXLENGTH][MAXLINES];
  int i, linelength;

  for (i = 0; i < MAXLINES && (linelength = inputline(line, MAXLENGTH)) > 1; ++i)
  {
    if (MINLENGTH <= linelength)
      copy_char_arr(line, lines[i]);
  }

  for (; i >= 0; --i)
  {
    if (lines[i][0] != '\0')
      printf("%s\n", lines[i]);
  }

  return 0;
}

int inputline(char line[], int maxlength)
{
  int c, i;
  for (i = 0; i < maxlength - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;
  line[i] = '\0';
  /* Longitud minima = 1 porque el caracter nulo cuenta */
  return i + 1;
}

void copy_char_arr(char from[], char to[])
{
  int i;

  for (i = 0; (to[i] = from[i]) != '\0'; ++i)
    ;
}