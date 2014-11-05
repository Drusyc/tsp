#include <stding.h>
#include <stdlib.h>
#include <stdout.h>
#include <math.h>

#include "generateur_connexe.h" 
#include "FloydWarshall.h"

uint32_t *node_seen;

bool is_seen(uint8_t a, uint8_t n) {
        for (uint8_t i = 0; i < n; i++) {
                if (a == node_seen[i]) {
                        return true;
                }//fi
        }//for 
        return false;
}//is_seen()


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
 * Complexité : fact(n)
 *
*/
void tsp_enum (int ** mat, uint8_t nb_node, uint8_t lastNodeSeen) {
        // on parcourt tous les voisins pour chaque noeuds
        for (uint8_t j = 0; j < nb_node; j++) {
                if (mat[i][j] > 0) /*il existe une arête*/{

                        /*  on revient sur le noeud de départ 
                         *  et on vérifie si tous les noeuds sont parcourues */ 
                        if (j == node_seen[0] && all_seen(n)) {
                                printf("Solution : ");
                                for (uint8_t i = 0; i <n; i++) {
                                        printf("%i", node_seen[i]);
                                }//for
                                printf("\n");
                                return;
                        } else if (!is_seen(j,n)) {
                                
                                lastNodeSeen += 1;
                                node_seen[lastNodeSeen] = j;
                                tsp_enum(mat,nb_node,lastNodeSeen);
                                lastNodeSeen -= 1;
                        }//fi 
                }//fi
        }//for
}//tsp_enum()

int main () {

        //Graphe généré sous la forme d'un matrice d'adjacence n*n

        uint8_t n = 4;


        double ** points = (double **) malloc (n*sizeof(double *));
        double ** couts  = (double **) malloc (n*sizeof(double*)) ;
        node_seen = malloc(n*sizeof(uint32_t));

        double p = double_rand(0);

        for (uint8_t i = 0; i < n; i++) {
                couts [i] = malloc(n*sizeof(double));
                points[i] = malloc(2*sizeof(double));
                node_seen[i] = 0;
        }//for

        srand(time(NULL));
        graphe_connexe(couts,points,n,p);
        
        cout = FloydWarshall (cout,n);
        

        //node_seen contient un tour hamiltonien de taille nb_node 
        //forcement, pour visiter chaque noeuds
        //on part du sommet 1
        i = 0;
        tsp_enum(cout, n, 0);

        return 0;
}//main()
