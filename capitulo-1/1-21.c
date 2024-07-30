#include <stdio.h>

/* Representa el maximo tamaño del
texto de entrada por llamada a la
funcion `get_line`.
```c
int main()
{
  char arr[MAXILGTH];

  // Maximo tamaño de texto
  // de entrada = 1024 caracteres
  // (1024 bytes).
  get_line(arr, MAXILGTH);

  return 0;
}

```
 */
#define MAXILGTH 1024

/* Representa la maxima cantidad
de lienas que el programa puede
leer para formatear. */
#define MAXLINES 32

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
void detab(char arr[], int maxlength);

/* Funcion encargada de leer la entrada
estandar y almacenar el resultado en un array.
La funcion devuelve el numero de caracteres
leidos de la entrada. */
int get_line(char arr[], int maxlength);

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
int get_next_multiple(int m, int n);

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

/* Permite desplzar `d` los numeros
enteros de `arr` (array de enteros)
a partir de `index`. Retorna el numero de
elementos afectados en el array. */
int displace_values(int arr[], int maxlength, int index, int d);

/* Permite desplazar `d` posiciones los
elementos de `arr` (array de caracteres)
a partir de `index`. Retorna la cantidad
de elementos afectados. */
int displace_indexes(char arr[], int maxlength, int index, int d);

/* Permite clonar los caracteres de
un array de caracteres `from` en un
segundo array de caracteres `to`. */
void copy(char from[], char to[]);

/* Programa para reemplazar caracteres
de espacio por tabulaciones (o espacios
si no hay mas remedio)  */
int main()
{
  char line[MAXILGTH];
  char lines[MAXILGTH][MAXLINES];
  int i;

  for (i = 0; i < MAXLINES && get_line(line, MAXILGTH) > 1; ++i)
  {
    detab(line, MAXILGTH);
    copy(line, lines[i]);
  }

  for (i = 0; i < MAXLINES; ++i)
  {
    copy(lines[i], line);
    printf("%s\n\n", line);
  }

  return 0;
}

void detab(char arr[], int maxlength)
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
  int m, n, d, tabpos, end;

  multiples[0] = 0;
  calc_multiples(&multiples[1], TABSIZE, tabstops);
  fill(tabs, tabstops, -1);
  end = 0;

  for (i = 0; end == 0 && i < tabstops; ++i)
  {
    m = multiples[i];
    tabpos = -1;
    for (j = m + TABSIZE - 1; end == 0 && j >= m; --j)
    {
      if (arr[j] == '\0')
        end = 1;
      else if (arr[j] != ' ')
        j = -1;
      else
        tabpos = j;
    }
    if (tabpos > -1 && tabpos - m < 7)
      beginsert(tabs, tabstops, tabpos);
  }

  for (k = 0; k < tabstops && tabs[k] != -1; ++k)
  {
    n = get_next_multiple(TABSIZE, tabs[k]);
    m = multiples[n];
    d = m - tabs[k] - 1;
    arr[tabs[k]] = '\t';

    if (tabs[k] + d < maxlength && arr[tabs[k] + 1] != '\0')
    {
      displace_values(tabs, maxlength, k + 1, -d);
      displace_indexes(arr, maxlength, tabs[k] + 1, -d);
      k += d;
    }
  }
}

int get_line(char arr[], int maxlength)
{
  int c, i;
  for (i = 0; i < maxlength - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
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

int get_next_multiple(int m, int n)
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
  int i;

  if (value == -1)
    return -1;

  for (i = 0; i < maxlength && arr[i] != -1; ++i)
    ;
  if (i < maxlength)
  {
    arr[i] = value;
    return i + 1;
  }
  else
    return -1;
}

void fill(int arr[], int maxlength, int value)
{
  int i;
  for (i = 0; i < maxlength; ++i)
    arr[i] = value;
}

int displace_values(int arr[], int maxlength, int index, int d)
{
  int i;
  for (i = index; i < maxlength && arr[i] != -1; ++i)
    arr[i] += d;
  return i;
}

int displace_indexes(char arr[], int maxlength, int index, int d)
{
  /* Array de referencia */
  char rarr[maxlength];
  /* Almacena los elementos afectados */
  int a;
  /* Variables de bucles */
  int i, k, j, o;

  if (index + -d >= maxlength || index + d >= maxlength - 1)
    return -1;

  copy(arr, rarr);

  i = k = 0;

  while (
      (i < maxlength - 1 && k < maxlength) &&
      rarr[k] != '\0')
  {
    if (i == index)
    {
      if (d > 0)
      {
        for (j = 0; j < d; ++j)
          arr[i + j] = ' ';
        i += d;
      }
      else
        k += -d;
    }
    arr[i] = rarr[k];

    ++k;
    ++i;
  }
  arr[i] = '\0';

  for (o = 0; o < maxlength && rarr[o] != '\0'; ++o)
    ;

  a = o - (index + 1);

  return a;
}

void copy(char from[], char to[])
{
  int i;
  for (i = 0; (to[i] = from[i]) != '\0'; ++i)
    ;
}