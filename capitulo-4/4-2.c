#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Permite convertir el literal numerico `s` en un double (permite notacion cientiica, ej: 2e2, que es 200.0)*/
double atof(const char s[]);

/* Permite elevar un numero `m` a un numero entero `n`. */
double powto(const double m, const int n);

/* Implementacion de atof pero con notacion cientifica. */
int main()
{
  printf("%f\n", atof("-2.123e6"));
  printf("%f\n", -2.123e6);
  return 0;
}

double atof(const char s[])
{
  double fpart;
  int i, sign, fpdiv, ipart, exp, exps;

  for (i = 0; isspace(s[i]); i++)
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
  for (ipart = 0; isdigit(s[i]); i++)
    ipart = ipart * 10 + (s[i] - '0');
  if (s[i] == '.')
    i++;
  for (fpart = 0.0, fpdiv = 1; isdigit(s[i]); i++, fpdiv *= 10)
    fpart = fpart * 10.0 + (s[i] - '0');
  fpart /= fpdiv;

  /* Calculo de exponente. */
  if (tolower(s[i]) == 'e')
    i++;
  exps = (s[i] == '-') ? -1 : 1;
  if ((s[i] == '+') || (s[i] == '-'))
    i++;
  for (exp = 0; isdigit(s[i]); i++)
    exp = exp * 10 + (s[i] - '0');

  return (((double)ipart + fpart) * sign) *
         powto(10, exp * exps);
}

double powto(const double m, const int n)
{
  double p;
  int i, max;

  max = (n >= 0) ? n : -n;
  for (p = 1, i = 0; i < max; i++)
  {
    if (n > 0)
      p *= m;
    else
      p /= m;
  }

  return p;
  ;
}