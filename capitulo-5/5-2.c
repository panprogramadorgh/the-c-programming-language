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
enum signals getfloat(float *n);

/* Permite obtener un caracter de entrada. */
int getch();

/* Permite devolver un caracter a la entrada. */
void ungetch(int c);

/* Ejercicio 5-1 */
int main()
{
  float numbers[100];
  int len;

  for (len = 0; len < 100 && (getfloat(&numbers[len])) != END; len++)
    ;

  for (int i = 0; i < len; i++)
    printf("%f\t", numbers[i]);
  putchar('\n');

  return 0;
}

enum signals getfloat(float *n)
{
  char ipartlit[MAXS];
  char fpartlit[MAXS];

  int i, j, c, sign;
  int ipart;
  float fpart;

  /* Numbers are obtained in literal format. */
  while (isspace(c = getchar()))
    ;

  sign = (c == '-') ? -1 : 1;
  if (c != '+' && c != '-')
    ungetch(c);

  for (i = 0; i < MAXS - 1 && isdigit((c = getch())); i++)
    ipartlit[i] = c;
  ipartlit[i] = '\0';

  if (c == EOF || i == 0)
    return END; // ------------

  if (c == '.')
  {
    for (i = 0; i < MAXS - 1 && isdigit((c = getch())); i++)
      fpartlit[i] = c;
    fpartlit[i] = '\0';

    if (c == EOF)
      return END; // ------------
  }
  else
    fpartlit[0] = '\0';

  while (c != '\n')
    c = getchar();

  /* Processing int part. */
  ipart = j = 0;
  do
  {
    ipart = ipart * 10 + (ipartlit[j] - '0');
  } while (ipartlit[++j] != '\0');

  /* Processing floating part. */
  if (fpartlit[0] != '\0')
  {
    fpart = j = 0;
    do
    {
      fpart = fpart * 10 + (fpartlit[j] - '0');
    } while (fpartlit[++j] != '\0');
    for (int z = 0; z < j; z++)
      fpart /= 10;
  }

  *n = (ipart + fpart) * sign;
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