#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "generateur_connexe.h" 
#include "FloydWarshall.h"

/* Tableau stockant les noeuds visités */
/* Indice du tableau node_seen */

double couts[5][5] = 	{{0, 1, 2, 2, 5}, 
			 {1, 0, 1, 1, 2}, 
			 {2, 1, 0, 1, 2}, 
			 {2, 2, 1, 0, 5}, 
			 {5, 2, 2, 5, 0}};


/*
 *
 * C(S,j) = min C(S\{j},i) + l(i,j)
 */
void enum_dynamique (uint8_t n) {

	int8_t *PCC = malloc(n * sizeof(int8_t));
	int8_t *S = malloc (n * sizeof(int8_t));

        for (uint8_t i = 0; i < n; i++) {
		S[i] = -1;
                PCC[i] = couts[0][i];
	}//for

	S[0] = 0;
	uint8_t j = 0;
	for (uint8_t i = 1; i < n; i++) {

	}//for()

	return;
}//enum_dynamique()


int main () {

        //Graphe généré sous la forme d'un matrice d'adjacence n*n

        uint8_t n = 5;
/*
        double ** points = (double **) malloc (n*sizeof(double *));
        double ** couts  = (double **) malloc (n*sizeof(double*)) ;
        node_seen = malloc(n*sizeof(uint32_t));

        double p = double_rand(1);

        for (uint8_t i = 0; i < n; i++) {
                couts [i] = malloc(n*sizeof(double));
                points[i] = malloc(2*sizeof(double));
                node_seen[i] = 0;
        }//for

        srand(time(NULL));
        graphe_connexe(couts,points,n,p);
       
        floydWarshall(couts,n);
*/


        //node_seen contient un tour hamiltonien de taille nb_node 
        //forcement, pour visiter chaque noeuds
        //on part du sommet 1
        enum_dynamique(n);

        return 0;
}//main()
