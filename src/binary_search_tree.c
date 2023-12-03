/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/binary_search_tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

/**
 * Renvoie si b est une feuille
*/
static bool is_bst_leaf(bst *t) {
	return t->left == NULL && t->right == NULL;
}

/**
 * Fonctions d'affichage
*/
static void print_head(int depth, int addr) {
    if (depth > 1) {
	int pre = addr / 2;
	print_head(depth - 1, pre);
	printf("%s", (pre % 2) != (addr % 2) ? "|    " : "     ");
	return;
    }
    if (depth == 1)
	printf ("     ");
}

static void pretty_rec(bst *t, int depth, int addr) {
    if (t == NULL) {
	print_head(depth, addr);
	printf("|----N\n");
	return;
    }
    pretty_rec(t->right, depth + 1, 2 * addr + 1);
    print_head(depth, addr);
    char c = (depth == 0) ? '-' : '|';
    printf("%c----%d\n", c, t->key);
    pretty_rec(t->left, depth + 1, 2 * addr);
}

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

bst* create_bst_empty(void) {
	bst *new_bst = calloc(1, sizeof(bst));
	if (new_bst == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc create bst\n");
		exit(EXIT_FAILURE);
	}
	return new_bst;
}

bst* create_bst(uint128_t k, bst *left, bst *right) {
	bst *new_bst = create_bst_empty();
	new_bst->key = calloc(1, sizeof(uint128_t));
	if (new_bst->key == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc create bst key\n");
		exit(EXIT_FAILURE);
	}
	*(new_bst->key) = k;
	new_bst->left = left;
	new_bst->right = right;
	return new_bst;
}

void free_bst(bst *t) {
	if (t == NULL)
		return;
	free_bst(t->left);
	free_bst(t->right);
	free(t->key);
	free(t);
}

bool is_bst_empty(bst *t) {
	return t == NULL || t->key == NULL;
}

bst* max_bst(bst *t) {
	if (is_bst_empty(t)) {
		free(t);
		return NULL;
	}
	if (t->right != NULL)
		return max_bst(t->right);

	return t;
}

bst* min_bst(bst *t) {
	if (is_bst_empty(t)) {
		free(t);
		return NULL;
	}
	if (t->left != NULL)
		return max_bst(t->left);

	return t;
}

bool is_bst(bst *t) {
	if (is_bst_empty(t) || is_bst_leaf(t))
		return true;
	uint128_t *max = max_bst(t)->key;
	uint128_t *min = min_bst(t)->key;
	if (inf(*min, *max))
		return is_bst(t->left) && is_bst(t->right);
	return false;
}

bst* add_bst(uint128_t k, bst *t) {
	if (is_bst_empty(t)) {
		free(t);
		return create_bst(k, NULL, NULL);
	}
	if (inf(*(t->key), k)) // t->key < k
		t->right = add_bst(k, t->right);

	if(inf(k, *(t->key))) // t->key > k
		t->left = add_bst(k, t->left);

	return t;
}

bst* supp_bst(bst *t, uint128_t k) {
	if (is_bst_empty(t))
		return NULL;

	if (inf(k, *(t->key))) // k < t->key
		t->left = supp_bst(t->left, k);

	if (inf(*(t->key), k) == true) // k > t->key
		t->right = supp_bst(t->right, k);
	// k == t->key
	if (is_bst_leaf(t)) {
		free_bst(t);
		return NULL;
	}
	if (is_bst_empty(t->left)) {
		bst *tmp = t->right;
		free_bst(t);
		return tmp;
	}
	if (is_bst_empty(t->right)) {
		bst *tmp = t->left;
		free_bst(t);
		return tmp;
	}
	// Il existe un fils gauche et un fils droit
	bst *tmp = max_bst(t->left);
	*(t->key) = *(tmp->key);
	*(tmp->key) = k;
	t->left = supp_bst(t->left, k);
	return t;
}

bst* search_bst(bst *t, uint128_t k) {
	if (is_bst_empty(t)) {
		free(t);
		return NULL;
	}
	if (eg(*(t->key), k)) // t->key == k
		return t;

	else if(inf(*(t->key), k)) // t->key < k
		return search_bst(t->right, k);
	else // t->key > k
		return search_bst(t->left, k);
}

void print_bst(bst *t) {
    pretty_rec(t, 0, 0);
}

/* -------------------------------------------------------------------------- */