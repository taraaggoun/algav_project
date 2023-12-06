/* -------------------------------- INCLUDE --------------------------------- */

#include "../include/binomial_heap.h"

#include "test_utils.h"

#include <string.h>

/* -------------------------------- DEFINES --------------------------------- */

#define NB_UINT128 3

binomh* create_binomial_heap_from_uint128_recursive(FILE *file, size_t k, binomh *bh) {
    if (k == 0) {
        return bh;
    }

    uint128_t cle;
    char cle_str[BUF_UINT128_LEN_B16] = { 0 };
    read_uint128(file, &cle, cle_str);

    binomh *tmp = binomh_create(cle);

    // Vérifier si le tas à fusionner a le même degré que bh
    if (bh->degre != tmp->degre) {
        dprintf(STDERR_FILENO, "Erreur: Fusion avec un tas de degre different\n");
        binomh_free(tmp);
        return NULL;  // Retourne NULL pour indiquer une erreur
    }

    // Appeler récursivement la fonction pour le reste des tas
    binomh *result = create_binomial_heap_from_uint128_recursive(file, k - 1, bh);

    if (result == NULL) {
        binomh_free(tmp);
        return NULL;  // Retourne NULL pour indiquer une erreur
    }

    // Fusionner le résultat avec le nouveau tas
    binomh *uni = binomh_union(result, tmp);
    binomh_free(result);
    binomh_free(tmp);

    return uni;
}




binomh* create_binomial_heap_from_uint128(FILE *file, size_t k) {
    uint128_t cle;
    char cle_str[BUF_UINT128_LEN_B16] = { 0 };

    // Lire le premier uint128
    read_uint128(file, &cle, cle_str);

    // Créer un binomial heap avec le premier uint128
    binomh *bh = binomh_create(cle);

    // Appeler la fonction récursive pour créer le reste des tas et les fusionner
    return create_binomial_heap_from_uint128_recursive(file, k - 1, bh);
}



/* ---------------------------------- MAIN ---------------------------------- */

int main(int argc, char *argv[]) {
	argument_manager(argc, argv);

	FILE *file = fopen(pathname, "r");
	if (file == NULL) {
		dprintf(STDERR_FILENO, "Erreur fopen\n");
		exit(EXIT_FAILURE);
	}

	binomh *bh = create_binomial_heap_from_uint128(file, NB_UINT128);
	binomh_print(bh);
	// size_t i = NB_UINT128;
	// while (i-- > 0) {
	// 	binomh *bh2 = create_binomial_heap_from_uint128()
	// }

	binomh_free(bh);
	fclose(file);

	return 0;
}

/* -------------------------------------------------------------------------- */