#include <stdio.h>

/* Max length for literal strings. */
#define MAXS (1U << 7)

/* Prints a integer number. */
static void printd(int n);

/* Saves the literal representacion of `n` inside `s`. */
static void itoa(int n, char s[]);

/* Solucion recursiva al programa de representacion literal de un numero entero. */
int main()
{
  char digit[MAXS];
  int n;

  n = 1024;
  itoa(n, digit);
  printf("%s\n", digit);

  n = 2048;
  itoa(n, digit);
  printf("%s\n", digit);

  return 0;
}

static void itoa(int n, char s[])
{
  static int i = 0; // Indice de pila recursiva
  static int r = 0; // Profundidad de la pila recursiva

  if (i == 0 && n < 0)
  {
    s[i] = '-';
    n *= -1;
  }
  if (n / 10)
  {
    r++;
    itoa(n / 10, s);
  }

  s[i] = n % 10 + '0';
  /* Handling max length. */
  if (i < MAXS - 1)
    i++;
  s[i] = '\0';

  if (r == i - 1)
    r = i = 0;
}
