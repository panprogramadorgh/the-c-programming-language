#include <stdio.h>
#include <limits.h>

/* Counts 1 bits in `x`. */
unsigned bitcount(unsigned x);

/* Returns if `bit` position
has the value 1 in `x`. */
unsigned isone(unsigned x, unsigned char bit);

/* Allows to parse a character
array representation of a binary
number into a real one in decimal
format. */
unsigned bintoint(const char bin[]);

/*

## Ejercicio 2-9.

En un sistema de números de complemento a dos, `x &= (x-1)` borra el bit 1 de más a la derecha en x. Explique el porqué. Utilice esta observación para escribir una
versión más rápida de bitcount:

Se basa en un principio que dice que si sumas a
un numero x una potencia de 2 (en este caso 2^0,
que es 1), el bit correspondiente a dicha potencia
(si es 2^0, hablamos de 0) vera alternado su valor.

Si contamos la cantidad de veces que hace falta
sumar 2^n entre si hasta llegar a x, obtendremos
un numero fraccionario (siendo dicha parte
fraccionaria el residuo; es decir, todos aquellos
bits menos significativos que n) del cual solamente
nos interesaremos por su parte entera; si hemos
obtenido una cantidad multiplo de 2 (un numero par)
es sinonimo de que el bit n tiene el valor 1 puesto
que es la unica forma de obtener un monto impar
generado a base de sumar 2^n entre si.

Si alternamos el ultimo bit de x, ya sea incrementando o disminuyendo en valor de 2^0, obtendremos una discordancia entre el antiguo
valor de x y el nuevo, resultando en 0 el ultimo bit tras realizar una operacion &.
*/
int main()
{
  unsigned n = bintoint("10101010101"); // 6 bits with 1
  unsigned bits;

  bits = bitcount(n);
  printf("%u\n", bits);

  return 0;
}

unsigned bitcount(unsigned x)
{
  unsigned char i, c;

  for (i = 0; i < __INT_WIDTH__; i++)
    c += isone(x, i);

  return c;
}

unsigned isone(unsigned x, unsigned char bit)
{
  unsigned int nbit = (~(~0 << 1) << bit);
  unsigned int reqnbit = x / nbit;
  return x >= nbit && reqnbit % 2 != 0;
}

unsigned bintoint(const char bin[])
{
  int i, n;
  char c;

  for (i = n = 0; (c = bin[i]) != '\0' && (c == '0' || c == '1'); i++)
    n = n * 2 + (c - '0');

  return n;
}