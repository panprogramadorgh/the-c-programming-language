#include <stdio.h>
#include <stdlib.h>

// Lector de entrada estandar que almacena una cadena de longitud varialbe
char *input(char *message)
{
  printf("%s", message);

  int index, c;
  char *buffer = (char *)malloc(sizeof(char));

  for (index = 0; (c = getchar()) != '\n'; ++index)
  {
    if (index == 0)
    {
      *buffer = c;
      continue;
    }
    buffer = (char *)realloc(buffer, (index + 1) * sizeof(char));
    *(buffer + index) = c;
  }

  return buffer;
}

// Contador de caracteres de espacio, tabulacion y salto de linea
void char_counter()
{
  int tabs = 0, spaces = 0, lines = 0;
  int c;
  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
      ++tabs;
    else if (c == ' ')
      ++spaces;
    else if (c == '\n')
      ++lines;
  }
  printf("\nChar\tCount\n");
  printf("tab\t%5d\n", tabs);
  printf("space\t%5d\n", spaces);
  printf("line\t%5d\n", lines);
}

// Lee escribir la entrada eliminando exceso de espacios.
void foo_a()
{
  int c, prev;
  c = getchar();
  while (c != EOF)
  {
    if (c == ' ')
    {
      if (prev != ' ')
        putchar(c);
    }
    else
      putchar(c);
    prev = c;
    c = getchar();
  }
}

// Reemplazo de escapes de caracter por su forma literal en una constante de cadena
void foo_b()
{
  int c;
  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
      printf("\\t");
    else if (c == '\b')
      printf("\\b");
    else if (c == '\\')
      printf("\\\\");
    else
      putchar(c);
  }
}

// Contador de palabras con verificacion del caracter previo
void foo_c()
{
  /* Variables locales de
  almacenaje de caracter */
  int c, prevc;

  /* Variables locales
  de conteo de caracteres.
  La variable `t` representa
  la cantidad de cualquier
  caracter que no forma parte
  de una palabra como `\n`,
  ` ` y `\t`. */
  int lines, words, chars;
  lines = words = chars = 0;

  /* Asignacion de variables
  de caracter inicial. `prevc`
  es inicialmente EOF */
  c = getchar();
  prevc = EOF;
  while (c != EOF)
  {
    ++chars;
    if (c == '\n')
      ++lines;
    /* Comprobar que el caracter
    actual no sea transparente y
    que el previo si lo sea.
    De esa manera se confirma la
    nueva palabra. */
    else if ((c != ' ' && c != '\t') && (prevc == EOF || prevc == '\n' || prevc == ' ' || prevc == '\t'))
      ++words;
    prevc = c;
    c = getchar();
  }

  printf("\n    C\t    W\t    L\n");
  printf("%5d\t%5d\t%5d\n", chars, words, lines);
}

// Contador de palabras con verificacion de estado (dentro de palabra || fuera de palabra)
int foo_d()
{
  const int in = 1;
  const int out = 2;

  int lines, words, chars;
  lines = words = chars = 0;

  int c, state;

  state = out;
  while ((c = getchar()) != EOF)
  {
    ++chars;
    if (c == '\n')
      ++lines;
    if (c == ' ' || c == '\t' || c == '\n')
      state = out;
    else if (state == out)
    {
      state = in;
      ++words;
    }
  }

  printf("\n     C\t     W\t     L\n");
  printf("%6d\t%6d\t%6d\n", chars, words, lines);
}

// Imprimir cada palabra en lineas diferentes
void foo_e()
{
  int c;

  while ((c = getchar()) != EOF)
  {
    if (c == ' ' || c == '\t' || c == '\n')
      putchar('\n');
    else
      putchar(c);
  }
}

// Contar el numero de caracteres por grupos: blancos (tabs, spaces y lineas), digitos y otros (alfabeticos).
void foo_f()
{
  int i, nwhite, nother, ndigits[10];
  nwhite = nother = 0;
  for (i = 0; i < 10; ++i)
    ndigits[i] = 0;

  int c;
  while ((c = getchar()) != EOF)
  {
    if (c >= '0' && c <= '9')
      ++ndigits[c - '0'];
    else if (c == ' ' || c == '\n' || c == '\t')
      ++nwhite;
    else
      ++nother;
  }

  printf("\nDigit\tCount\tWhites\tOther\n");
  for (i = 0; i < 10; ++i)
  {
    printf("%1d\t%5d", i, ndigits[i]);
    if (i == 0)
      printf("\t%5d\t%5d\n", nwhite, nother);
    else
      printf("\n");
  }
}

void foo_g()
{
  const int out = 0, in = 1;
  int w = 3, wl[w];
  int c;
  int i, j, gh = 10, state;

  for (i = 0; i < w; ++i)
  {
    state = in;
    wl[i] = 0;
    printf("Word [%d]: ", i);
    while ((c = getchar()) != '\n')
    {
      if (state == in && c != '\t' && c != ' ')
        ++wl[i];
      else
        state = out;
    }
  }

  for (j = gh; j > 0; --j)
  {
    for (i = 0; i < w; ++i)
    {
      if (wl[i] >= j)
        putchar('#');
      else
        putchar(' ');
    }
    putchar('\n');
  }
}

void foo_h()
{
  int l = 3, nc[l];
  int c;
  int i, j, gh = 10;

  for (i = 0; i < l; ++i)
  {
    nc[i] = 0;
    printf("Line [%d]: ", i);
    while ((c = getchar()) != '\n')
      ++nc[i];
  }

  for (j = gh; j > 0; --j)
  {
    for (i = 0; i < l; ++i)
    {
      if (nc[i] >= j)
        putchar('#');
      else
        putchar(' ');
    }
    putchar('\n');
  }
}

int main()
{
  foo_h();

  return 0;
}