#include <stdio.h>

#define ABUFFSIZE (1U << 13)

/* Asigna un blque de memoria. */
char *alloc(int size);

/* Libera el bloque de memoria correspondiente con el puntero. */
void afree(char *p);

/* Alocador de memoria de pila. */
int main()
{
  char *first = alloc(32);
  char *seccond = alloc(16);
  char *third = alloc(24);

  for (char *i = third; i < third + 24; i++)
    printf("%d\n", *(i));

  afree(first);

  return 0;
}

static char allocbuff[ABUFFSIZE];
static char *allocp = allocbuff;

char *alloc(int size)
{
  if (allocbuff + ABUFFSIZE - allocp >= size)
  {
    allocp += size;
    return allocp - size;
  }
  return 0;
}

void afree(char *p)
{
  if (p >= allocbuff && p < allocp)
    allocp = p;
}