#include "../include/arbre_binaire.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

struct arbre_binaire* ArbreVide() {
	struct arbre_binaire *ab = malloc(sizeof(struct arbre_binaire));
	if (ab == NULL) {
		dprintf(STDERR_FILENO, "Erreur malloc ArbreVide\n");
		exit(EXIT_FAILURE);		
	}
	ab->racine = NULL;
	return ab;
}

void delete_arbre_binaire(struct arbre_binaire *ab) {
	if (ab->racine->fils_gauche == NULL && ab->racine->fils_droit == NULL) {
		free(ab);
	}
	delete_arbre_binaire(ab->racine->fils_gauche);
	delete_arbre_binaire(ab->racine->fils_droit);
	free(ab);
}

struct arbre_binaire* ArbreBinaire(uint128_t val, struct arbre_binaire *g, struct arbre_binaire *d) {
	struct arbre_binaire *ab = malloc(sizeof(struct arbre_binaire));
	if (ab == NULL) {
		dprintf(STDERR_FILENO, "Erreur malloc ArbreBinaire\n");
		exit(EXIT_FAILURE);
	}
	ab->racine = malloc(sizeof(struct noeud_uint128));
	ab->racine->valeur.i1 = val.i1;
	ab->racine->valeur.i2 = val.i2;
	ab->racine->valeur.i3 = val.i3;
	ab->racine->valeur.i4 = val.i4;
	ab->racine->fils_gauche = g;
	ab->racine->fils_droit  = d;
	
	return ab;
}

bool EstVide(struct arbre_binaire *arbre_binaire) {
	return arbre_binaire->racine == NULL;
}
