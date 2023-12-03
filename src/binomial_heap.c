/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/uint128.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/binomial_heap.h"

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

// Crée le noeud d'un arbre binomiale
static binomh* create_bin_heap_node(uint128_t k) {
	binomh *bh = calloc(1, sizeof(binomh));
	if (bh == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc create bh node");
		exit(EXIT_FAILURE);
	}
	bh->key = k;
	bh->degre = 0;
	bh->childs = NULL;
	bh->siblings = NULL;

	return bh;
}

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

void free_bin_heap(binomh *bh) {
	if (bh == NULL)
		return;
	free_bin_heap(bh->childs);
	free_bin_heap(bh->siblings);
	free(bh);
}

/* -------------------------------------------------------------------------- */
