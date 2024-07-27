#include <stdio.h>

/* Representa el maximo tamaño del
texto de entrada por llamada a la
funcion `get_input`.
```c
int main()
{
  char arr[MAXILGTH];

  // Maximo tamaño de texto
  // de entrada = 1024 caracteres
  // (1024 bytes).
  get_input(arr, MAXILGTH);

  return 0;
}

```
 */
#define MAXILGTH 32

/* Representa el tamaño de las tabulaciones */
#define TABSIZE 8

/* Funcion encargada de formatear el array
de caracteres `arr` reemplazando los
espaciados formados por caracteres espacio en
blanco por la minima cantidad posible de
tabuluadores o espacios (si dado el momento
es necesario). El segundo parametro `maxlength`
indica la longitud de entrada de texto maxima a ser
guardada en el array (longitud del texto
una vez establecido el nuevo formato deseado) */
int detab(char arr[], int maxlength);

/* Funcion encargada de leer la entrada
estandar y almacenar el resultado en un array.
La funcion devuelve el numero de caracteres
leidos de la entrada. */
int get_input(char arr[], int maxlength);

/* Permite calcular multiplos de `m` donde
`n` es el multiplo deseado de `m`. Si `m` = 4
y `n` = 3, el resultado sera 12 porque el tercer
multiplo de 4 es 12. */
int calc_multiple(int m, int n);

/* Guarda en el parametro `arr` una
matriz de multiplos de `m` con longitud `n`. */
void calc_multiples(int arr[], int m, int n);

/* Permite calcular el multiplo de `m`
inmediatamente superior al valor de `n` */
int calc_next_multiple(int m, int n);

/* Permite insertar `value` en el primer
elemento con el valor -1 en `arr` (array
de int), para lo cual `arr` debe ser definido
previamente con todos los valores de sus
posiciones en -1. Se debe indicar la longitud
maxima del array `arr` y la funcion
retorna la cantidad de numeros enteros que
conteiene (sin contar los -1) */
int beginsert(int arr[], int maxlength, int value);

/* Permite rellenar el array de enteros `arr`
con un valor determinado. Se debe indicar
el tamaño maximo de `arr` y  */
void fill(int arr[], int maxlength, int value);

/* Programa para reemplazar caracteres
de espacio por tabulaciones (o espacios
si no hay mas remedio)  */
int main()
{
  char arr[MAXILGTH];
  int length;

  length = get_input(arr, MAXILGTH);

  detab(arr, MAXILGTH);

  return 0;
}

int detab(char arr[], int maxlength)
{
  /* Numero de paros de tabulacion */
  int tabstops = maxlength / TABSIZE;
  /* Contiene los indices de las
  posiciones dentro del parametro
  `arr` donde deberia ir una tabulacion. */
  int tabs[tabstops];
  /* Array de multiplos de `TABSIZE`
  con longitud tanto como `tabstops` */
  int multiples[tabstops];
  /* Variables de bucles  */
  int i, j, k;
  /* Variables intermedias */
  int m, tabpos, isend;

  fill(tabs, tabstops, -1);

  multiples[0] = 0;
  calc_multiples(&multiples[1], TABSIZE, tabstops);

  isend = 0;

  for (i = 0; isend == 0 && i < tabstops; ++i)
  {
    m = multiples[i];
    tabpos = -1;
    for (j = m + TABSIZE - 1; j >= m; --j)
    {
      if (arr[j] == '\0')
        isend = 1;
      else if (arr[j] != ' ')
        j = m - 1;
      else
        tabpos = j;
    }
    if (tabpos - m < 7)
      beginsert(tabs, tabstops, tabpos);
  }

  /* Leer los indices de tabulaciones */
  for (k = 0; k < tabstops && tabs[k] != -1; ++k)
  {
    printf("%d\n", tabs[k]);
  }

  return i;
}

int get_input(char arr[], int maxlength)
{
  int c, i;
  for (i = 0; i < maxlength - 1 && (c = getchar()) != EOF; ++i)
    arr[i] = c;
  arr[i] = '\0';
  return i + 1;
}

int calc_multiple(int m, int n)
{
  return m * n;
}

void calc_multiples(int arr[], int m, int n)
{
  int i;
  for (i = 0; i < n; ++i)
    arr[i] = calc_multiple(TABSIZE, i + 1);
}

int calc_next_multiple(int m, int n)
{
  int i;

  if (n < m)
    return 1;

  for (i = 2; m * i <= n; ++i)
    ;

  return i;
}

int beginsert(int arr[], int maxlength, int value)
{
  int i, length;

  for (i = 0; i < maxlength && arr[i] != -1; ++i)
    ;
  length = i + 1;
  if (i < maxlength)
    arr[i] = value;
  else
    length = -1;

  return length;
}

void fill(int arr[], int maxlength, int value)
{
  int i;
  for (i = 0; i < maxlength; ++i)
    arr[i] = value;
}