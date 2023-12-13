/* -------------------------------- INCLUDE --------------------------------- */

#include "../include/binomial_heap.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "test_utils.h"

/* -------------------------------- DEFINE ---------------------------------- */

#define NB_UINT128 5

/* ---------------------------------- MAIN ---------------------------------- */

int main(int argc, char *argv[]) {
	argument_manager(argc, argv);

	FILE *file = fopen(pathname, "r");
	if (file == NULL) {
		dprintf(STDERR_FILENO, "Erreur fopen\n");
		exit(EXIT_FAILURE);
	}

	uint128_t *keys = malloc(pow(2, NB_UINT128) * sizeof(uint128_t));
	
	int i = 0;
	uint128_t cle = { 0 };
	char cle_str[BUF_UINT128_LEN_B16] = { 0 };

	// Ajoute dans keys 2 puissance nb_uint128 cles
	while(i < pow(2, NB_UINT128)) {
		if (read_uint128(file, &cle, cle_str) == 0)
			break;
		keys[i] = cle;
		i++;
	}

	binomh *uni = binomh_createK(NB_UINT128, keys);

	binomh_print(uni);
	printf("\n");

	if (isBinomialHeap(uni))
		printf("\nest un tournoi\n");
	else
		printf("\nn'est pas un tournoi\n");

	// Liberation de la memoire
	binomh_free(uni);
	free(keys);
	fclose(file);

	return 0;
}

/* -------------------------------------------------------------------------- */

// int main() {
// 	binomh *b = binomh_create(5);
// 	binomh_print(b);
// 	binomh *b2 = binomh_copy(b, false);
// 	binomh_print(b2);
// 	binomh *uni = binomh_union(b, b2);
// 	binomh_print(uni);
// 	binomh_free(b);
// 	binomh_free(b2);
// 	binomh_free(uni);

// 	size_t k = 3;
// 	size_t list[] = {1, 5, 8, 3, 2, 7, 6, 4};

// 	binomh *result_heap = binomh_createK(k, list);
// 	printf("%d\n", isBinomialHeap(result_heap));
// 	binomh_print(result_heap);
// 	binomh_free(result_heap);
// 	return 0;
// }