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

        unsigned n = atoi(argv[1]);

        double ** points = (double **)malloc( n * sizeof(double*));
        double ** couts  = (double **)malloc( n * sizeof(double*));
        int * res    = (int *)malloc( n * sizeof(int));

        clock_t my_clock;

/*
  int * glouton_res_tab = (int *)malloc(n * sizeof(int));
  int * bb_res_tab = (int *)malloc(n * sizeof(int));
*/


        printf("\n\n--------------- GENERATION ARBRE CONNEXE ---------------");
        //double p = double_rand(0);
        double p = 0.2;

        for(unsigned i = 0;i < n;i++){
                couts[i] =  malloc( n * sizeof(double));
                points[i] =  malloc( 2 * sizeof(double));
                res[i] = -1;
        }//for()
        
        
        srand (time(NULL));
        graphe_connexe(couts,points, n, p);

        printf("\n\nGraphe généré (avant floydWarshall) pour n = %i et p = %f\n\n", n, p);

        affiche2D(couts,n);

        printf("\n\n--------------- GENERATION ARBRE COMPLET ---------------");

        printf("\n\nGraphe après floydWarshall :\n\n");
        floydWarshall(couts, n);
        affiche2D(couts,n);

        printf("\n\n--------------- ALGO ENUMERATION ---------------\n");

        my_clock = clock();
        printf("\nCalcul des solutions possibles données par l'algo d'enumeration.. \n\n");
        enumeration(n, couts);
        my_clock = clock() - my_clock;

        printf("Complexité : O(n!) ; Temps d'execution : %f secondes\n\n", 
                        ((float)my_clock)/CLOCKS_PER_SEC);

        printf("\n\n--------------- ALGO GLOUTON ---------------\n");

        printf("\nCalcul de solution par l'algo glouton.. \n\n");

        my_clock = clock();
        double glouton_res = glouton(couts, res, n);
        my_clock = clock() - my_clock;

        printf("Solution : ");
        affiche1D(res ,n);
        printf("Coût : %0.2f \n", glouton_res);

        printf("Complexité : O(n²) ; Temps d'execution : %f secondes\n\n", 
                        ((float)my_clock)/CLOCKS_PER_SEC);
  /*

  printf("glouton_res %0.2f \n", glouton_res);

  double bb_res = bb(couts, bb_res_tab, n);
  affiche1D(bb_res_tab,n);

  printf("bb_res %0.2f \n", bb_res);
  */
        for(unsigned i = 0;i < n;i++){
                free(couts[i]);
                free(points[i]);
        }//for
         
        free(couts);
        free(points);
        free(res);
        return 0;

}//main

