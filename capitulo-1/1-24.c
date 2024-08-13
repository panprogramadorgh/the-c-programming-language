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
#define MAX_LNS 64

/* Permite obtener texto desde
la entrada estadar y guardarlo
dentro del array del array de
caracteres `inp`. Retorna la
cantidad de caracteres introducidos
(contando el ultimo caracter nulo) */
int getinput(char inp[]);

/* Retorna todas las apariciones de la
constante de cadena `tar` dentro de
la constante de cadenaes `from`.
Si `from` sobre sale del limite de
caracteres `MAXINP`, la funcion
retorna 0. */
int count(char from[], char tar[], int offset);

/* Permite obtener un slice de la
constante de cadena `from` y guardarlo en
el array de caracteres `to` (formado
una nueva constante de cadena con
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
constante de cadena `from`.
El parametro `offset` permite indicar
que la busqueda se hara a partir de
cierta posicion dentro de `from`.
La funcion retorna -1 en caso de no
error o bien en caso de no encontrar
el elemento deseado. */
int find(char from[], char tar[], int offset);

/* Permite dividir la constante de cadena
`from` en diferentes trozos, el fin de cada
trozo lo marcan las aparicines de `tar`.
Retorna la cantidad de lineas analizadas. */
int split(char from[], char tar[], char to[MAX_LNS][MAX_LN_LGTH]);

/* Permite eliminar quirurgicamente
una secuencia de caracteres a partir
de un indice determinado dentro de
una constante de cadena.*/
void surgrm(char chain[], int from, int to);

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
char max_line_length_error[] = "Syntax error: max line length exceded.";
char max_lines_error[] = "Syntax error: max lines count exceded.";
char parenthesis_error[] = "Syntax error: missing opening or closing parenthesis.";
char curly_braces_error[] = "Syntax error: missing opening or closing curly braces.";
char brackets_error[] = "Syntax error: not aligned brackets.";
char single_quots_error[] = "Syntax error: malformed char constant.";
char double_quots_error[] = "Syntax error: malformed chain constant.";
char escaped_char_error[] = "Syntax error: malformed escaped char sequence.";
char comment_error[] = "Syntax error: malformed comment sequence.";

/*
## Checkeador de sintaxis basico para codigo fuente de C.

### Objetivos:

1.      Perentesis                              [S]
2.      Llaves                                  [S]
3.      Corchetes alineados                     [S]
4.      Single quots                            [S]
5.      Double quots                            [S]
6.      Secuencias de escape                    [S]
7.      Comentarios                             [S]

Cuando hablamos de corcheste alineados, hablamos de que deben estar en la misma linea.

En el caso de los single quots, se aseume que solamente es valido colocar un solo caracter entre par de single quots, a no ser que el caracter se trate de un caracter escapado como \t.

TODO: Manejar problematicas con inputs largos.
 */
