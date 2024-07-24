#include <stdio.h>

int truncated_fahr_to_cel(int fahr)
{
  return 5 * (fahr - 32) / 9;
}

float fahr_to_cel(float fahr)
{
  return (5.0 / 9.0) * (fahr - 32.0);
}

float cel_to_fahr(float cel)
{
  return ((9.0 / 5.0) * cel) + 32.0;
}

void print_truncated_fahr_to_cel(int min, int max, int step)
{
  int fahr = min, cel;
  printf("Fahr\tCel\n");
  while (fahr <= max)
  {
    cel = truncated_fahr_to_cel(fahr);
    printf("%3d\t%3d\n", fahr, cel);
    fahr += step;
  }
}

void print_fahr_to_cel(int min, int max, int step)
{
  float fahr, cel;
  fahr = min;

  printf("Fahr\tCel\n");
  while (fahr <= max)
  {
    cel = fahr_to_cel(fahr);
    printf("%3.0f\t%5.1f\n", fahr, cel);
    fahr += step;
  }
}

void print_cel_to_fahr(int min, int max, int step)
{
  float cel, fahr;
  cel = min;

  printf("Cel\tFahr\n");
  while (cel <= max)
  {
    fahr = cel_to_fahr(cel);
    printf("%3.0f\t%4.0f\n", cel, fahr);
    cel += step;
  }
}

int main()
{
  print_fahr_to_cel(0, 300, 20);
  print_cel_to_fahr(0, 300, 20);

  print_truncated_fahr_to_cel(0, 500, 50);
  return 0;
}