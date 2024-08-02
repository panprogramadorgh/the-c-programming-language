#include <stdio.h>

/* Determina el maximo de caracteres
por linea a obtener por la funcion
`get_fline`. */
#define MAXLINE 1024

/* Determina la longitud
de cada una de las lineas
dobladas (el salto de linea cuenta). */
#define COLS 32

/* Permite obtener lineas de texto
desde la entrada estandar y guardarlas
en el arreglo de caracteres `line`.
La funcion retorna la cantidad de
caracteres de la linea (contando el
caracter nulo); ademas la funcion omite
los caracteres de tabulacion y de espacio
en blanco trimenado asi el contenido. */
int get_flines(char line[], int maxlength, int finterval);

/* Permite obtener el indice en la
lista de multiplos de `m` inmediatamente
superior al valor de `n`. */
int calc_next_multiple(int m, int n);

/* Programa para doblar lineas de
entrada de texto. */
int main()
{
  /* Almacena la linea actual */
  char line[MAXLINE];
  int length;

  while ((length = get_flines(line, MAXLINE, COLS)) > 1)
  {
    printf("%s\n", line);
  };

  return 0;
}

int get_flines(char line[], int maxlength, int finterval)
{
  int n, m;
  int i, c;

  for (i = 0;
       i < maxlength - 1 &&
       (c = getchar()) != EOF &&
       c != '\n';
       ++i)
  {
    n = calc_next_multiple(finterval, i);
    m = finterval * n;
    if (i != 0 && i == m - 1)
    {
      line[i] = '\n';
      ++i;
    }
    if (c != '\t' && c != ' ')
      line[i] = c;
    else
      line[i] = ' ';
  }
  line[i] = '\0';

  return i + 1;
}

int calc_next_multiple(int m, int n)
{
  int i;
  for (i = 0; i * m <= n; ++i)
    ;
  return i;
}