#include <stdio.h>

#define MAX_LNS 100
#define MAX_LN_LGTH 1000

/*
  Permite obtener una linea de entrada de stdin
  y guardarla en el arreglo pasado como primer
  argumento.
*/
int get_line(char line[], int maxlength);

/*
  Permite copiar los datos de las posiciones de la memoria del array `from` al array `to`.
*/
int copy_line(char from[], int froml, char to[], int maxtol);

/*
  Permite clonar el contenido de manera
  inversa del array de caractesres `from`
  en el array de caracteres `to`.
  Se debe indicar la longitud maxima de `to`
  y esta debe superar la longitud actual
  de `from`.
*/
int reverse_line(char from[], int from_length, char to[], int maxto);

/*
  Permite obtener la longitud de una
  cadena de caracteres.
*/
int get_line_length(char line[]);

int main()
{
  char process_state = 0;
  /* Cada linea */
  char line[MAX_LN_LGTH];
  /* Cada linea dada la vuelta */
  char rline[MAX_LN_LGTH];
  /* Arreglo con todas las lineas dadas la vuelta */
  char rlines[MAX_LN_LGTH][MAX_LNS];

  int length, lindex;

  for (lindex = 0; (length = get_line(line, MAX_LN_LGTH)) > 1 && lindex < MAX_LNS; ++lindex)
  {
    if (reverse_line(line, length, rline, MAX_LN_LGTH) == 0)
    {
      if (copy_line(rline, length, rlines[lindex], MAX_LN_LGTH) != 0)
      {
        fprintf(stderr, "Error due copyng line");
        process_state = 1;
      }
    }
    else
    {
      fprintf(stderr, "Error due reversing line");
      process_state = 1;
    }
  }

  for (--lindex; lindex >= 0; --lindex)
  {
    printf("%s\n", rlines[lindex]);
  }

  return process_state;
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

  /* Indice caracter nulo + 1 = longitud
  de la cadena contando caracter nulo */
  return i + 1;
}

int get_line_length(char line[])
{
  int i;
  for (i = 0; line[i] != '\0'; ++i)
    ;

  /* Indice caracter nulo + 1 = longitud
 de la cadena contando caracter nulo */
  return i + 1;
}

int copy_line(char from[], int froml, char to[], int maxtol)
{
  if (froml > maxtol)
    return 1;

  int i;
  for (i = 0; (to[i] = from[i]) != '\0'; ++i)
    ;

  return 0;
}

int reverse_line(char from[], int from_length, char to[], int maxto)
{
  int c, i, from_end_index;
  from_end_index = from_length - 1;

  if (from_end_index + 1 > maxto)
    return 1;

  for (i = from_end_index; i > 0; --i)
    to[from_end_index - i] = from[i - 1];
  to[from_end_index - i] = '\0';

  return 0;
}