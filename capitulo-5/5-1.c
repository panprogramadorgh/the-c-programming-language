#include <stdio.h>
#include <ctype.h>

#define MAXS 1024

#define MAXBUFF 1024

enum signals
{
  END = EOF,
  NUMBER
};

/* Obtiene un numero desde la entrada estandar y lo guarda en `n`. */
enum signals getint(int *n);

/* Permite obtener un caracter de entrada. */
int getch();

/* Permite devolver un caracter a la entrada. */
void ungetch(int c);

/* Ejercicio 5-1 */
int main()
{
  int numbers[100];
  int len;

  for (len = 0; len < 100 && (getint(&numbers[len])) != END; len++)
    ;

  for (int i = 0; i < len; i++)
    printf("%d\t", numbers[i]);
  putchar('\n');

  return 0;
}

enum signals getint(int *n)
{
  char digit[MAXS];
  int i, j, c;
  int sign, result;

  while (isspace(c = getchar()))
    ;

  sign = (c == '-') ? -1 : 1;
  if (c != '+' && c != '-')
    ungetch(c);

  for (i = 0; i < MAXS - 1 && isdigit((c = getch())); i++)
    digit[i] = c;
  digit[i] = '\0';

  if (c == EOF || i == 0)
    return END;

  while (c != '\n')
    c = getchar();

  result = j = 0;
  do
  {
    result = result * 10 + (digit[j] - '0');
    j++;
  } while (j < i);

  *n = result * sign;
  return NUMBER;
}

int buffer[MAXBUFF], buffpos = 0;

int getch(void)
{
  if (buffpos > 0)
    return buffer[--buffpos];
  return getchar();
}

void ungetch(int c)
{
  if (buffpos >= MAXBUFF)
  {
    fprintf(stderr, "error: Max input buffer size.");
    return;
  }
  buffer[buffpos++] = c;
}