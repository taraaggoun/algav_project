/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/uint128.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/binomial_heap.h"

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */


/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

// Crée le tas binomiale vide
binomh* create_bin_heap_empty() {
	binomh *bh = calloc(1, sizeof(binomh));
	if (bh == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc create bh empty");
		exit(EXIT_FAILURE);
	}
	return bh;
}

binomh* create_bin_heap(uint128_t k, int d, binomh *childs) {
	binomh *bh = create_bin_heap_empty();
	bh->childs = calloc(1, d * sizeof(binomh));
	if (bh->childs = NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc create bh node");
		exit(EXIT_FAILURE);
	}
	*(bh->key) = k;
	bh->degre = d;
	memcpy(bh->childs, childs, d * sizeof(binomh));
	return bh;
}

void free_bin_heap(binomh *bh) {
	if (bh == NULL)
		return;
	free_bin_heap(bh->childs);
	free(bh);
}

bool binh_is_empty(binomh *bh) {
	return bh == NULL || bh->key == NULL;
}

// TODO : faire la fonction
binomh* binomh_union(binomh *bh1, binomh *bh2) {
	if (binh_is_empty(bh1))
		return bh2;
	if (binh_is_empty(bh2))
		return bh1;
	binomh *res = malloc(sizeof(binomh));
	if (res == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc union");
		exit(EXIT_FAILURE);
	}
	res->childs = calloc(1, sizeof(binomh) * (bh1->degre + 1));
	*(res->key) = *(bh1->key);
	res->degre = bh1->degre;
	memcpy(res->childs, bh1->childs, bh1->degre * sizeof(binomh));
}

/* -------------------------------------------------------------------------- */
