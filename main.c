#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "generateur_connexe.h"
#include "FloydWarshall.h"
#include "enum.h"
#include "glouton.h"
#include "dynamique.h"
#include "bb.h"

void affiche2D(double ** m, int n){
        for(int i = 0;i < n;i++){ 
                for(int j = 0;j < n;j++)
                        printf("[%0.3f] \t ", m[i][j]);
                printf("\n");
        }//for
}

void affiche1D(int * m, int n){
  for(int i = 0;i < n;i++) 
     printf("%d ", m[i]);
  
  printf("\n");
  
}

int main (int argc, char* argv[]){

        if (argc != 2) {
                printf("Entrer une valeur de n\n");
                return -1;
        }//fi

        int n = atoi(argv[1]);

        double ** points = (double **)malloc( n * sizeof(double*));
        double ** couts  = (double **)malloc( n * sizeof(double*));
        int * res    = (int *)malloc( n * sizeof(int));


/*
  int * glouton_res_tab = (int *)malloc(n * sizeof(int));
  int * bb_res_tab = (int *)malloc(n * sizeof(int));
*/

        //double p = double_rand(0);
        double p = 0.2;

        for(int i = 0;i < n;i++){
                couts[i] =  malloc( n * sizeof(double));
                points[i] =  malloc( 2 * sizeof(double));
                res[i] = -1;
        }//for()
        

        srand (time(NULL));
        graphe_connexe(couts,points, n, p);

        printf("\n\n\nGraphe généré (avant floydWarshall) pour n = %i et p = %f\n\n", n, p);

        affiche2D(couts,n);


        printf("\n\n\nAprès floydWarshall :\n\n");
        floydWarshall(couts, n);
        affiche2D(couts,n);

   printf("\n");
  /*
  double glouton_res = glouton(couts, glouton_res_tab, n);
  affiche1D(glouton_res_tab,n);

  printf("glouton_res %0.2f \n", glouton_res);

  double bb_res = bb(couts, bb_res_tab, n);
  affiche1D(bb_res_tab,n);

  printf("bb_res %0.2f \n", bb_res);
  */

  return 0;

}//main

