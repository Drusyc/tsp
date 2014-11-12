#include <float.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <float.h>

/*Algo de branch & bound*/
/*
renvoie le cout min d'un cycle hamiltonien 
G - matrice des couts
res - le chemin qu'on construit
n - taille de graphe
*/
double bb (double ** G, int * res, int n);
