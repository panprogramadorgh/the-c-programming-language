#include <stdio.h>

#define MAX_LENGTH 1000

int get_input_line(char line[], int max_length);

int copy_char_arr(char from[], char to[]);

int main()
{
  int each_line_length;
  char each_line[MAX_LENGTH];
  int longest_line_length = 0;
  char longest_line[MAX_LENGTH];

  int copy_arr_state;

  while ((each_line_length = get_input_line(each_line, MAX_LENGTH)) > 0)
  {
    if (each_line_length > longest_line_length)
    {
      longest_line_length = each_line_length;
      copy_arr_state = copy_char_arr(each_line, longest_line);
      if (copy_arr_state == 0)
      {
        printf("Error due copyng new longest char array");
        return 1;
      }
    }
  }

  if (longest_line_length > 0)
    printf("%s\n", longest_line);

  return 0;
}

/*
  Lee la linea de texto que ingresa el usuario mientras escribe en el arreglo de caracteres pasado como argumento, la funcion retorna la longitud de caracteres que ha sido rellenado el arreglo. Para finalizar la linea de debe enviar al programa un caracter EOF o un salto de linea.
*/
int get_input_line(char line[], int max_length)
{
  int c, i;

  for (i = 0; i < max_length - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;
  line[i] = '\0';

  return i;
}

/*
  Cada dato de las posiciones del array `from` son copiados a las posiciones equivalentes del `to`. Ademas, se supone que ambos arrays son del mismo tamaño. Si el valor retornado por la funcion es 1, quiere decir que todo salio bien; por otra parte, si se obtiene un 0 quiere decir que se fallo en el intento. Un motivo para que la funcion falle es que el tamaño de los arrays sea distinto.
*/
int copy_char_arr(char from[], char to[])
{
  int i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;

  return 1;
}