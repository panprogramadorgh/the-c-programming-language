#include <stdio.h>

/* Determina la maxima cantidad
de caracteres de entrada para
la funcion `get_input`.  */
#define MAXINPUT 1024

/* Funcion para leer texto de
la entrada estandar. La funcion
retorna la cantidad de caracteres
leidos (incluyendo el caracter nulo). */
int get_input(char arr[], int maxlength);

/* Funcion para obtener el indice
de inicio de una secuencia de caracteres
`tar` dentro del array de caracteres `arr`. */
int find(char arr[], int maxlength, char tar[], int tarlength);

/* Permite comprarar dos arrays de
caracteres. Si contienen los mismos
elementos retornara 1 y si no, retornara 0.
La longitud maxima de ambos arrays ha de
ser la misma. */
int compare(char a[], char b[], int maxlength);

/* TODO: Permite obtener un extracto de un
array de caracteres en base a un indice
de comienzo y fin. */
void stract(char tar[], char arr[], int maxlength, int start, int end);

/* Programa para eliminar comentarios
de un programa de C. */
int main()
{
  char a[MAXINPUT] = "hola";
  char b[MAXINPUT] = "hola";
  int eq;

  eq = compare(a, b, MAXINPUT);

  printf("%d\n", eq);

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

int find(char arr[], int maxlength, char tar[], int tarlength)
{
  int end;
  int i, j;

  end = 0;

  for (i = 0; end == 0 && i < maxlength; ++i)
  {
    for (j = i; j + tarlength < tarlength; ++j)
    {
      /* TODO: Extraer array de caracteres
      a partir de indices de `arr` y compararlo
      con array de caracteres `tarlength`. */
    }
  }
  return i - 1;
}

int compare(char a[], char b[], int maxlength)
{
  int eq;
  int i;

  eq = 1;

  for (i = 0; i < maxlength && eq == 1; ++i)
  {
    if (a[i] != b[i])
      eq = 0;
  }

  return eq;
}