#include <stdio.h>
#include <ctype.h>

#define MAXS 1024

/* Obtiene un numero desde la entrada estandar y lo guarda en `n`. */
int getint(int *n);

/* Recreacion programa de ejemplo pagina 117 */
int main()
{
  int numbers[100];
  int len;

  for (len = 0; (getint(&numbers[len])) != EOF; len++)
    ;

  for (int i = 0; i < len; i++)
    printf("%d\t", numbers[i]);
  putchar('\n');

  return 0;
}

int getint(int *n)
{
  char digit[MAXS];
  int i, j, c;
  int result;

  for (i = 0; i < MAXS - 1 && isdigit((c = getchar())); i++)
    digit[i] = c;
  digit[i] = '\0';

  if (c == EOF)
    return EOF;

  while (c != '\n')
    c = getchar();

  result = j = 0;
  do
  {
    result = result * 10 + (digit[j] - '0');
    j++;
  } while (j < i);

  *n = result;
  return 0;
}