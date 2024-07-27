#include <stdio.h>

/* Representa el maximo tamaño del
texto de entrada por llamada a la
funcion `get_detabed_input`.
```c
int main()
{
  char arr[MAXILGTH];

  // Maximo tamaño de texto
  // de entrada = 1024 caracteres
  // (1024 bytes).
  get_detabed_input(arr, MAXILGTH);

  return 0;
}

```
 */
#define MAXILGTH 1024

/* Representa el tamaño de las tabulaciones */
#define TABSIZE 8

/* Representa el caracter que reemplazara
las tabulaciones */
#define TABCHAR '-'

/* Permite obtener texto de la entrada
estandar reemplazando las tabulaciones
por cuantos espacios sea necesario para
alcanzar el siguiente paro de tabulacion.
La funcion retorna la longitud del nuevo
texto sin tabulaciones. */
int get_detabed_input(char arr[], int maxlength);

/* Permite calcular multiplos de `m` donde
`n` es el multiplo deseado de `m`. Si `m` = 4
y `n` = 3, el resultado sera 12 porque el tercer
multiplo de 4 es 12. */
int calc_multiple(int m, int n);

/* Permite calcular el multiplo de `m`
inmediatamente superior al valor de `n` */
int calc_next_multiple(int m, int n);

/* Programa para obtener texto en la
entrada estandar con las tabulaciones
reemplazadas con tantos espacios como
sea necesario para llegar al proximo
paro de tabulacion. */
int main()
{
  char arr[MAXILGTH];

  get_detabed_input(arr, MAXILGTH);

  printf("%s\n", arr);

  return 0;
}

int get_detabed_input(char arr[], int maxlength)
{
  int c, i, j, n, m, rspaces;

  for (i = 0; i < maxlength - 1 && (c = getchar()) != EOF; ++i)
  {
    if (c == '\t' || c == '\n')
    {
      n = calc_next_multiple(TABSIZE, i);
      m = calc_multiple(TABSIZE, n);
      rspaces = m - i;

      if (c == '\t' && i > 1 && arr[i - 1] == '\n')
        rspaces = TABSIZE;

      if (rspaces + i <= maxlength - 1)
      {
        for (j = i; j < i + rspaces; ++j)
          if ((j == i + rspaces - 1 && c == '\n') ? 0 : 1)
            arr[j] = TABCHAR;

        if (c == '\n' && rspaces > 0)
          arr[j - 1] = '\n';
        else if (c == '\n')
          arr[j] = '\n';

        i += rspaces - 1;
      }
      else
      {
        i = maxlength - 1;
      }
    }
    else
    {
      arr[i] = c;
    }
  }
  arr[i] = '\0';
  return i + 1;
}

int calc_multiple(int m, int n)
{
  return m * n;
}

int calc_next_multiple(int m, int n)
{
  int i;

  if (n < m)
    return 1;

  for (i = 2; i * m <= n; ++i)
    ;
  return i;
}