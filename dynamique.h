
#ifndef __DYNAMIQUE_H__
#define __DYNAMIQUE_H__

#include <stdint.h>

struct liste_chemin;

struct liste_chemin {
	char * id;
	uint32_t cout;

	uint32_t level;
	struct liste_chemin ** next;
};

void choix_opti(struct liste_chemin *PCC, uint8_t n);
void dynamique_recursif (struct liste_chemin *PCC, uint8_t n);
void enum_dynamique (uint8_t n);

#endif /* __DYNAMIQUE_H__ */
