#include <stdio.h>

/* Determina la maxima cantidad
de caracteres de entrada para
la funcion `get_input`.  */
#define MAXINPUT 1024

/* Hace referencia a la forma
de iniciar un comentario en
el lenguaje de programacion C. */
#define CSTART "/*"

/* Hace referencia a la forma
de terminar un comentario en
el lenguaje de programacion C. */
#define CEND "*/"

/* Funcion para leer texto de
la entrada estandar. La funcion
retorna la cantidad de caracteres
leidos (incluyendo el caracter nulo). */
int get_input(char arr[], int maxlength);

/* Funcion para obtener el indice
de inicio de una secuencia de caracteres
`tar` dentro del array de caracteres `arr`.
Se debe indicar la longitud maxima del
array de caracteres `from` y un valor
de desplazamiento `offset` (que debe
ser 0 en caso de que `from` sea una
referencia al primer elemento del array). */
int find(char from[], char tar[], int offset, int maxlength);

/* Permite comprarar dos arrays de
caracteres. Si contienen los mismos
elementos retornara 1 y si no, retornara 0. */
int compare(char a[], char b[]);

/* Permite obtener un extracto de un
array de caracteres en base a un indice
de comienzo y fin. */
void stract(char from[], char to[], int maxlength, int start, int end);

/* Permite obtener la longitud
de un array de caracteres. */
int get_length(char arr[]);

/* Permite desplazar los caracteres
de una cadena de caracteres `d`
posiciones a partir de `index`.
El resultado se guarda en el array `to`. */
int displace_chars(char arr[], int maxlength, int index, int d);

/* Permite copiar un array de caracteres
origen (`from`) en un array de caracteres
destino (`to`). */
void copy(char from[], char to[]);

/* TODO: Permite obtener el indice de inicio
y fin de un comentario del lenguaje
de programacion C, dentro del array de
caracteres `from`. Para buscar la secuencia
de caracteres de inicio y fin se tiene
en cuenta factores como que dichas secuencias
no se encuentren dentro de una constante
de caracter. */
int find_comment(char from[], int maxlength);

/* Programa para eliminar comentarios
de un programa de C. */
int main()
{
  char arr[MAXINPUT] =
      "hola /* y */ adios";
  int length, start, end;

  if ((length = get_input(arr, MAXINPUT)) > 1)
  {
    while ((start = find(arr, CSTART, 0, MAXINPUT)) > -1)
    {
      end = find(arr, CEND, start, MAXINPUT);
      if (end == -1)
        end = length - 1;
      displace_chars(arr, MAXINPUT, start,
                     -((end - start) + get_length(CEND)));
    }
    printf("%s\n", arr);
  }

  return 0;
}

int get_input(char arr[], int maxlength)
{
  int i, c;
  for (i = 0; i < maxlength - 1 && (c = getchar()) != EOF; ++i)
    arr[i] = c;
  arr[i] = '\0';
  return i + 1;
}

int find(char from[], char tar[], int offset, int maxlength)
{
  int eq, index, tarlength;
  int i, j;

  tarlength = get_length(tar);

  char tartry[tarlength];

  index = -1;

  for (i = offset; index == -1 && i < maxlength && from[i] != '\0'; ++i)
  {
    stract(from, tartry, maxlength, i, i + tarlength);
    eq = compare(tartry, tar);
    if (eq == 1)
      index = i;
  }

  return index;
}

int compare(char a[], char b[])
{
  int eq, length;
  int i;

  length = get_length(a);
  if (get_length(b) != length)
    return 0;

  eq = 1;

  for (i = 0; i < length && eq == 1; ++i)
  {
    if (a[i] != b[i])
      eq = 0;
  }

  return eq;
}

void stract(char from[], char to[], int maxlength, int start, int end)
{
  int i;
  for (i = start; i < end; ++i)
    to[i - start] = from[i];
  to[i - start] = '\0';
}

int get_length(char arr[])
{
  int i;
  for (i = 0; arr[i] != '\0'; ++i)
    ;
  return i;
}

int displace_chars(char arr[], int maxlength, int index, int d)
{
  char rarr[maxlength];
  /* Variables de bucles */
  int i, k, j;
  int length, affected;

  copy(arr, rarr);

  /* `index` + el valor absoluto de `d`
  debe ser inferior a `maxlength`. */
  if (index + d >= maxlength || index + (-d) >= maxlength)
    return -1;

  i = k = 0;

  while (i < maxlength - 1 &&
         k < maxlength &&
         rarr[k] != '\0')
  {
    if (i == index && k == i)
    {
      if (d > 0)
      {
        for (j = i; j < i + d; ++j)
          arr[j] = ' ';
        i += d;
      }
      else if (d < 0)
        k += -d;
    }

    arr[i] = rarr[k];

    ++i;
    ++k;
  }
  arr[i] = '\0';

  length = get_length(rarr);
  affected = length - index;

  /* Los espacios adicionales
  en un desplazamiento positivo
  no cuentan como caracteres
  afectados. */
  if (d > 0)
    affected -= d;

  return affected;
}

void copy(char from[], char to[])
{
  int i;

  for (i = 0; (to[i] = from[i]) != '\0'; ++i)
    ;
}