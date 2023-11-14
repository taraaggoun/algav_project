#include "uint128.h"

struct  noeud_uint128{
	uint128_t valeur;
	struct arbre_binaire *fils_gauche;
	struct arbre_binaire *fils_droit;
};

struct arbre_binaire {
	struct noeud_uint128 *racine;
};

struct arbre_binaire* ArbreVide();
void delete_arbre_binaire(struct arbre_binaire *ab);
struct arbre_binaire* ArbreBinaire(uint128_t val, struct arbre_binaire *g, struct arbre_binaire *d);
bool EstVide(struct arbre_binaire *arbre_binaire);