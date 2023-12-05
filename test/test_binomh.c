/* -------------------------------- INCLUDE --------------------------------- */

#include "../include/binomial_heap.h"

#include "test_utils.h"

#include <string.h>

/* -------------------------------- DEFINES --------------------------------- */

#define NB_UINT128 2

/* ---------------------------------- MAIN ---------------------------------- */

int main(int argc, char *argv[]) {
	argument_manager(argc, argv);

	FILE *file = fopen(pathname, "r");
	if (file == NULL) {
		dprintf(STDERR_FILENO, "Erreur fopen\n");
		exit(EXIT_FAILURE);
	}

	uint128_t cle = { 0 };
	char cle_str[BUF_UINT128_LEN_B16] = { 0 };
	binomh *bh = binomh_create_empty();
	printf("Tournois Binomiale vide \n");
	binomh_print(bh);
	printf("\n");

	size_t i = NB_UINT128;
	while( i-- > 0 && read_uint128(file, &cle, cle_str)) {
		binomh *tmp = binomh_create(cle);
		binomh *uni = binomh_union(bh, tmp);
		binomh_free(tmp);
		binomh_free(bh);
		bh = NULL;
		bh = uni;
	}
	binomh_print(bh);

	// print_bst(bst);
	// printf("L'arbre est un abr ? %d\n", is_bst(bst));
	
	// bool exist = search_bst(bst, cle) != NULL;
	// printf("Es ce que %s appartient a l'arbre? %d \n", cle_str, exist);

	// printf("\nSuppression de %s\n", cle_str);
	// bst = supp_bst(bst, cle);
	// print_bst(bst);
	// printf("L'arbre est un abr ? %d\n", is_bst(bst));

	// exist = search_bst(bst, cle) != NULL;
	// printf("Es ce que %s appartient a l'arbre? %d \n", cle_str, exist);

	// binomh_free(bh);
	fclose(file);

	return 0;
}

/* -------------------------------------------------------------------------- */