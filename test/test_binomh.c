/* -------------------------------- INCLUDE --------------------------------- */

#include "../include/binomial_heap.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "test_utils.h"

/* -------------------------------- DEFINE ---------------------------------- */

#define NB_UINT128 1

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

	while(i < pow(2, NB_UINT128)) {
		if (read_uint128(file, &cle, cle_str) == 0)
			break;
		keys[i] = cle;
		i++;
	}

	binomh *uni = binomK_create(keys,NB_UINT128);

	binomh_print(uni);
	printf("\n");

	if (isBinomialHeap(uni))
		printf("\nest un tournoi\n");
	else
		printf("\nn'est pas un tournoi\n");

	free(keys);
	binomh_free(uni);
	fclose(file);
	return 0;
}

/* -------------------------------------------------------------------------- */
