#include <stdio.h>
#include <string.h>

#define MAX_LINES 1024
#define LINE_LENGTH 128

int readlines(char *lines[LINE_LENGTH], int max);

void writelines(char *lines[LINE_LENGTH], int nlines);

void qsort(char *lines[LINE_LENGTH], int from, int to);

// Almacena punteros al comienzo de todas las lineas.
char *line_ptrs[MAX_LINES];

// 5-7 Ahora readlines obtiene un arreglo de pila pasado desde main con la peculiaridad de que para el manejo de las lineas se construye un arreglo a punteros de caracteres.
int main()
{
  char lines[MAX_LINES][LINE_LENGTH]; // Asignar memoria de pila
  int nlines = MAX_LINES;
  while (nlines > 0)
    line_ptrs[nlines] = lines[nlines--];

  if ((nlines = readlines(line_ptrs, MAX_LINES)) > 0)
  {
    qsort(line_ptrs, 0, nlines - 1);
    writelines(line_ptrs, nlines);
  }

  return 0;
}

int readlines(char *lines[LINE_LENGTH], int max)
{
  int getln(char *line, int max);

  char line[LINE_LENGTH];
  int line_len, line_index;

  line_index = 0;
  while ((line_len = getln(line, LINE_LENGTH)) > 0)
  {
    strcpy(lines[line_index], line);
    if (++line_index >= max)
      return -1;
  }

  return line_index;
}

void writelines(char *lines[LINE_LENGTH], int nlines)
{
  while (nlines-- > 0)
    printf("%s\n", *lines++);
}

void qsort(char *v[], int left, int right)
{
  int i, last;
  void swap(char *v[], int i, int j);
  if (left >= right) /* no hace nada si el arreglo contiene */
    return;          /* menos de dos elementos */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

int getln(char *line, int max)
{
  int len, c;

  len = 0;
  while ((c = getchar()) != EOF && c != '\n' && len++ < max)
    *line++ = c;
  *line = '\0';

  return len;
}

void swap(char *v[], int i, int j)
{
  char *temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}