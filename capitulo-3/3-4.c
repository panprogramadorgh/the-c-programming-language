#include <stdio.h>

/* Determines the maxiumum length for literal strings throughout the programm. */
#define MAX 1024

/* Converts a interger number into a literal string. */
void itoa(int n, char result[]);

/* Reverses a literal string. */
void reverse(char s1[]);

/*
### Explicacion
No es posible transformar el valor -(2^palabra-1) en una constante literal porque implicaria salirse del valor maximo para el rango signed de la palabra al momento de convertir en positivo el numero.

### Ejemplo (bytes):
-128 (1000 0000) -> convertir a positivo -> 128 (cuando el maximo positivo es 127 (0111 1111))

### Solucion:
No intentar convertir el signo de `n` y en su lugar dividir directamente entre 10. Para obtener el ultimo digito de `n` se obtiene el resto de la division con el operador modulo. Se obtendra un resto negativo y se le intercambiara el signo para posteriormente convertirse en un caracter. Se parara de dividir entre 10 `n` cuanado sea igual a 0.
 */
int main()
{
  char digit[MAX];

  itoa(~(~0U >> 1), digit);

  printf("%s\n", digit);

  return 0;
}

void itoa(int n, char result[])
{
  int digit, sign;
  int i;

  sign = 1;
  if (n < 0)
    sign = -1;

  i = 0;
  do
  {
    digit = (sign > 0) ? (n % 10 + '0') : (-(n % 10) + '0');
    result[i++] = digit;
  } while ((n /= 10) != 0);

  if (sign < 0)
    result[i++] = '-';

  result[i] = '\0';

  reverse(result);
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