#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <float.h> //DBL_MAX..

#include "dynamique.h"
#include "generateur_connexe.h" 
#include "FloydWarshall.h"

/* Tableau stockant les noeuds visités */
/* Indice du tableau node_seen */

double ** couts = NULL;

/*
double couts[5][5] = 	{{0, 1, 2, 2, 5}, 
			 {1, 0, 1, 2, 2}, 
			 {2, 1, 0, 9, 2}, 
			 {2, 2, 9, 0, 5}, 
			 {5, 2, 2, 5, 0}};

double couts[4][4] = 	{{0, 1, 2, 5}, 
			 {1, 0, 1, 2}, 
			 {2, 1, 0, 3}, 
			 {5, 2, 3, 0}};
			 */

void my_itoa (uint8_t i, char * c) {
	sprintf(c, "%d", i);
}

void free_liste (struct liste_chemin *l, uint8_t n) {

	if (l == NULL) {
		return;
	} else if (((n-1) - l->level) == 0) {

		free(l->next[0]->id);
		free(l->next[0]);
		free(l->next);
		free(l->id);
		free(l);
		return;
	} else {
		for (uint8_t i = 1; i < ((n) - l->level); i++) {
			free_liste(l->next[i],n);
		}//for
		free(l->next);
		free(l->id);
		free(l);
	}//fi
}//free_liste();

double recur_opti(struct liste_chemin *iter, uint8_t n, double *min, char* choix) {
	
	if (iter->level == (unsigned)(n-1)) {
		return iter->next[0]->cout; 
	}//fi

	double tmp;
	for (uint8_t i = 1; i < n - iter->level; i++) {
		tmp = *min;
		*min = fmin(recur_opti(iter->next[i],n,min,choix), *min);
		if (tmp != *min && iter->next[i]->level == (unsigned)(n-1)) {
			strcpy(choix, iter->next[i]->next[0]->id);
		}//fi
	}//for
	
	return *min;
	
}//recur_opti()


void dynamique_recursif (struct liste_chemin *PCC, uint8_t n) {

	/* n-2 étapes |S| = 3,4..n-1 */
	char * c = malloc (sizeof(char)*5);
	uint8_t nb_child, count_child, last_node;
	count_child = 0;

	struct liste_chemin * iter = PCC;

	struct liste_chemin ** iter_child;
	
	/* Créer les nouveaux sous-ensembles S */
	//printf("Pour noeud : %s\n", iter->id);

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
			//printf("Previous size id : %i\n", strlen(iter->id));
			iter_child[count_child]->id = malloc((strlen(iter->id) + 10) * sizeof(char));

			strcpy(iter_child[count_child]->id,iter->id);
			strcat(iter_child[count_child]->id, c);
			strcat(iter_child[count_child]->id, "->");
			//printf("New size id : %i\n", strlen(iter_child[count_child]->id));
			//printf("\t\tcréation fils : %s",iter_child[count_child]->id);

			//printf("Chemin : %s ", iter_child[count_child]->id);
			//last_node = atoi(&(iter->id[(iter_child[count_child]->level)-2]));
			last_node = iter->last_node_seen;
			iter_child[count_child]->last_node_seen = k;
			iter_child[count_child]->cout = iter->cout 
						      + couts[last_node][k];
			//printf(" avec cout : %i \n", iter_child[count_child]->cout);

			iter_child[count_child]->next = NULL;
			
			dynamique_recursif(iter_child[count_child], n);
		}//fi
	}//init child

	/* Si aucun fils n'a été créé, c'est qu'on est passé par tous les points, rajoutons 0 pour
	 * faire le circuit heulérien */
	if (count_child == 0) {
		iter->next = realloc(iter->next, sizeof(struct liste_chemin));
		iter_child = iter->next;

		iter_child[0] = malloc(sizeof(struct liste_chemin));
		
		free(c);
		c = "0";
		iter_child[0]->level = n;
		iter_child[0]->id = malloc((strlen(iter->id) + 10) *sizeof(char));
		strcpy(iter_child[0]->id, iter->id);
		strcat(iter_child[0]->id,c);

		last_node = iter->last_node_seen;
		iter_child[0]->cout = (float) (iter->cout + couts[last_node][0]);

		iter_child[0]->next = NULL;

		//printf("\t\tChemin final : %s avec cout %i \n", iter_child[0]->id, iter_child[0]->cout);
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
	
        //Graphe généré sous la forme d'un matrice d'adjacence n*n
	
	double ** points = (double **) malloc (n*sizeof(double *));
	double ** main_couts  = (double **) malloc (n*sizeof(double*)) ;

        double p = double_rand(1);

        for (uint8_t i = 0; i < n; i++) {
                main_couts [i] = malloc(n*sizeof(double));
                points[i] = malloc(2*sizeof(double));
        }//for

        srand(time(NULL));
        graphe_connexe(main_couts,points,n,p);
       
        floydWarshall(main_couts,n);

	couts = main_couts;
        for (uint8_t i = 0; i < n; i++) {
		for (uint8_t j = 0; j < n; j++) {
			printf("[%f] ", couts[i][j]);
		}//forj
		printf("\n");
	}//for
        
	struct liste_chemin * PCC = malloc(sizeof (struct liste_chemin));
	PCC->id = 0;
	PCC->level = 0;

	PCC->next = malloc(n * sizeof(struct liste_chemin));

	/* Initialisation de C(S,j) avec |S| = 2 */
	struct liste_chemin ** iter = PCC->next;
	for (uint8_t i = 1; i < n; i++) {
		iter[i] 	= malloc(sizeof(struct liste_chemin));
		iter[i]->level 	= 1;
		iter[i]->id	= malloc(250 * sizeof(char));
		/* id va contenir le chemin actuel */
		my_itoa(i,iter[i]->id); //iter[i]->id = string(i);
		strcat(iter[i]->id, "->");
		iter[i]->last_node_seen = i;
		iter[i]->cout 	= couts[0][i];
		iter[i]->next 	= NULL;
	}//for
	printf("\n");

	for (uint8_t i = 1; i < n; i++) {
		dynamique_recursif(iter[i], n);
	}//For

	double *min = malloc(sizeof(double));
	*min = DBL_MAX;
	char * choix_opti = malloc(sizeof(char) * (3*n)) ;
	for(uint8_t i = 1; i < n - iter[1]->level; i++) {
		*min = recur_opti(iter[i], n, min, choix_opti);
	}//for

	printf("PCC : %s avec un coût de %f\n", choix_opti,*min);

	for (uint8_t i = 0; i < n; i++) {
                //free(main_couts [i]);
                //free(points[i]);
        }//for

	//free(main_couts);
	//free(points);

	free(min);
	free(choix_opti);
	free_liste(PCC,n);
	return;
}//enum_dynamique()


int main () {
	const uint8_t n = 11;
	enum_dynamique(n);
        return 0;
}//main()
