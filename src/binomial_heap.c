/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/binomial_heap.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

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
static void pretty_rec(binomh *bh, int depth, int addr) {
	if (binomh_is_empty(bh)) {
		print_head(depth, addr);
		printf("|----N\n");
		return;
    	}

	for (size_t i = 0; i < bh->degree/2; i++) {
    	pretty_rec(bh->children[i], depth + 1, 2 * addr + i);
	}

	print_head(depth, addr);
	char c = (depth == 0) ? '-' : '|';
	char buf[BUF_UINT128_LEN_B10] = { 0 };
	uint128_to_str(*(bh->key), buf, BUF_UINT128_LEN_B10);
    	printf("%c----%s\n", c, buf);
	for (size_t i = bh->degree/2; i < bh->degree; i++) {
    		pretty_rec(bh->children[i], depth + 1, 2 * addr + i);
	}
}

static binomh* binomh_copy(binomh *bh, bool more_child) {
	binomh *copy = calloc(1, sizeof(binomh));
	if (copy == NULL) {
		dprintf(STDERR_FILENO, "Erreur copy binomh\n");
		exit(EXIT_FAILURE);
	}
	copy->key = calloc(1, sizeof(uint128_t));
	if (copy->key == NULL) {
		dprintf(STDERR_FILENO, "Erreur copy key\n");
		exit(EXIT_FAILURE);
	}
	*(copy->key) = *(bh->key);
	copy->degree = bh->degree + (more_child == true);
	copy->children = calloc(1, sizeof(binomh *) * copy->degree);
	if (copy->children == NULL) {
		dprintf(STDERR_FILENO, "Erreur copy children\n");
		exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < bh->degree; i++)
        	copy->children[i] = binomh_copy(bh->children[i], false);

	return copy;
}

static int powAB(int a , int k){
	int tmp = 1;
	for(int i = 0 ; i < k ; i++)
		tmp *= a;
	return tmp;
}

static bool is_nodeHeap(binomh *node) {
	if (node->degree > 0)
		for (size_t i = 0; i < node->degree - 1 ;i++) {
			binomh *child_1 = node->children[i];
			binomh *child_2 = node->children[i+1];

			if ((child_1->degree) > (child_2->degree))
				return false;
			if (inf(*(child_1->key), *(node->key)) && inf(*(child_2->key), *(node->key)))
				return false;
		}
	return true;
}

static bool is_binomT(binomh * tree) {
	// Un arbre vide est également considéré comme un tournoi binomial
	if (tree == NULL)
	        return true; 

	for (size_t i = 0 ; i < tree->degree ; i++) {
		if (is_nodeHeap(tree->children[i]))
			is_binomT(tree->children[i]);
		else
			return false;
	}
	return true;
}

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

binomh* binomh_create_empty() {
	binomh *bh = calloc(1, sizeof(binomh));
	if (bh == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc create bh empty");
		exit(EXIT_FAILURE);
	}
	return bh;
}

binomh* binomh_create(uint128_t k) {
	binomh *bh = calloc(1, sizeof(binomh));
	if (bh == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc binomh\n");
		exit(EXIT_FAILURE);
	}
	bh->key = calloc(1, sizeof(uint128_t));
	if (bh->key == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc key\n");
		exit(EXIT_FAILURE);
	}
	*(bh)->key = k;
	return bh;
}

bool binomh_is_empty(binomh *bh) {
	return bh == NULL || bh->key == NULL;
}

void binomh_print(binomh *bh) {
    pretty_rec(bh, 0, 0);
}

binomh* binomh_union(binomh *bh1, binomh *bh2) {
	binomh *uni = NULL;
	if (inf(*(bh1->key), *(bh2->key))) {
		bool bh2_not_empty = !binomh_is_empty(bh2);
		uni = binomh_copy(bh1, bh2_not_empty);
		if (bh2_not_empty)
			uni->children[uni->degree - 1] = binomh_copy(bh2, false);
	}
	else {
		bool bh1_not_empty = !binomh_is_empty(bh1);
		uni = binomh_copy(bh2, bh1_not_empty);
		if (bh1_not_empty)
			uni->children[uni->degree - 1] = binomh_copy(bh1, false);
	}
	return uni;
}

void binomh_free(binomh *bh) {
	if (bh == NULL)
		return;

	for (size_t i = 0; i < bh->degree; i++) {
		binomh_free(bh->children[i]);
	}

	free(bh->key);
	free(bh->children);
	free(bh);
}

binomh* binomh_createK(size_t k, uint128_t *list) {
	if (list == NULL) {
        	return NULL;
    	}

	size_t bh_size = powAB(2, k);
	binomh **bh_array = calloc(bh_size, sizeof(binomh*));

	for (size_t i = 0; i < bh_size; i++)
        	bh_array[i] = binomh_create(list[i]);

	while (bh_size > 1) {
        	size_t new_heap_size = bh_size / 2;
        	binomh **new_heap_array = calloc(new_heap_size, sizeof(binomh*));

        	for (size_t i = 0; i < new_heap_size; i++) {
        		if (2 * i + 1 < bh_size)
	                	new_heap_array[i] = binomh_union(bh_array[2 * i], bh_array[2 * i + 1]);
        		else
		                new_heap_array[i] = binomh_copy(bh_array[2 * i], false);
        	}

		for (size_t i = 0; i < bh_size; i++)
        		binomh_free(bh_array[i]);
		free(bh_array);
	        bh_array = new_heap_array;
        	bh_size = new_heap_size;
    	}
	binomh *result = bh_array[0];
    	free(bh_array);

    	return result;
}

bool isBinomialHeap(binomh *heap) {
	if(heap != NULL)
		// Si l'un des arbres n'est pas un tournoi binomial, retourne faux
        	if (!is_binomT(heap))
            		return false;
	return true; // Tous les arbres sont des tournois binomiaux
}

/* -------------------------------------------------------------------------- */
