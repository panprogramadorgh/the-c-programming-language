#include <stdio.h>

/* Determina la maxima cantidad
de caracteres de entrada para
la funcion `get_input` asi
como la longitud maxima de muchos
arrays de todo el programa.  */
#define MAX 1024

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
void slice(char from[], char to[], int maxto, int start, int end);

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

/* TODO: Permite obtener el indice de inicio o fin
de un comentario del lenguaje de programacion
C, dentro del array de caracteres `from`.
Para buscar la secuencia de caracteres de
inicio se tiene en cuenta factores como
que dicha secuencia no se encuentre dentro
de una constante de caracter. Los posibles
valores para `seq` provienen de las constantes
simbolicas `CSTART` y `CEND`. */
int find_comment(char from[], int offset, int maxlength, char seq[]);

/* Permite comprobar que `n` sea multiplo
de `m`. Si la funcion retorna ` quiere decir
que si lo es y si retorna 0 quiere decir que no. */
int is_multiple_of(int m, int n);

/* Permite contar todas las apariciones
de un caracter concreto `c` dentro
de un array de caracteres `from`.
Se debe indicar la longitud maxima
del array. */
int count(char from[], char tar[], int maxlength);

/* Programa para eliminar comentarios
de un programa de C. */
int main()
{
  // FIXME: Logica para eliminar comentarios
  // char arr[MAX] =
  //     "hola /* y */ adios";
  // int length, start, end;

  // if ((length = get_input(arr, MAX)) > 1)
  // {
  //   while ((start = find(arr, CSTART, 0, MAX)) > -1)
  //   {
  //     end = find(arr, CEND, start, MAX);
  //     if (end == -1)
  //       end = length - 1;
  //     displace_chars(arr, MAX, start,
  //                    -((end - start) + get_length(CEND) - 1));
  //   }
  //   printf("%s\n", arr);
  // }

  char arr[MAX] =
      "hola /* comentario */ que tal";

  find_comment(arr, 0, MAX, CSTART);

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

  if (offset >= maxlength)
    return -1;

  for (i = offset; index == -1 && i < maxlength && from[i] != '\0'; ++i)
  {
    slice(from, tartry, maxlength, i, i + tarlength);
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

// FIXME: Cosas raras con slice.

void slice(char from[], char to[], int maxto, int start, int end)
{
  int i, length;

  length = end - start;

  for (i = start; i < end && i - start < maxto - 1; ++i)
    to[i - start] = from[i];
  to[i - start] = '\0';
}

int get_length(char arr[])
{
  int i;
  for (i = 0; arr[i] != '\0'; ++i)
    ;
  /* Se cuenta el caracter nulo */
  return i + 1;
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

int find_comment(char from[], int offset, int maxlength, char seq[])
{
  int pos = find(from, seq, offset, maxlength);
  char some_slice[pos];

  /* TODO: Obtener slice desde la posicion 0
  hasta la posicion en la que se encontro `seq`. */

  /* TODO: Contar numero de apariciones para
  el caracter quot ("). */

  /* TODO: Comprobar si dicha cantidad es
  multiplo de 2, en cuyo caso la secuencia
  de comentario estaria a fuera de una constante
  de caracter y por lo tanto seria una posicion
  para una secuencia de comentario valida. */

  // slice(from, some_slice, pos, 0, pos - 1);

  printf("%s\n", some_slice);
}

int is_multiple_of(int m, int n)
{
  int p, i, is;

  is = 0;

  for (p = i = 1; p < n; ++i)
  {
    if ((p = m * i) == n)
      is = 1;
  }
  return is;
}

int count(char from[], char tar[], int maxlength)
{
  int pos, ccount;

  pos = ccount = 0;

  while (pos > -1 && pos < maxlength)
  {
    pos = find(from, tar, pos + 1, maxlength);
    if (pos > -1)
      ++ccount;
  }

  return ccount;
}