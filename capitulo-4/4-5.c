#include <stdio.h>
#include <math.h>

/* degres to radians. */
double dtor(double deg);

/* Ejercicio 4-5 pagina 98. Algunas utilidades matematicas de math.h. */
int main()
{
  printf("%f\n", sin(dtor(23))); // seno
  printf("%f\n", cos(dtor(23))); // coseno
  printf("%f\n", tan(dtor(23))); // tangente
  return 0;
}

double dtor(double deg)
{
  return deg * M_PI / 180;
}