#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef GENERATEUR_CONNEXE_H_INCLUDED
#define GENERATEUR_CONNEXE_H_INCLUDED

typedef struct {
  int comp;
  int next;
}connect;

void graphe_connexe(double** couts, double** points, int n);

#endif // GENERATEUR_CONNEXE_H_INCLUDED
