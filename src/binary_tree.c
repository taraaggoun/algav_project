/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/binary_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

binary_tree* bt_empty(void) {
	binary_tree *bt = calloc(1, sizeof(binary_tree));
	if (bt == NULL) {
		dprintf(STDERR_FILENO, "Erreur malloc ArbreVide\n");
		exit(EXIT_FAILURE);
	}
	return bt;
}

binary_tree* bt_new(tree_value v, type t, binary_tree *l, binary_tree *r) {
	binary_tree *bt = bt_empty();
	bt->val = calloc(1, sizeof(v));
	if (bt->val == NULL) {
		dprintf(STDERR_FILENO, "Erreur malloc ArbreVide\n");
		exit(EXIT_FAILURE);
	}
	memcpy(bt->val, &v, sizeof(v));
	bt->left = l;
	bt->right = r;
	bt->type = t;

	if (bt->left == NULL)
		bt->left = bt_empty();
	if (bt->right == NULL)
		bt->right = bt_empty();

	bt->left->parent = bt;
	bt->right->parent = bt;

	return bt;
}

void bt_free(binary_tree *bt) {
	if (bt->val == NULL) {
		free(bt);
		return;
	}
	bt_free(bt->left);
	bt_free(bt->right);
	free(bt->val);
	bt->val = NULL;
	free(bt);
}

bool bt_is_empty(binary_tree *bt) {
	return bt->val == NULL;
}

/* -------------------------------------------------------------------------- */