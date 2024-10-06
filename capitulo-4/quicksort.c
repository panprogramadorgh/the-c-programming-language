#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum order
{
  ASC,
  DESC,
};

/* Permite ordenar un array numerico. */
void quicksort(int arr[], int from, int to, enum order o);

/* Rellena el array `arr` con numeros aleatorios (1 - 100) */
void rfill(int arr[], int max);

/* Implementacion propia de quicksort. */
int main()
{
  int size = 128;
  int *digits = (int *)malloc(sizeof(int) * size);
  int i;

  rfill(digits, size);

  quicksort(digits, 0, size, ASC);
  for (i = 0; i < size; i++)
    printf("%d,\n", digits[i]);

  return 0;
}

void quicksort(int arr[], int from, int to, enum order o)
{
  if (from >= to)
    return;

  int pivot = arr[from];
  int bigger[to - from], bi = 0;
  int smaller[to - from], si = 0;

  for (int i = from + 1; i < to; i++)
    if (arr[i] >= pivot)
      bigger[bi++] = arr[i];
    else
      smaller[si++] = arr[i];

  for (int i = 0; i < si; i++)
    arr[from + i + (o == ASC ? 0 : bi)] = smaller[i];
  arr[from + (o == ASC ? si : bi)] = pivot;
  for (int i = 0; i < bi; i++)
    arr[from + i + (o == ASC ? si + 1 : 0)] = bigger[i];

  quicksort(arr, from, from + (o == ASC ? si : bi), o);
  quicksort(arr, from + (o == ASC ? si + 1 : bi + 1), to, o);
}

void rfill(int arr[], int max)
{
  int n;

  srand(time(NULL));
  for (int i = 0; i < max; i++)
  {
    n = rand() % 100;
    arr[i] = n;
  }
}