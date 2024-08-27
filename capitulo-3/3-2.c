#include <stdio.h>
#include <string.h>

/* Determines the maximum length for literal strings in the programm.  */
#define MAX 1024

/* Allows to remove `n` chars from `str` starting at `p`. */
void surgrm(char str[], unsigned p, unsigned n);

/* Allows to insert the literal string `insertion` inside `str` starting at `p`.

### Funcionamiento algoritmo:

Al estar haciendo una insercion, logicamente la longitud de la nueva cadena literal sera mayor (o por lo menos igual); es por eso que el primer paso es deducir la longitud de la futura cadena literal (y con ello la posicion del ultimo caracter). Para averiguar cual es la longitud de la nueva cadena literal hay que sumar la longitud de ambas cadenas (a partir de ahora no referiremos a la longitud de la segunda cadena con el nombre `inslgth`). Para obtener la posicion del ultimo caracter (a partir de ahora denominado `endp`), restar en valor de 1 a la nueva longitud obtenida. El segundo paso consiste en clonar cada caracter de posicion `endp - inslgth` en `endp` disminuyendo por cada caracter clonado `endp` en valor de 1. El ultimo caracter a clonar sera el ubicado en `p + inslgth`; valor el cual en algun momento sostendra la variable `endp`, puesto que por cada caracter es disniuida en valor de 1. */
void surgins(char str[], int p, const char ins[]);

/* Allows to convert spaced characters like \t and \n from `s` while copies the new string literal into `t`.  */
void scape(const char s[], char t[]);

/* TODO: Allows to convert literal scaped character sequences from `s` into real scaped characters and copies the new literal string into `t`. */
void unscape(const char s[], char t[]);

int main()
{
  char from[MAX] = "hola-\n-adios-\t-hola-\b-\?-\\-adios";
  char to[MAX];

  scape(from, to);

  printf("%s\n", to);

  return 0;
}

void surgrm(char str[], unsigned p, unsigned n)
{
  int i, k;

  i = k = 0;

  while (str[i] != '\0')
  {
    if (i < p || i > p + n)
      str[k++] = str[i];
    i++;
  }
  str[k] = '\0';
}

void surgins(char str[], int p, const char ins[])
{
  int slgth, inslgth;
  int endp;

  slgth = strlen(str), inslgth = strlen(ins);
  endp = slgth + inslgth - 1;

  if (endp >= MAX - 1)
    endp -= ((MAX - 1) - 1) - endp;

  str[endp + 1] = '\0';

  while (endp >= p)
  {
    if (endp < p + inslgth)
    {
      str[endp] = ins[endp - p];
    }
    else
      str[endp] = str[endp - inslgth];
    endp--;
  }
}

void scape(const char s[], char t[])
{
  int c, i, k;

  k = i = 0;

  while (i < MAX - 1 && (c = s[i]) != '\0')
  {
    switch (c)
    {
    case '\n':
      t[k++] = '\\';
      t[k] = 'n';
      break;
    case '\t':
      t[k++] = '\\';
      t[k] = 't';
      break;
    case '\b':
      t[k++] = '\\';
      t[k] = 'b';
      break;
    case '\r':
      t[k++] = '\\';
      t[k] = 'r';
      break;
    case '\'':
      t[k++] = '\\';
      t[k] = '\'';
      break;
    case '\"':
      t[k++] = '\\';
      t[k] = '\"';
      break;
    case '\?':
      t[k++] = '\\';
      t[k] = '\?';
      break;
    case '\\':
      t[k++] = '\\';
      t[k] = '\\';
      break;
    default:
      t[k] = c;
      break;
    }

    i++;
    k++;
  }
  t[k] = '\0';
}