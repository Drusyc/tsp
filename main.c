#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "generateur_connexe.h"

void affiche(double ** m, int n){
  for(int i = 0;i < n;i++){ for(int j = 0;j < n;j++)
     printf("%0.2f ", m[i][j]);
    printf("\n");
  }
}

int main (){

  int n = 7;
  double ** points = (double **)malloc( n * sizeof(double*));
  double ** couts = (double **)malloc( n * sizeof(double*));
  
  double p = double_rand(0);
  //double p = 0.2;

  for(int i = 0;i < n;i++){
        couts[i] =  malloc( n * sizeof(double));
        points[i] =  malloc( 2 * sizeof(double));
  }

  srand (time(NULL));
  graphe_connexe(couts,points, n, p);
  affiche(couts,n);
  return 0;

}

