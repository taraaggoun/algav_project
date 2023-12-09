

#include "../include/min_heap_tree.h"
#include "../include/min_heap_array.h"
#include "../test/test_utils.h"

#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "profiler.h"

#define MAX_KEY 200000
#define STEP    1000

void get_keys(const char *filename, uint128_t *keys, size_t size) {
	FILE *key_file = fopen(filename, "r");
	if (key_file == NULL) {
		dprintf(STDERR_FILENO, "Erreur fopen\n");
		exit(EXIT_FAILURE);
	}
	char key_str[BUF_UINT128_LEN_B16] = { 0 };
	for(size_t i = 0; i < size; i++) {
		memset(key_str, 0, BUF_UINT128_LEN_B16);
		if(!read_uint128(key_file, &(keys[i]), key_str)) {
			break;
		}
	}
}

void min_heap_tree_tests(void) {
	uint128_t keys_1[MAX_KEY] = { 0 };
	get_keys("test/cles_alea/jeu_5_nb_cles_200000.txt", keys_1, MAX_KEY);
	uint128_t keys_2[MAX_KEY] = { 0 };
	get_keys("test/cles_alea/jeu_5_nb_cles_200000.txt", keys_2, MAX_KEY);

	mhtree *mht_addi  = NULL;
	mhtree *mht_const = NULL;
	mhtree *mht_union = NULL;
	for (int i = 0; i < MAX_KEY; i+= STEP) {
		mhtree_ajout_iteratifs(keys_1, i, &mht_addi);
		mht_const = mhtree_construction(keys_2, i);
		mht_union = mhtree_union(mht_addi, mht_const, 2 * i);
		mhtree_free(mht_addi);
		mht_addi = NULL;
		mhtree_free(mht_const);
		mht_const = NULL;
		// mhtree_free(mht_union);
		mht_union = NULL;
	}
}

void min_heap_array_tests(void) {
	uint128_t keys_1[MAX_KEY] = { 0 };
	get_keys("test/cles_alea/jeu_1_nb_cles_1000.txt", keys_1, MAX_KEY);
	uint128_t keys_2[MAX_KEY] = { 0 };
	get_keys("test/cles_alea/jeu_2_nb_cles_1000.txt", keys_2, MAX_KEY);

	mharray mha_addi;
	mharray mha_const;
	mharray mha_union;
	for (int i = 0; i < MAX_KEY; i+= STEP) {
		constTabDyn(&mha_addi, i);
		mharray_ajout_iteratif(keys_1, i, &mha_addi);
		constTabDyn(&mha_const, i);
		for (int j = 0; j < i; j++)
			addElement(&mha_const, keys_2[j]);
		mharray_construction(&mha_const);

		mha_union = mharray_union(&mha_addi, &mha_const);
		freeTable(&mha_addi);
		freeTable(&mha_const);
		freeTable(&mha_union);
	}
}

int main(void) {
	printf("Debut calcul du temps d'execution pour min_heap_tree\n");

	BEGIN_PROFILE_SESSION("graph/ressource/min_heap_tree");
	min_heap_tree_tests();
	END_PROFILE_SESSION();

	printf("Fin calcul du temps d'execution pour min_heap_tree\n\n");

	printf("Debut calcul du temps d'execution pour min_heap_array\n");

	BEGIN_PROFILE_SESSION("graph/ressource/min_heap_array");
	min_heap_array_tests();
	END_PROFILE_SESSION();

	printf("Fin calcul du temps d'execution pour min_heap_array\n\n");
	return 0;
}
