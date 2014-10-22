#include <stding.h>
#include <stdlib.h>
#include <stdout.h>

uint32_t const nb_node = 10 ;
uint32_t *node_seen;
uint8_t i; // node

        /*
         *
         * Enumeration de toutes les solutions possibles d'un graphe G complet.
         * Complexité : fact(n)
         *
         */
        void tsp_enum (int ** mat) {
                
                // on parcourt tous les voisins pour chaque noeuds
                for (uint8_t j = 0; j < nb_node; j++) {
                        if (mat[i][j] > 0) /*il existe une arête*/{
                                if (j == node_seen[0]) {
                                                
                                }
                        }//fi
                }//for
        }//tsp_enum()

int main () {

        //Graphe généré sous la forme d'un matrice d'adjacence n*n
        

        int mat [5][5] = { 0, 1, 1, 1, 1,
                           1, 0, 1, 1, 1,
                           1, 1, 0, 1, 1,
                           1, 1, 1, 0, 1,
                           1, 1, 1, 1, 0}

        
        //node_seen contient un tour hamiltonien de taille nb_node 
        //forcement, pour visiter chaque noeuds
        node_seen = malloc(sizeof(uint32_t) * nb_node);
        for (uint8_t k = 0; k < nb_node; k ++) {
                node_seen[k] = 0;
        }//init tab

        //on part du sommet 1
        node_seen[0] = 0;
        i = 0;
        tsp_enum(mat);

        return 0;
}//main()
