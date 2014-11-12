#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef GENERATEUR_CONNEXE_H_INCLUDED
#define GENERATEUR_CONNEXE_H_INCLUDED

typedef struct{
  int comp;
  int next;
}connect;

double double_rand(int bornes);
void graphe_connexe(double** couts, double** points, int n, double p);

#endif // GENERATEUR_CONNEXE_H_INCLUDED
