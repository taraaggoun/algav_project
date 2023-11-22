/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/min_heap_tree.h"

#include <stdio.h>

/* ---------------------------------- MAIN ---------------------------------- */

int main(void) {
	printf("Creation du tas vide \n");
	min_heap_tree *mht = mhtree_empty();
	printf("Tas est vide ? %d\n", mhtree_is_empty(mht));
	mhtree_free(mht); // libere la memoire

	tree_value v = { 0 };
	v.u128.i2 = 12;
	printf("Ajoue d'un element (12) dans l'arbre\n");
	mht = mhtree_empty();
	Ajout(v, uint128, mht);
	printf("Tas est vide ? %d\n", mhtree_is_empty(mht));
	printf("Valeur de la racine: %lu\n", v.u128.i2);
	printf("Suppression d'un element dans l'arbre\n");
	SupprMin(mht);
	printf("Tas est vide ? %d\n", mhtree_is_empty(mht));

	mhtree_free(mht); // libere la memoire


	return 0;
}

/* -------------------------------------------------------------------------- */
