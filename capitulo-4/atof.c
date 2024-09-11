#include <stdio.h>
#include <ctype.h>

/* Convierte el literal numerico `s` en un double. */
double atof(const char s[]);

/* A diferencia de la funcion mostrada en la pagina 89, esta verion de atof soporta numeros double de cualquier tamaño puesto que emplea dos variables por separado para calcular la parte entera y flotante del numero. En la funcion orignal, se acumulan todos los digitos flotantes en la misma variable que en la de los enteros (pudiendo causar desbordamiento al sobre pasar el maximo numero de digitos enteros soportado por un double) y luego se aplica una division. */
int main()
{
  printf("%lf\n", atof("             3.141596"));

  return 0;
}

double atof(const char s[])
{
  long int ipart;
  double fpart, divisor;
  int i, sign;

  for (i = 0; isspace(s[i]); i++)
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
  for (ipart = 0L; isdigit(s[i]); i++)
    ipart = ipart * 10 + (s[i] - '0');
  if (s[i] == '.')
    i++;
  for (fpart = 0.0, divisor = 1; isdigit(s[i]); i++, divisor *= 10)
    fpart = fpart * 10 + (s[i] - '0');
  fpart /= divisor;

  return (ipart + fpart) * sign;
}