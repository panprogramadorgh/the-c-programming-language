#include <stdio.h>
#include <ctype.h>

/* Convierte una cadena de hexadecimal
en un numero entero. */
unsigned long int htoi(char hex[]);

/* Permite aberiguar si un caracter
es hexadecimal o no. */
int ishexd(int c);

/* Utilidades de digitos hexadecimales
para tabla de codificion ASII. */
int main()
{
  unsigned long int decimal;

  decimal = htoi("0xFF");
  printf("%ld\n", decimal);

  return 0;
}

unsigned long int htoi(char hex[])
{
  unsigned long int n;
  int a, f, c, d;
  int i;

  if (hex[0] != '0' || (hex[1] != 'x' && hex[1] != 'X'))
    return 0;

  n = 0;

  for (i = 2; hex[i] != '\0' && ishexd(hex[i]); ++i)
  {
    if (isdigit(hex[i]))
    {
      d = hex[i] - '0';
      n = n * 16 + d;
    }
    // Hexadecimal con letras minusculas
    else if (hex[i] > 'F')
    {
      a = 'a';
      f = 'f';
    }
    else
    {
      a = 'A';
      f = 'F';
    }
    for (c = a; c <= f; ++c)
    {
      if (c == hex[i])
      {
        d = c - a + 10;
        n = n * 16 + d;
      }
    }
  }

  return n;
}

int ishexd(int c)
{
  int is;

  is = isdigit(c) ||
       ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));

  return is;
}