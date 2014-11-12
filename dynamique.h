
#ifndef __DYNAMIQUE_H__
#define __DYNAMIQUE_H__

#include <stdint.h>

struct liste_chemin;

struct liste_chemin {
	char * id;
	double cout;

	uint32_t level;
	uint32_t last_node_seen;
	struct liste_chemin ** next;
};

//double recur_opti(struct liste_chemin *iter, uint8_t n, double *min, char* choix);
void my_itoa (uint8_t i, char * c);
void dynamique_recursif (struct liste_chemin *PCC, uint8_t n);
void enum_dynamique (uint8_t n);

#endif /* __DYNAMIQUE_H__ */
