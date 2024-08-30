#include <string.h>
#include "surgstr.h"

void surgrm(char str[], unsigned p, unsigned n)
{
  int i, k;

  i = k = 0;

  while (str[i] != '\0')
  {
    if (i < p || i > p + n)
      str[k++] = str[i];
    i++;
  }
  str[k] = '\0';
}

void surgins(char str[], int p, const char ins[])
{
  int slgth, inslgth;
  int endp;

  slgth = strlen(str), inslgth = strlen(ins);
  endp = slgth + inslgth - 1;

  if (endp >= MAX - 1)
    endp -= ((MAX - 1) - 1) - endp;

  str[endp + 1] = '\0';

  while (endp >= p)
  {
    if (endp < p + inslgth)
    {
      str[endp] = ins[endp - p];
    }
    else
      str[endp] = str[endp - inslgth];
    endp--;
  }
}