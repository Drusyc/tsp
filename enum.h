#ifndef __ENUM_H_
#define __ENUM_H_ 

#include <stdint.h>
#include <stdbool.h>



/*
 * Fonction renvoyant vrai si un sommet a déjà été visité
 */
bool is_seen(uint8_t a, uint8_t n);

/*
 * Fonction renvoyant vrai si tous les noeuds ont été visités
 */
bool all_seen (uint8_t n);

/*
 *
 * Enumeration de toutes les solutions possibles d'un graphe G complet.
 * Complexité : fact(n)
 *
*/
void tsp_enum (double ** mat, uint8_t nb_node, uint8_t lastNodeSeen);

#endif /*__ENUM_H_*/
