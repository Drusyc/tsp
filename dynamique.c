#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "dynamique.h"
#include "generateur_connexe.h" 
#include "FloydWarshall.h"

/* Tableau stockant les noeuds visités */
/* Indice du tableau node_seen */

const uint8_t n = 5;

double couts[5][5] = 	{{0, 1, 2, 2, 5}, 
			 {1, 0, 1, 2, 2}, 
			 {2, 1, 0, 9, 2}, 
			 {2, 2, 9, 0, 5}, 
			 {5, 2, 2, 5, 0}};
/*
double couts[4][4] = 	{{0, 1, 2, 5}, 
			 {1, 0, 1, 2}, 
			 {2, 1, 0, 3}, 
			 {5, 2, 3, 0}};
*/
void my_itoa (uint8_t i, char * c) {
	sprintf(c, "%d", i);
}

void free_liste (struct liste_chemin *l, uint8_t n) {
	//TODO free next[0]
	
	if (l == NULL) {
		return;
	} else if (((n-1) - l->level) == 0) {
		free(l->id);
		free(l);
		return;
	} else {
		for (uint8_t i = 0; i < ((n) - l->level); i++) {
			if (l->next != NULL) {
				free_liste(l->next[i],n);
			}//fi
			
		}//for
		free(l);
	}//fi
}//free_liste();

uint32_t recur_opti(struct liste_chemin *iter, uint8_t n, uint32_t *min, char* choix) {
	
	if (iter->level == (unsigned)(n-1)) {
		printf("Return pour ID %s avec cout : %u\n", iter->next[0]->id, iter->next[0]->cout);
		return iter->next[0]->cout; 
	}//fi

	uint32_t tmp;
	for (uint8_t i = 1; i < n - iter->level; i++) {
		tmp = *min;
		printf("Appel pour ID : %s\n", iter->next[i]->id);
		*min = fmin(recur_opti(iter->next[i],n,min,choix), *min);
		if (tmp != *min) {
			printf("new min pour %s\n", iter->next[i]->id);
			strcpy(choix, iter->next[i]->id);
		}//fi
	}//for
	
	return *min;
	
}//recur_opti()


void dynamique_recursif (struct liste_chemin *PCC, uint8_t n) {

	/* n-2 étapes |S| = 3,4..n-1 */
	char * c = malloc (sizeof(char)*2);
	uint8_t nb_child, count_child, last_node;
	count_child = 0;

	struct liste_chemin * iter = PCC;

	struct liste_chemin ** iter_child;
	
	/* Créer les nouveaux sous-ensembles S */
	printf("Pour noeud : %s\n", iter->id);

	nb_child = n - iter->level - 1;
	iter->next = malloc(nb_child * sizeof(struct liste_chemin));	
	iter_child = iter->next;
	for (uint8_t k = 1; k < n ; k++) {
		/* Création d'un point qui n'a pas été encore visité */
		my_itoa(k,c);
		if (strchr(iter->id,c[0]) == NULL) {
			//printf("%i n'est pas dans %s\n", k, iter->id);

			iter_child[++count_child] = malloc(sizeof(struct liste_chemin));
			iter_child[count_child]->level = iter->level + 1;
			iter_child[count_child]->id = malloc
				((iter_child[count_child]->level + 1) * sizeof(char));

			strcpy(iter_child[count_child]->id,iter->id);
			strcat(iter_child[count_child]->id, c);
			printf("\t\tcréation fils : %s",iter_child[count_child]->id);

			//printf("Chemin : %s ", iter_child[count_child]->id);
			last_node = atoi(&(iter->id[(iter_child[count_child]->level)-2]));
			iter_child[count_child]->cout = iter->cout 
						      + couts[last_node][k];
			printf(" avec cout : %i \n", iter_child[count_child]->cout);

			iter_child[count_child]->next = NULL;
			
			dynamique_recursif(iter_child[count_child], n);
		}//fi
	}//init child

	/* Si aucun fils n'a été créé, c'est qu'on est passé par tous les points, rajoutons 0 pour
	 * faire le circuit heulérien */
	if (count_child == 0) {
		iter->next = malloc (sizeof(struct liste_chemin));
		iter_child = iter->next;

		iter_child[0] = malloc(sizeof(struct liste_chemin));
		
		free(c);
		c = "0";
		iter_child[0]->level = n;
		iter_child[0]->id = malloc(iter_child[0]->level + 1 *sizeof(char));
		strcpy(iter_child[0]->id, iter->id);
		strcat(iter_child[0]->id,c);

		last_node = atoi(&(iter->id[(iter_child[0]->level)-2]));
		iter_child[0]->cout = iter->cout + couts[last_node][0];

		iter_child[0]->next = NULL;

		printf("\t\tChemin final : %s avec cout %i \n", iter_child[0]->id, iter_child[0]->cout);
	}//fi
	else {

		free(c);
	}
}//dynamique_recursif

/*
 *
 * C(S,j) = min C(S\{j},i) + l(i,j)
 */
void enum_dynamique (uint8_t n) {

	struct liste_chemin * PCC = malloc(sizeof (struct liste_chemin));
	PCC->id = 0;
	PCC->level = 0;

	PCC->next = malloc(n * sizeof(struct liste_chemin));

	/* Initialisation de C(S,j) avec |S| = 2 */
	struct liste_chemin ** iter = PCC->next;
	for (uint8_t i = 1; i < n; i++) {
		iter[i] 	= malloc(sizeof(struct liste_chemin));
		iter[i]->level 	= 1;
		iter[i]->id	= malloc((iter[i]->level + 1) * sizeof(char));
		/* id va contenir le chemin actuel */
		my_itoa(i,iter[i]->id); //iter[i]->id = string(i);
		iter[i]->cout 	= couts[0][i];
		iter[i]->next 	= NULL;
	}//for

	for (uint8_t i = 1; i < n; i++) {
		dynamique_recursif(iter[i], n);
	}//For

	uint32_t *min = malloc(sizeof(uint32_t));
	*min = 1000;
	char * choix_opti = malloc(sizeof(char) * (n+1)) ;
	for(uint8_t i = 1; i < n - iter[1]->level; i++) {
		*min = recur_opti(iter[i], n, min, choix_opti);
	}//for

	printf("\nmin : %i pour le chemin %s\n", *min,choix_opti);

	free(min);
	free_liste(PCC,n);
	return;
}//enum_dynamique()


int main () {

        //Graphe généré sous la forme d'un matrice d'adjacence n*n

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