int main()
{
  /* Variables relacionadas con
  la entrada. */
  char text[MAXINP];
  int textlgth;

  /* Almacena cada una de las
  lineas de la constante de cadena
  `text`. */
  char lines[MAX_LNS][MAX_LN_LGTH];
  int noflines;

  /* Almacenan las ocurrencias
  de un caracter determinado. */
  int
      open_parenthesis,
      closed_parenthesis,

      open_curly_braces,
      closed_curly_braces,

      open_brackets,
      closed_brackets,

      double_quots,

      comment_start,
      comment_end;

  int cstart, cend;

  /* Almacenan posiciones de
  caracteres de quots. */
  int quotpos, prevquotpos;

  /* Almacena la posicion del
  caracter de slash descendiente. */
  int desslashpos;

  /* Otras variables. */
  int i;

  /* Obtener entrada. */
  getinput(text);

  /* Comprobar comentarios. */
  comment_start = count(text, "/*", 0);
  comment_end = count(text, "*/", 0);

  if (comment_start < comment_end)
  {
    fprintf(stderr, "%s\n", comment_error);
    return 1;
  }

  /* Eliminar comentarios de la
  evaluacion. */
  cstart = find(text, "/*", 0);
  while (cstart > -1)
  {
    cend = find(text, "*/", cstart);
    if (cend == -1)
      cend = len(text) - 1 - 2;

    surgrm(text, cstart, cend + 2);

    cstart = find(text, "/*", cend);
  }

  printf("%s\n", text);

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

  /* Comprobar corchetes y constantes
  de cadena alineados. */
  noflines = split(text, "\n", lines);
  for (i = 0; i < noflines; ++i)
  {
    open_brackets = count(lines[i], "[", 0);
    closed_brackets = count(lines[i], "]", 0);

    if (open_brackets != closed_brackets)
    {
      fprintf(stderr, "%s\n", brackets_error);
      return 1;
    }

    double_quots = count(lines[i], "\"", 0);
    if (ismultiof(2, double_quots) == 0)
    {
      fprintf(stderr, "%s\n", double_quots_error);
      return 1;
    };
  }

  /* Comprobar constantes de caracter.
  Se asume que solamente puede haber un
  solo caracter en la constante de caracter. */
  prevquotpos = -1;
  quotpos = find(text, "\'", 0);
  while (quotpos > -1)
  {
    if (prevquotpos > -1)
    {
      if (prevquotpos + 3 == quotpos &&
          text[prevquotpos + 1] == '\\')
        ; // Caracter escapado entre single quots.
      else if (prevquotpos + 2 == quotpos)
        ; // Caracter entre single quots.
      else
      {
        fprintf(stderr, "%s\n", single_quots_error);
        return 1;
      }
    }

    prevquotpos = quotpos;
    quotpos = find(text, "\'", prevquotpos + 1);
  }

  /* Comprobar caracteres escapados.
  Solamente pueden estar dentro de
  constantes de caracteres o constantes
  de cadena. */
  desslashpos = find(text, "\\", 0);
  while (desslashpos > -1)
  {
    double_quots = count(text, "\"", desslashpos);
    if (ismultiof(2, double_quots) == 0)
      ; // Dentro de una constante de cadena.
    else if (text[desslashpos - 1] == '\'')
      ; // Dentro de una constante de caracter.
    else
    {
      fprintf(stderr, "%s\n", escaped_char_error);
      return 1;
    }

    desslashpos = find(text, "\\", desslashpos + 1);
  }

  fprintf(stdout, "%s\n", correct_syntax);

  return 0;
}

int getinput(char inp[])
{
  int i, c;

  for (i = 0; (c = getchar()) != EOF && i < MAXINP - 1; ++i)
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

int split(char from[], char tar[], char to[MAX_LNS][MAX_LN_LGTH])
{
  int tarcount, tarpos, prevtarpos;
  int frlgth, tarlgth;
  int line;
  int i;

  prevtarpos = 0;
  frlgth = len(from);
  tarlgth = len(tar);

  if (tarlgth < 2)
    return 0;

  line = 0;
  while ((tarpos = find(from, tar, prevtarpos)) > -1 && line < MAX_LNS)
  {
    for (i = prevtarpos; i < tarpos && (i - prevtarpos) < MAX_LN_LGTH - 1; ++i)
      to[line][i - prevtarpos] = from[i];
    // Supero la maxima longitud de liena.
    if (i == MAX_LN_LGTH)
    {
      fprintf(stderr, "%s\n", max_line_length_error);
      return 1;
    }
    to[line][i - prevtarpos] = '\0';

    prevtarpos = tarpos + tarlgth - 1;
    ++line;
  }

  if (line == MAX_LNS)
  {
    fprintf(stderr, "%s\n", max_lines_error);
    return 1;
  }

  /* Rellena la ultima linea para `to` */
  for (i = prevtarpos; i < frlgth - 1 && (i - prevtarpos) < MAX_LN_LGTH - 1; ++i)
    to[line][i - prevtarpos] = from[i];
  if (i == MAX_LN_LGTH)
  {
    fprintf(stderr, "%s\n", max_line_length_error);
    return 1;
  }

  return line + 1;
}

void surgrm(char chain[], int from, int to)
{
  int chainlgth;
  int i, k;

  chainlgth = len(chain);

  char newchain[chainlgth];

  if (from < 0 || to <= 0 || from >= chainlgth - 1 || to >= chainlgth || from + 2 > to)
    return;

  i = k = 0;
  while (k < chainlgth)
  {
    if (i == from && k == i)
      k = to;

    newchain[i] = chain[k];

    ++i;
    ++k;
  }

  slice(newchain, chain, chainlgth - (to - from), 0);
  chain[chainlgth - (to - from) + 1] = '\0';
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