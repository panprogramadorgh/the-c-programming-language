#include <stdio.h>
#include <string.h>

#define MAX_LINES 1024
#define LINE_LENGTH 128

int readlines(char *lines[LINE_LENGTH], int max);

void writelines(char *lines[LINE_LENGTH], int nlines);

void qsort(char *lines[LINE_LENGTH], int from, int to);

// Almacena punteros al comienzo de todas las lineas.
char *line_ptrs[MAX_LINES];

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

void qsort(char *lines[LINE_LENGTH], int from, int to)
{
  if (from >= to)
    return;

  char *pivot = lines[from];
  char *bigger[to - from], bi = 0;
  char *smaller[to - from], si = 0;

  for (int i = from + 1; i < to; i++)
    if (strcmp(lines[i], pivot) > 0)
      bigger[bi++] = lines[i];
    else
      smaller[si++] = lines[i];

  for (int i = 0; i < si; i++)
    lines[from + i + bi] = smaller[i];
  lines[from + bi] = pivot;
  for (int i = 0; i < bi; i++)
    lines[from + i] = bigger[i];

  qsort(lines, from, from + bi);
  qsort(lines, from + bi + 1, to);
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