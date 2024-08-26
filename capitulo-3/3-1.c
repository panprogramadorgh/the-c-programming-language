#include <stdio.h>

#define LOW 0
#define HIGH 1

/* Search `x` inside `v` by a
binary search algorithm. Elementos
inside `v` must be shorted in an
ascending way. `n` represents
the max length for `v`. The funcion
returns the position of `x` inside
`v` or -1 if it was not found.  */
int binsearch(int x, int v[], int n);

/* Mayor cantidad de pruebas dentro
de la funcion. Teoricamente mas lento. */
int _binsearch(int x, int v[], int n);

int main()
{
  int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int n = 3;

  printf("%d\n", _binsearch(n, numbers, 10));

  return 0;
}

int binsearch(int x, int v[], int n)
{
  int limits[2];
  int mid, lt;

  limits[LOW] = 0;
  limits[HIGH] = n - 1;

  while (limits[LOW] <= limits[HIGH])
  {
    mid = (limits[LOW] + limits[HIGH]) / 2;

    if (x == v[mid])
      return mid;

    lt = x < v[mid];
    limits[lt] = mid + (lt ? -1 : 1);
  }
  return -1;
}

int _binsearch(int x, int v[], int n)
{
  int low, high, mid;

  low = 0, high = n - 1;

  while (low <= high)
  {
    mid = (low + high) / 2;

    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else
      return mid;
  }

  return -1;
}