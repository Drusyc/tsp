#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "generateur_connexe.h"
#include "glouton.h"
#include "bb.h"
#include "FloydWarshall.h"

void affiche2D(double ** m, int n){
  for(int i = 0;i < n;i++){ for(int j = 0;j < n;j++)
     printf("%0.3f ", m[i][j]);
    printf("\n");
  }
}

void affiche1D(int * m, int n){
  for(int i = 0;i < n;i++) 
     printf("%d ", m[i]);
  
  printf("\n");
  
}

int main (){

  int n = 5;
  double ** points = (double **)malloc( n * sizeof(double*));
  double ** couts = (double **)malloc( n * sizeof(double*));
  int * glouton_res_tab = (int *)malloc(n * sizeof(int));
  int * bb_res_tab = (int *)malloc(n * sizeof(int));

  //double p = double_rand(0);
  double p = 0.2;

  for(int i = 0;i < n;i++){
        couts[i] =  malloc( n * sizeof(double));
        points[i] =  malloc( 2 * sizeof(double));
	glouton_res_tab[i] = -1;
	bb_res_tab[i] = -1;
  }

  srand (time(NULL));
  graphe_connexe(couts,points, n, p);
  affiche2D(couts,n);

  printf("\n");

  floydWarshall(couts, n);
  affiche2D(couts,n);

   printf("\n");

  double glouton_res = glouton(couts, glouton_res_tab, n);
  affiche1D(glouton_res_tab,n);

  printf("glouton_res %0.2f \n", glouton_res);

  /*double bb_res = bb(couts, bb_res_tab, n);
  affiche1D(bb_res_tab,n);

  printf("bb_res %0.2f \n", bb_res);*/

  return 0;

}

