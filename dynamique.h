
#ifndef __DYNAMIQUE_H__
#define __DYNAMIQUE_H__

#include <stdint.h>

struct liste_chemin;

/*
 *      Chaque noeud contient l'information du chemin précédent
 *      Le noeud 12 le chemin pour y accéder (1) et calcul son coût par rapport à son père
 *      Le père contient le coût C(k-1)
 *      Les noeuds représentes les sous ensembles S l'appel récursif k={0..n-1}
 *
 *      Ex pour n = 4 
 * k=0                  0
 *               /      |      \
 * k=1          1       2       3       
 *            /   \   /   \   /   \   
 * k=2      12    13 21   23 31   32  
 *          |     |   |    |  |    |       
 * k=3     123   132 213  231 312 321
 *
 * 
 */

struct liste_chemin {
	char * id;
	double cout;

	uint32_t level;
	uint32_t last_node_seen;
	struct liste_chemin ** next;
};

void my_itoa (uint8_t i, char * c);
void dynamique_recursif (struct liste_chemin *PCC, uint8_t n);
void enum_dynamique (double ** mat_couts, uint8_t n, double *dyn_min);

#endif /* __DYNAMIQUE_H__ */
