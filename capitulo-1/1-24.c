#include <stdio.h>
#include <stdlib.h>

/* Referencia la maxima cantidad
en bytes que se puede obtener desde
la entrada estandar antes de que
se corte el stream de lectura. */
#define MAXINP 1024

/* Referencia la maxima cantidad
de caracteres por lina que ha de
tener el programa de C a analizar. */
#define MAX_LN_LGTH 256

/* Referencia la maxima cantidad
de lineas de codigo fuente C que
puede leer este programa. */
#define MAX_LNS 1024

/* Permite obtener texto desde
la entrada estadar y guardarlo
dentro del array del array de
caracteres `inp`. Retorna la
cantidad de caracteres introducidos
(contando el ultimo caracter nulo) */
int getinput(char inp[], int inplgth);

/* Retorna todas las apariciones de la
constante de caracter `tar` dentro de
la constante de caracteres `from`. */
int count(char from[], char tar[], int offset);

/* Permite obtener un slice de la
constante de caracter `from` y guardarlo en
el array de caracteres `to` (formado
una nueva constante de caracter con
caracter nulo al final), el cual
se debe indicar su maxima longitud
en `maxto`. El slice comenzara en la
posicion `start` dentro del array
`from` y termina en `start + maxto`. */
void slice(
    char from[],
    char to[],
    int maxto,
    int start);

/* Permite obtener el indice de
la primera aparicion de la constante
de caracter `tar` dentro de la
constante de caracter `from`.
El parametro `offset` permite indicar
que la busqueda se hara a partir de
cierta posicion dentro de `from`. */
int find(char from[], char tar[], int offset);

/* Permite dividir la constante de caracter
`from` en diferentes trozos, el fin de cada
trozo lo marcan las aparicines de `tar`.
Retorna la cantidad de lineas analizadas. */
int split(char from[], char tar[], char to[MAX_LN_LGTH][MAX_LNS]);

/* Compara dos arrays de caracteres
para comprobar si son iguales. Si son
iguales retorna 1 y si no lo son, retorna 0.*/
int compare(char a[], char b[]);

/* Retorna el numero total de
caracteres de la constante de
caracter `from` contando el
ultimo caracter nulo. Se debe
indicar el maximo tamaño del array. */
int len(char from[]);

/* Retorna 1 si `n` es multiplo de `m`. */
int ismultiof(int m, int n);

/* Varibles externas de mensajes. */
char correct_syntax[] = "Syntax is correct, nothing to be worried about.";
char parenthesis_error[] = "Syntax error: missing opening or closing parenthesis.";
char curly_braces_error[] = "Syntax error: missing opening or closing curly braces.";

/*
## Checkeador de sintaxis basico para codigo fuente de C.

### Objetivos:

1.      Perentesis                              [S]
2.      Llaves                                  [S]
3.      Corchetes alineados (en la misma linea) [N]
4.      Single quots                            [N]
5.      Double quots                            [N]
6.      Secuencias de escape (ej. \t)           [N]
7.      Comentarios                             [N]
 */
int main()
{
  char text[MAXINP];
  int
      open_parenthesis,
      closed_parenthesis,

      open_curly_braces,
      closed_curly_braces;

  /* Obtener entrada. */
  getinput(text, MAXINP);

  /* Comprobar parentesis. */
  open_parenthesis = count(text, "(", 0);
  closed_parenthesis = count(text, ")", 0);
  if (open_parenthesis != closed_parenthesis)
  {
    fprintf(stderr, "%s\n", parenthesis_error);
    return 1;
  }

  /* Comprobar llaves. */
  open_curly_braces = count(text, "{", 0);
  closed_curly_braces = count(text, "}", 0);
  if (open_curly_braces != closed_curly_braces)
  {
    fprintf(stderr, "%s\n", curly_braces_error);
    return 1;
  }

  fprintf(stdout, "%s\n", correct_syntax);

  char lines[MAX_LN_LGTH][MAX_LNS];
  int i, n;

  n = split(text, "\n", lines);

  printf("%d\n", n);
  // for (i = 0; i < MAX_LNS; ++i)
  // {
  //   printf("%s\n", lines[i]);
  // }

  return 0;
}

int getinput(char inp[], int inplgth)
{
  int i, c;

  for (i = 0; (c = getchar()) != EOF && i < inplgth - 1; ++i)
    inp[i] = c;
  inp[i] = '\0';

  return i + 1;
}

int count(char from[], char tar[], int offset)
{
  int frlgth = len(from);
  int tarlgth = len(tar);

  /* Proteccion contra desbordamiento
  de pila en array `compare_try`. */
  if (tarlgth > MAXINP)
    return 0;

  char compare_try[tarlgth];
  int i, eq, count;

  count = 0;

  for (i = offset; i + tarlgth < frlgth + 1; ++i)
  {
    slice(from, compare_try, tarlgth, i);
    eq = compare(tar, compare_try);
    if (eq == 1)
      ++count;
  }

  return count;
}

void slice(
    char from[],
    char to[],
    int maxto,
    int start)
{
  int i, endfrom, endto;

  endfrom = len(from);
  endto = start + maxto;

  for (i = start; i < endfrom && i < endto - 1; ++i)
    to[i - start] = from[i];

  to[i - start] = '\0';
}

int find(char from[], char tar[], int offset)
{
  int frlgth = len(from);
  int tarlgth = len(tar);

  /* Proteccion contra desbordamiento
  de memoria de pila. */
  if (tarlgth > MAXINP)
    return -1;

  char compare_try[tarlgth];
  int i, eq, pos;

  pos = -1;

  for (i = offset; i + tarlgth < frlgth && pos == -1; ++i)
  {
    slice(from, compare_try, tarlgth, i);
    eq = compare(tar, compare_try);
    if (eq == 1)
      pos = i;
  }

  return pos;
}

// FIXME: No lee la ultima linea

int split(char from[], char tar[], char to[MAX_LN_LGTH][MAX_LNS])
{
  int tarcount, tarpos, prevtarpos;
  int frlgth, tarlgth;
  // int endswithtar;
  char line;
  int i;

  prevtarpos = 0;
  frlgth = len(from);
  // tarlgth = len(tar);
  // endswithtar = 0;

  // char someslice[tarlgth];

  tarcount = count(from, tar, 0) + 1;

  // slice(from, someslice, tarlgth, frlgth - tarlgth);
  // endswithtar = compare(tar, someslice);

  line = 0;
  tarpos = find(from, tar, prevtarpos);
  do
  {
    for (i = prevtarpos; i < tarpos && i < MAX_LN_LGTH; ++i)
    {
      printf("%d\t%d\n", i - prevtarpos, line);
      // to[i - prevtarpos][line] = from[i];
    }

    prevtarpos = tarpos + 1;
    tarpos = find(from, tar, prevtarpos);

    if (tarpos == -1)
    {
      for (i = prevtarpos; i < frlgth && i < MAX_LN_LGTH; ++i)
      {
        printf("%d\t%d\n", i - prevtarpos, line);
        // to[i - prevtarpos][line] = from[i];
      }
    }

    ++line;
  } while (tarpos > -1 && line < MAX_LNS);

  return tarcount;
}

int compare(char a[], char b[])
{
  int i, length, eq;

  length = len(a);
  if (len(b) != length)
    return 0;

  eq = 1;

  for (i = 0; eq == 1 && i < length; ++i)
  {
    if (a[i] != b[i])
      eq = 0;
  }

  return eq;
}

int len(char from[])
{
  int i;

  for (i = 0; from[i] != '\0'; ++i)
    ;

  return i + 1;
}

int ismultiof(int m, int n)
{
  return n % m == 0;
}