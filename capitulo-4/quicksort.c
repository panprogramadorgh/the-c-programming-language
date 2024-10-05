#include <stdio.h>

void sort(int arr[], int from, int to);

/* Implementacion propia de quicksort. */
int main()
{
  int digits[] = {5,
                  4,
                  3,
                  2,
                  1};

  sort(digits, 0, 5);
  for (int i = 0; i < 5; i++)
    printf("%d\n", digits[i]);

  return 0;
}

void sort(int arr[], int from, int to)
{
  if (from >= to)
    return;

  int pivot = arr[from];
  int bigger[to - from], bi = 0;
  int smaller[to - from], si = 0;

  for (int i = from; i < to; i++)
    if (arr[i] >= pivot)
      bigger[bi++] = arr[i];
    else
      smaller[si++] = arr[i];

  for (int i = 0; i < si; i++)
    arr[from + i] = smaller[i];
  for (int i = 0; i < bi; i++)
    arr[from + si + i] = bigger[i];

  sort(arr, from, from + si);
  sort(arr, from + si + 1, from + to);
}
