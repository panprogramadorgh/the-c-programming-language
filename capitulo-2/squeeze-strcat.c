#include <stdio.h>

#define MAXLN 1024

/* Permite obtener una linea de
la entrada estandar retornando
la cantidad de caracteres de la
constante literal pasada como
argumento. */
int gline(char inp[]);

/* Permite eliminar un caracter
de una constante literal. */
void squeeze(char s[], int c);

/* Concatena la cadena literal `t`
al final de la cadena literal `s`.
Esta provisto que la constante literal
`t` cabe perfectamente dentro de `s`. */
void my_strcat(char s[], char t[]);

/* Implementacion de funciones
pagina 62 y 63. */
int main()
{
  char line[MAXLN];

  gline(line);
  my_strcat(line, "--dos por uno en burros--");

  printf("%s\n", line);

  return 0;
}

int gline(char inp[])
{
  int i, c;

  for (i = 0; i < MAXLN - 1 && (c = getchar()) != '\n' && c != EOF; i++)
    inp[i] = c;
  inp[i] = '\0';

  return i;
}

void squeeze(char s[], int c)
{
  int i, k;

  i = k = 0;

  while (s[i] != '\0')
  {
    if (s[i] != c)
      s[k++] = s[i];
    i++;
  }
  s[k] = '\0';
}

void my_strcat(char s[], char t[])
{
  int i, k;

  i = k = 0;

  while (s[i] != '\0')
    i++;
  while ((s[i++] = t[k++]) != '\0')
    ;
}