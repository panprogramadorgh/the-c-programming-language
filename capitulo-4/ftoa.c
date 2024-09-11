#include <stdio.h>
#include <float.h>

#define PI (float)(3.141596f)

/* Define la longitud maxima para los literal string a lo largo de todo el programa. */
#define MAXSTR 1024 // 1.0 KiB

/* Convierte un numero flotante en su representacion de caracteres. El parametro `maxs` indica la maxima longitud de `s`. Si no se conoce dicha cantidad de ante mano, es necesario primero ejecutar la funcion pasando `NULL` a `s`, obteniendo asi del retorno de la funcion dicha longitud. */
int ftoa(float n, char s[]);

/* Funcion para concatenar las cadenas literales `s1` y `s2` en `r`. */
void concat(char literals[][MAXSTR], unsigned int length, char r[]);

/* Reverses the literal string `s`. */
void reverse(char s[]);

/* Permite copiar el literal string `from` en `to`. */
void copystr(const char from[], char to[]);

/* Returns the length of `s`. */
int strlength(const char s[]);

/* Potencia un numero `n` a la potencia `m`. */
double powto(double n, int m);

/* Funcion temporal para ver todos los caracteres de una cadena literal. */
void print_chars(const char s[])
{
  int i;
  for (i = 0; s[i] != '\0'; i++)
    printf("%c\t%d\n", s[i], s[i]);
}

/* Convertir un numero flotante en su representacion de caracteres. */
int main()
{
  char frep[MAXSTR];

  ftoa(PI, frep);
  printf("%s\n", frep);

  return 0;
}

int ftoa(float n, char s[])
{
  int ipart, ifpart, sign;
  float fpart;

  int count;
  int i;

  sign = (n >= 0) ? 1 : -1;

  ipart = n;
  fpart = (n - ipart) * sign;
  count = FLT_DIG + 1; // Hay que sumar 1 por el caracter de punto.

  if (s == NULL)
  {
    /* Por si solamente se quiere saber la cantidad de caracteres que se emplearan para la representacion. */
    i = 0;
    do
      count++;
    while ((ipart /= 10) != 0);
  }
  else
  {
    /* Para evitar conflictos con las longitudes de las cadenas literales, todas ellas tendran la misma longitud maxima, la cantidad de digitos en la parte entera de `n` + 1 por \0. */
    const int ipartlit = 0, separator = 1, fpartlit = 2;
    char split[3][MAXSTR];
    copystr(".", split[separator]);

    ifpart = fpart * powto(10, FLT_DIG);

    /* Al conocer la longitud de los decimales, es posible ahorrarse el paso de dar la vuelta a la cadena obtenida. */
    for (i = FLT_DIG - 1; i >= 0; i--, ifpart /= 10)
      split[fpartlit][i] = ifpart % 10 + '0';
    split[fpartlit][FLT_DIG] = '\0';

    /* En este caso si es necesario dar la vuelta a la cadena porque no se conoce la cantidad de digitos enteros al momento de operar. */
    i = 0;
    do
    {
      int digit = (sign > 0) ? (ipart % 10) : -(ipart % 10);
      split[ipartlit][i++] = digit + '0';
      count++;
    } while ((ipart /= 10) != 0);
    if (sign == -1)
      split[ipartlit][i++] = '-';
    split[ipartlit][i] = '\0';
    reverse(split[ipartlit]);

    /* Concatenacion de split en la cadena resultante. */
    concat(split, 3, s);
  }

  return count;
}

void concat(char literals[][MAXSTR], unsigned int length, char r[])
{
  int slen;
  int i, j, k;

  k = 0;
  for (i = 0; (k < MAXSTR - 1) && (i < length); i++)
  {
    slen = strlength(literals[i]);
    for (j = 0; (k < MAXSTR - 1) && (j < slen); j++, k++)
      r[k] = literals[i][j];
  }
  r[k] = '\0';
}

void reverse(char s[])
{
  int c;
  int i, j;
  for (j = 0; s[j] != '\0'; j++)
    ;
  for (i = 0, j--; i < j; i++, j--)
    c = s[i], s[i] = s[j], s[j] = c;
}

void copystr(const char from[], char to[])
{
  int i;
  for (i = 0; (i < MAXSTR - 1) && (from[i] != '\0'); i++)
    to[i] = from[i];
  to[i] = '\0';
}

int strlength(const char s[])
{
  int i;
  for (i = 0; s[i] != '\0'; i++)
    ;
  return i;
}

double powto(double n, int m)
{
  double p;
  int rsign;
  unsigned int i, um;

  if (m == 0)
    return 1;

  p = 1;
  um = (m > 0) ? m : -m;
  rsign = (m > 0) ? 1 : ((m % 2 == 0) ? 1 : -1);

  for (i = 0; i < um; i++)
    p *= n;

  return p * rsign;
}
