/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/binary_search_tree.h"

#include <string.h>

#include "test_utils.h"

/* -------------------------------- DEFINE ---------------------------------- */

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
	bst *bst = bst_create_empty();
	bst_print(bst);
	printf("L'arbre est un abr ? %d\n", is_bst(bst));


	size_t i = NB_UINT128;
	printf("\nAjout de %ld valeur dans l'arbre\n", i);
	while( i-- > 0 && read_uint128(file, &cle, cle_str)) {
		bst = bst_add(cle, bst);
	}
	bst_add_word(&bst, "test", cle);

	bst_print(bst);
	printf("L'arbre est un abr ? %d\n", is_bst(bst));

	struct binary_search_tree *s = bst_search(bst, cle);
	bool exist = s != NULL;
	printf("Es ce que %s appartient a l'arbre? %d \n", cle_str, exist);
	printf("word = %s\n", s->words.name);
	printf("next is null ? %d\n", s->words.next == NULL);
	bst_add_word(&bst, "test2", cle);
	printf("word = %s\n", s->words.name);
	printf("word = %s\n", s->words.next->name);
	printf("next is null ? %d\n", s->words.next->next == NULL);

	printf("\nSuppression de %s\n", cle_str);
	bst = bst_supp(bst, cle);
	bst_print(bst);
	printf("L'arbre est un abr ? %d\n", is_bst(bst));

	exist = bst_search(bst, cle) != NULL;
	printf("Es ce que %s appartient a l'arbre? %d \n", cle_str, exist);


	bst_free(bst);
	fclose(file);

	return 0;
}

/* -------------------------------------------------------------------------- */