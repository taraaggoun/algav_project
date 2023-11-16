/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/binary_tree.h"

#include <stdio.h>

/* ---------------------------------- MAIN ---------------------------------- */

int main(void) {
	binary_tree *bt = ArbreVide();
	printf("Arbre vide est vide ? %d\n", bt_EstVide(bt));
	free_binary_tree(bt); // libere la memoire

	tree_value v = { 0 };
	bt = ArbreBinaire(v, ArbreVide(), ArbreVide());
	printf("Arbre vide est vide ? %d\n", bt_EstVide(bt));
	free_binary_tree(bt); // libere la memoire

	return 0;
}
/* -------------------------------------------------------------------------- */