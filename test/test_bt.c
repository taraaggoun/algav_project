/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/binary_tree.h"

#include <stdio.h>

/* ---------------------------------- MAIN ---------------------------------- */

int main(void) {
	printf("Creation de l'arbre vide \n");
	binary_tree *bt = bt_empty();
	printf("Arbre est vide ? %d\n", bt_is_empty(bt));
	bt_free(bt); // libere la memoire

	tree_value v = { 0 };
	printf("Ajoue d'un element dans l'arbre\n");
	bt = bt_new(v, uint128, bt_empty(), bt_empty());
	printf("Arbre est vide ? %d\n", bt_is_empty(bt));
	bt_free(bt); // libere la memoire

	return 0;
}
/* -------------------------------------------------------------------------- */