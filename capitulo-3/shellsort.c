#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 1 << 16

/* Shell sort for integers algorithm. */
void shellsort(int v[], unsigned n);

/* Regular integer array sorter function. */
void sort(int v[], unsigned n);

int main()
{
  int numbers[MAX];
  int i;

  for (i = 0; i < MAX; i++)
    numbers[i] = rand() % (MAX);

  shellsort(numbers, MAX);
  for (i--; i >= 0; i--)
    printf("%d\t", numbers[i]);

  return 0;
}

void shellsort(int v[], unsigned n)
{
  int gap, temp, i, j;

  for (gap = n / 2; gap > 0; gap /= 2)
    for (i = gap; i < n; i++)
      for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
      {
        temp = v[j];
        v[j] = v[j + gap];
        v[j + gap] = temp;
      }
}

void sort(int v[], unsigned n)
{
  int temp, j, i;

  if (n < 2)
    return;

  for (j = 0; j < n; j++)
    for (i = 0; i < n - 1; i++)
      if (v[i] > v[i + 1])
      {
        temp = v[i];
        v[i] = v[i + 1];
        v[i + 1] = temp;
      }
}