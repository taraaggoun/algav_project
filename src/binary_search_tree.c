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

#define BUF_UINT128_LEN_B10 38
static void pretty_rec(bst *t, int depth, int addr) {
    if (bst_is_empty(t)) {
    	print_head(depth, addr);
    	printf("|----N\n");
    	return;
    }
    pretty_rec(t->right, depth + 1, 2 * addr + 1);
    print_head(depth, addr);
    char c = (depth == 0) ? '-' : '|';
    char buf[BUF_UINT128_LEN_B10] = { 0 };
    uint128_to_str(*(t->key), buf, BUF_UINT128_LEN_B10);
    printf("%c----%s\n", c, buf);
    pretty_rec(t->left, depth + 1, 2 * addr);
}

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

bst* bst_create_empty(void) {
	bst *new_bst = calloc(1, sizeof(bst));
	if (new_bst == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc create bst\n");
		exit(EXIT_FAILURE);
	}
	return new_bst;
}

bst* bst_create(uint128_t k, bst *left, bst *right) {
	bst *new_bst = bst_create_empty();
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

void bst_free(bst *t) {
	if (t == NULL)
		return;
	bst_free(t->left);
	bst_free(t->right);
	free(t->key);
	free(t);
}

bool bst_is_empty(bst *t) {
	return t == NULL || t->key == NULL;
}

bst* bst_max(bst *t) {
	if (bst_is_empty(t)) {
		free(t);
		return NULL;
	}
	if (t->right != NULL)
		return bst_max(t->right);

	return t;
}

bst* bst_min(bst *t) {
	if (bst_is_empty(t)) {
		free(t);
		return NULL;
	}
	if (t->left != NULL)
		return bst_max(t->left);

	return t;
}

bool is_bst(bst *t) {
	if (bst_is_empty(t) || is_bst_leaf(t))
		return true;
	uint128_t *max = bst_max(t)->key;
	uint128_t *min = bst_min(t)->key;
	if (inf(*min, *max))
		return is_bst(t->left) && is_bst(t->right);
	return false;
}

bst* bst_add(uint128_t k, bst *t) {
	if (bst_is_empty(t)) {
		free(t);
		return bst_create(k, NULL, NULL);
	}
	if (inf(*(t->key), k)) // t->key < k
		t->right = bst_add(k, t->right);

	if(inf(k, *(t->key))) // t->key > k
		t->left = bst_add(k, t->left);

	return t;
}

bst* bst_supp(bst *t, uint128_t k) {
	if (bst_is_empty(t))
		return NULL;

	if (inf(k, *(t->key))) // k < t->key
		t->left = bst_supp(t->left, k);

	if (inf(*(t->key), k) == true) // k > t->key
		t->right = bst_supp(t->right, k);
	
	bool egl = eg(*(t->key), k);
	if (egl && is_bst_leaf(t)) {
		free(t);
		return NULL;
	}
	if (egl && bst_is_empty(t->left)) {
		bst *tmp = t->right;
		free(t);
		return tmp;
	}
	if (egl && bst_is_empty(t->right)) {
		bst *tmp = t->left;
		free(t);
		return tmp;
	}
	if (egl) {
		bst *tmp = bst_max(t->left);
		*(t->key) = *(tmp->key);
		*(tmp->key) = k;
		t->left = bst_supp(t->left, k);
		return t;
	}
	return t;
}

bst* bst_search(bst *t, uint128_t k) {
	if (bst_is_empty(t)) {
		free(t);
		return NULL;
	}
	if (eg(*(t->key), k)) // t->key == k
		return t;

	else if(inf(*(t->key), k)) // t->key < k
		return bst_search(t->right, k);
	else // t->key > k
		return bst_search(t->left, k);
}

void bst_print(bst *t) {
    pretty_rec(t, 0, 0);
}

/* -------------------------------------------------------------------------- */
