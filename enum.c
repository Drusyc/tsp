#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "generateur_connexe.h" 
#include "FloydWarshall.h"

FILE * pFile;

/* Tableau stockant les noeuds visités */
uint32_t *node_seen;
/* Indice du tableau node_seen */
uint8_t k;

/* Nb solutions */
double nb_solutions = 0;

/*
 * Fonction renvoyant vrai si un sommet a déjà été visité
 */
bool is_seen(uint8_t a, uint8_t n) {
        for (uint8_t i = 0; i < n; i++) {
                if (a == node_seen[i]) {
                        return true;
                }//fi
        }//for 
        return false;
}//is_seen()


/*
 * Fonction renvoyant vrai si tous les noeuds ont été visités
 */
bool all_seen (uint8_t n) {
        bool seen;
        for (uint8_t i = 0; i < n; i++) {
                seen = false;
                seen = is_seen(i, n);        
                if (seen == false) {
                        return false;
                }//fi
        }//for()
        return true;
}//all_seen()

/*
 *
 * Enumeration de toutes les solutions possibles d'un graphe G complet.
 * Complexité : fact(n-1)
 *
*/
void tsp_enum (double ** mat, uint8_t nb_node, uint8_t lastNodeSeen) {
        // on parcourt tous les voisins pour chaque noeuds
        uint8_t tmp;
        for (uint8_t j = 0; j < nb_node; j++) {
          /*      printf("%i %i\n", lastNodeSeen, j);
                for (uint8_t i = 0; i<nb_node; i++){
                        printf("%i", node_seen[i]);
                }//for
                printf("\n");*/
                if (mat[lastNodeSeen][j] > 0) /*il existe une arête*/{

                        /*  on revient sur le noeud de départ 
                         *  et on vérifie si tous les noeuds sont parcourues */ 
                        //if (j == node_seen[0] && all_seen(nb_node)) {
                        if (j == node_seen[0] && k == (nb_node-1)) {
                                for (uint8_t i = 0; i <nb_node; i++) {
                                        fprintf(pFile, "%i", node_seen[i]);
                                }//for
                                fprintf(pFile, "0\n");
                                nb_solutions++;
                                return;
                        } else if (!is_seen(j,nb_node)) {
                                
                               
                                //printf("Node : %i\nj : %i\n\n", lastNodeSeen, j);
                                tmp = lastNodeSeen; 
                                lastNodeSeen = j;
                                k += 1;
                                node_seen[k] = j;
                                tsp_enum(mat,nb_node,lastNodeSeen);
                                node_seen[k] = 0;
                                lastNodeSeen = tmp;
                                k -= 1;
                        }//fi 
                }//fi
        }//for
}//tsp_enum()

void enumeration (unsigned n, double ** graph) {
        
        node_seen = malloc(n*sizeof(uint32_t));
        pFile = fopen("enum.txt", "w");

        if (pFile == NULL) {
                printf("Impossible de créer le fichier pour écrire les solutions d'enum\n");
                return;
        }//fi

        for (uint8_t i = 0; i < n; i++) {
                node_seen[i] = 0;
        }//for

        k = 0;
	nb_solutions = 0;
        tsp_enum(graph, n, 0);

        //printf("Solutions écrites dans enum.txt (%7.0f solutions)\n", nb_solutions);
        fclose(pFile);
        free(node_seen);
        return;
}//enumeration()

/*
int main () {

        //Graphe généré sous la forme d'un matrice d'adjacence n*n

        uint8_t n = 5;

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
        //node_seen contient un tour hamiltonien de taille nb_node 
        //forcement, pour visiter chaque noeuds
        //on part du sommet 1
        k = 0;
        tsp_enum(couts, n, 0);

        free(points);
        free(couts);
        free(node_seen);
        return 0;
}//main()
*/
