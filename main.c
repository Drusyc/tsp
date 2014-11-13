#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "generateur_connexe.h"
#include "FloydWarshall.h"
#include "enum.h"
#include "glouton.h"
#include "RechercheLocale.h"
#include "sortirMinLocaux.h"
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
        int * res_chemin    = (int *)malloc( n * sizeof(int));
        int * tmp = (int *)malloc( n * sizeof(int));
        double res_cout;

        clock_t my_clock;



        printf("\n\n--------------- GENERATION ARBRE CONNEXE ---------------");
        //double p = double_rand(0);
        double p = 0.2;

        for(unsigned i = 0;i < n;i++){
                couts[i] =  malloc( n * sizeof(double));
                points[i] =  malloc( 2 * sizeof(double));
                res_chemin[i] = -1;
        }//for()
        
        
        srand (time(NULL));
        graphe_connexe(couts,points, n, p);

        printf("\n\nGraphe généré (avant floydWarshall) pour n = %i et p = %f\n\n", n, p);



        printf("\n\n--------------- GENERATION ARBRE COMPLET ---------------");

        printf("\n\nGraphe après floydWarshall :\n\n");
        floydWarshall(couts, n);
        affiche2D(couts,n);


        printf("\n\n--------------- ALGO ENUMERATION (n<10) ---------------\n");

	if (n<10) {
		my_clock = clock();
		printf("\nCalcul des solutions possibles données par l'algo d'enumeration.. \n\n");
		enumeration(n, couts);
		my_clock = clock() - my_clock;

		printf("Complexité : O(n!) ; Temps d'execution : %f secondes\n\n", 
				((float)my_clock)/CLOCKS_PER_SEC);
	}//fi

        printf("\n\n--------------- ALGO GLOUTON ---------------\n");

        printf("\nCalcul de solution par l'algo glouton.. \n\n");

        my_clock = clock();
        res_cout = glouton(couts, res_chemin, n);
        my_clock = clock() - my_clock;

        printf("Solution : ");
        affiche1D(res_chemin ,n);
        printf("Coût : %0.2f \n", res_cout);

        printf("Complexité : O(n²) ; Temps d'execution : %f secondes\n\n", 
                        ((float)my_clock)/CLOCKS_PER_SEC);
        
        
        for (unsigned i = 0; i < n; i++) {
                tmp[i] = res_chemin[i];
        }//for


        printf("\n\n--------------- ALGO RECHERCHE LOCALE ---------------\n");

        printf("\nCalcul de solution par l'algo recherche locale.. \n\n");

        my_clock = clock();
        RechercheLocale(couts, res_chemin, &res_cout, n);
        my_clock = clock() - my_clock;

        printf("Solution : ");
        affiche1D(res_chemin ,n);
        printf("Coût : %0.2f \n", res_cout);

        printf("Complexité (en moyenne):O(n²) ; Temps d'execution : %f secondes\n\n", 
                        ((float)my_clock)/CLOCKS_PER_SEC);



        printf("\n\n--------------- ALGO RECHERCHE LOCALE + RECUIT SIMULE ---------------\n");

        printf("\nCalcul de solution par l'algo recherche locale en sortant des minimaux locaux.. \n\n");

        my_clock = clock();
	sortirMinLocaux(couts, tmp, &res_cout, n);
        my_clock = clock() - my_clock;

        printf("Solution : ");
        affiche1D(tmp ,n);
        printf("Coût : %0.2f \n", res_cout);

        printf("Complexité (en moyenne): O(n²) ; Temps d'execution : %f secondes\n\n", 
                        ((float)my_clock)/CLOCKS_PER_SEC);


        printf("\n\n--------------- ALGO PROGRAMMATION DYNAMIQUE (n<12) ---------------\n");

	if (n<12) {
		printf("\nCalcul de solution par l'algo de programmation dynamique.. \n\n");

		my_clock = clock();
		enum_dynamique(couts, n, &res_cout);
		my_clock = clock() - my_clock;

		printf("Coût : %0.2f \n", res_cout);

		printf("Complexité : O(n * 2^n) ; Temps d'execution : %f secondes\n\n", 
				((float)my_clock)/CLOCKS_PER_SEC);


	}//fi

        printf("\n\n--------------- ALGO BRANCH & BOUND (n<13) ---------------\n");

	if (n<13) {
		printf("\nCalcul de solution par l'algo de branch & bound.. \n\n");

		my_clock = clock();
		res_cout = bb(couts, res_chemin, n);
		my_clock = clock() - my_clock;

		printf("Solution optimale : ");
		affiche1D(res_chemin ,n);
		printf("Coût : %0.2f \n", res_cout);

		printf("Complexité : n^2*c^n ; Temps d'execution : %f secondes\n\n", 
				((float)my_clock)/CLOCKS_PER_SEC);
	}//fi

	/*        printf("\n\n--------------- ALGO D'APPROXIMATION ---------------\n");


        printf("\nCalcul de solution par l'algo d'approximation.. \n\n");

        my_clock = clock();
        my_clock = clock() - my_clock;

        printf("Solution optimale : .. ");
        printf("Coût : .. \n" );

        printf("Complexité : ?? ; Temps d'execution : %f secondes\n\n", 
                        ((float)my_clock)/CLOCKS_PER_SEC);

	*/     

        for(unsigned i = 0;i < n;i++){
                free(couts[i]);
                free(points[i]);
        }//for
        free(couts);
        free(points);
        free(tmp);
        free(res_chemin);
        return 0;

}//main

