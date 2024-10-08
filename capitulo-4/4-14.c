#include <stdio.h>

#define swap(t, x, y) \
  {                   \
    t temp = x;       \
    x = y;            \
    y = temp;         \
  }

int main()
{
  int n1 = 500, n2 = 250;
  swap(int, n1, n2);

  printf("%d\t%d\n", n1, n2);

  return 0;
}