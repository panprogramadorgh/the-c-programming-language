#include <stdio.h>

#define MAX_LN_LGTH 100

/*
  Permite obtener una linea de entrada de stdin
  y guardarla en el arreglo pasado como primer
  argumento.
*/
int get_line(char line[], int maxlength);

/*
  Elimina las tabulaciones y espacios en blanco
  al final de cada linea.
*/
void trim_line(char line[]);

/*
  Programa para leer lineas de texto de entrada
  y eliminar los caracteres de tabulacion
  y espacio al final.
*/
int main()
{
  char line[MAX_LN_LGTH];
  int length;

  while ((length = get_line(line, MAX_LN_LGTH)) > 1)
  {
    trim_line(line);
    printf("%s\n", line);
  }

  return 0;
}

int get_line(char line[], int maxlength)
{
  int c, i;

  for (
      i = 0;
      i < maxlength - 1 &&
      (c = getchar()) != EOF &&
      c != '\n';
      ++i)
  {
    line[i] = c;
  }
  line[i] = '\0';

  /* Longitud minima = 1 porque
  el caracter nulo cuenta */
  return i + 1;
}

void trim_line(char line[])
{
  int i, c;
  for (i = 0; (c = line[i]) != '\0'; ++i)
  {
    if (c == ' ' || c == '\t')
      line[i] = '\0';
  }
}
