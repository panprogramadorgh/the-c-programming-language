#include <stdio.h>

#define INVAINT 1
#define VAINT 0

/*
  Funcion de exponenciacion de exponente natural
*/
size_t pow_number(int m, int n);

/*
  Funcion de de obtencion de numero natural. El limite de digitos se establece en el segundo parametro.
  ```c
  int maxdigits = 6;
  size_t n = getnatural("Numero: ", maxdigits);
  // posibles valores de n: n >= 0 && n <= 999.999
  ```
*/
size_t getnatural(char message[], int dlimit);

/*
  Permite obtener una linea de entrada de stdin y guardarla en el arreglo pasado como primer argumento.
*/
int inputline(char line[], int maxlength);

/*
  Permite copiar los datos de las posiciones de la memoria del array `from` al array `to`.
*/
void copy_char_arr(char from[], char to[]);

/*
  Obtener linea mas larga arbitrariamente largas como sea posible.
*/
int main()
{
  int linelength, longestlinelength, maxlength;
  maxlength = getnatural("Max line length: ", 6);

  char line[maxlength], longestline[maxlength];

  /* Comienza en 1 puesto que el minmo es 1 por el caracter nulo */
  longestlinelength = 1;

  while ((linelength = inputline(line, maxlength)) > 1)
  {
    if (linelength > longestlinelength)
    {
      longestlinelength = linelength;
      copy_char_arr(line, longestline);
    }
  }

  if (longestlinelength > 1)
    printf("%d\t%s\n", longestlinelength, longestline);
  else
    printf("%d\t \n", longestlinelength);

  return 0;
}

size_t pow_number(int m, int n)
{
  size_t p;
  for (p = 1; n > 0; --n)
    p *= m;
  return p;
}

size_t getnatural(char message[], int dlimit)
{
  int c, i, j;
  char state, eachdigit, digits[dlimit];
  size_t total;

  state = VAINT;
  total = 0;

  if (message != NULL)
    printf("%s", message);

  for (i = 0; i < dlimit && state == VAINT && (c = getchar()) != EOF && c != '\n'; ++i)
  {
    if (c >= '0' && c <= '9')
    {
      eachdigit = c - '0';
      digits[i] = eachdigit;
    }
    else
      state = INVAINT;
  }

  if (state == INVAINT)
    return 0;

  for (j = i; j > 0; --j)
  {
    int foo = i - j;
    total += digits[foo] * pow_number(10, j - 1);
  }

  return total;
}

int inputline(char line[], int maxlength)
{
  int c, i;
  for (i = 0; i < maxlength - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;
  line[i] = '\0';
  /*
    La longitud minima es 1, porque cuenta el caracter nulo.
   */
  return i + 1;
}

void copy_char_arr(char from[], char to[])
{
  int i;

  for (i = 0; (to[i] = from[i]) != '\0'; ++i)
    ;
}