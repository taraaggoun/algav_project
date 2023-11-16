/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/binary_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

binary_tree* ArbreVide(void) {
	binary_tree *bt = calloc(1, sizeof(binary_tree));
	if (bt == NULL) {
		dprintf(STDERR_FILENO, "Erreur malloc ArbreVide\n");
		exit(EXIT_FAILURE);
	}
	return bt;
}

binary_tree* ArbreBinaire(const tree_value v, binary_tree *l, binary_tree *r) {
	binary_tree *bt = ArbreVide();
	bt->val = calloc(1, sizeof(v));
	if (bt->val == NULL) {
		dprintf(STDERR_FILENO, "Erreur malloc ArbreVide\n");
		exit(EXIT_FAILURE);
	}
	memcpy(bt->val, &v, sizeof(v));
	bt->left = l;
	bt->right = r;

	if (bt->left != NULL)
		bt->left->parent = bt;
	if (bt->right != NULL)
		bt->right->parent = bt;

	return bt;
}

void free_binary_tree(binary_tree *bt) {
	if (bt->val == NULL) {
		free(bt);
		return;
	}
	free_binary_tree(bt->left);
	free_binary_tree(bt->right);
	free(bt->val);
	bt->val = NULL;
	free(bt);
}

bool bt_EstVide(binary_tree *bt) {
	return bt->val == NULL;
}

/* -------------------------------------------------------------------------- */