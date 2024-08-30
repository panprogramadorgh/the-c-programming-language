#ifndef SURGSTR_H
#define SURGSTR_H

#define MAX 1024

/* Allows to remove `n` chars from `str` starting at `p`. */
void surgrm(char str[], unsigned p, unsigned n);

/* Allows to insert the literal string `insertion` inside `str` starting at `p`.

### Funcionamiento algoritmo:

Al estar haciendo una insercion, logicamente la longitud de la nueva cadena literal sera mayor (o por lo menos igual); es por eso que el primer paso es deducir la longitud de la futura cadena literal (y con ello la posicion del ultimo caracter). Para averiguar cual es la longitud de la nueva cadena literal hay que sumar la longitud de ambas cadenas (a partir de ahora no referiremos a la longitud de la segunda cadena con el nombre `inslgth`). Para obtener la posicion del ultimo caracter (a partir de ahora denominado `endp`), restar en valor de 1 a la nueva longitud obtenida. El segundo paso consiste en clonar cada caracter de posicion `endp - inslgth` en `endp` disminuyendo por cada caracter clonado `endp` en valor de 1. El ultimo caracter a clonar sera el ubicado en `p + inslgth`; valor el cual en algun momento sostendra la variable `endp`, puesto que por cada caracter es disniuida en valor de 1. */
void surgins(char str[], int p, const char ins[]);

#endif