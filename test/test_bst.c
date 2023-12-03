/* -------------------------------- INCLUDE --------------------------------- */

#include "../include/binary_search_tree.h"

#include "test_utils.h"

#include <string.h>

/* -------------------------------- DEFINES --------------------------------- */

#define NB_UINT128 10

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
	bst *bst = create_bst_empty();
	print_bst(bst);
	printf("L'arbre est un abr ? %d\n", is_bst(bst));


	size_t i = NB_UINT128;
	printf("\nAjout de %ld valeur dans l'arbre\n", i);
	while( i-- > 0 && read_uint128(file, &cle, cle_str)) {
		bst = add_bst(cle, bst);
	}

	print_bst(bst);
	printf("L'arbre est un abr ? %d\n", is_bst(bst));
	
	bool exist = search_bst(bst, cle) != NULL;
	printf("Es ce que %s appartient a l'arbre? %d \n", cle_str, exist);

	printf("\nSuppression de %s\n", cle_str);
	bst = supp_bst(bst, cle);
	print_bst(bst);
	printf("L'arbre est un abr ? %d\n", is_bst(bst));

	exist = search_bst(bst, cle) != NULL;
	printf("Es ce que %s appartient a l'arbre? %d \n", cle_str, exist);

	free_bst(bst);
	fclose(file);

	return 0;
}

/* -------------------------------------------------------------------------- */