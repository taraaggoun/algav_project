/* -------------------------------- INCLUDES -------------------------------- */

#include "test_utils.h"
#include "../include/min_heap_tree.h"

/* -------------------------------- DEFINES --------------------------------- */

#define NB_UINT128 490

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

/**
 * Rempli un tableau de valeur
**/
static uint128_t *create_tab(size_t *len, FILE *file) {
	uint128_t *tab = (uint128_t*) malloc(sizeof(uint128_t) * (*len));
	size_t i = 0;
	uint128_t cle = { 0 };
	char cle_str[BUF_UINT128_LEN_B16] = { 0 };
	while(read_uint128(file, &cle, cle_str)  && i < NB_UINT128) {
		tab[i] = cle;
		i ++;
		if (i >= *len) 
			tab = realloc(tab, 2 * i * sizeof(uint128_t));
	}
	*len = i;
	return tab;
}

// Fonction de test
// void affiche(mhtree *h) {
// 	if (h == NULL)
// 		return;
// 	printf("-------------------------------------------------\n");
// 	printf("key    : %lu \n", h->key->low);
// 	if (h->parent != NULL)
// 		printf("parent : %lu \n", h->parent->key->low);
// 	if (h->empty_leaf_parent != NULL)
// 		printf("empty  :%lu \n", h->empty_leaf_parent->key->low);
// 	if (h->last_leaf != NULL)
// 		printf("last   :%lu \n", h->last_leaf->key->low);
// 	affiche(h->left);
// 	affiche(h->right);
// }

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

int main(int argc, char *argv[]) {
	argument_manager(argc, argv);
	
	FILE *file = fopen(pathname, "r");
	if (file == NULL) {
		dprintf(STDERR_FILENO, "Erreur fopen\n");
		exit(EXIT_FAILURE);
	}

	uint128_t cle = { 0 };
	char cle_str[BUF_UINT128_LEN_B16] = { 0 };

	// Creation d'un tas vide
	printf("Creation du tas vide: \n");
	mhtree *mht = mhtree_empty();
	mhtree_print(mht);
	printf("l'arbre est il un tas? %d \n", is_mhtree(mht));
	printf("le tas est il vide ? %d \n", mhtree_is_empty(mht));
	printf("\n");

	if (read_uint128(file, &cle, cle_str) == 0) {
		dprintf(STDERR_FILENO, "fichier vide \n");
		exit(EXIT_FAILURE);
	}

	// Ajout dans un tas
	printf("Ajout du %s dans le tas: \n", cle_str);
	mhtree_ajout(cle, &mht);
	mhtree_print(mht);
	printf("l'arbre est il un tas? %d \n", is_mhtree(mht));
	printf("le tas est il vide ? %d \n", mhtree_is_empty(mht));

	// Ajout iteratif
	size_t tab1_len = NB_UINT128;
	uint128_t *tab1 = create_tab(&tab1_len, file);
	printf("\nAjout de %ld cles dans le tas: \n", tab1_len);
	mhtree_ajout_iteratifs(tab1, NB_UINT128, &mht);
	mhtree_print(mht);
	printf("l'arbre est il un tas? %d \n", is_mhtree(mht));

	// Construction
	size_t tab2_len = NB_UINT128;
	uint128_t *tab2 = create_tab(&tab2_len, file);
	printf("\nConstruction d'un tas a %ld element\n", tab2_len);
	mhtree *mht_cons = mhtree_construction(tab2, tab2_len);
	mhtree_print(mht_cons);
	printf("l'arbre est il un tas? %d \n", is_mhtree(mht_cons));

	// Union
	printf("\nUnion des tas\n");
	mhtree *mht_union = mhtree_union(mht, mht_cons, -1);
	mhtree_print(mht_union);
	printf("l'arbre est il un tas? %d \n", is_mhtree(mht_union));

	// Suppression du min
	uint128_t supp = mhtree_suppr_min(&mht_union, -1);
	char supp_str[BUF_UINT128_LEN_B16] = { 0 };
	uint128_to_str(supp, supp_str, BUF_UINT128_LEN_B10);
	printf("\nSuppression du min: %s\n", supp_str);
	mhtree_print(mht_union);
	printf("l'arbre est il un tas? %d \n", is_mhtree(mht_union));

	supp = mhtree_suppr_min(&mht_union, -1);
	uint128_to_str(supp, supp_str, BUF_UINT128_LEN_B10);
	printf("\nSuppression du min: %s\n", supp_str);
	mhtree_print(mht_union);
	printf("l'arbre est il un tas? %d \n", is_mhtree(mht_union));

	if (read_uint128(file, &cle, cle_str) == 0) {
		dprintf(STDERR_FILENO, "fichier vide \n");
		exit(EXIT_FAILURE);
	}

	// Ajout dans un tas
	printf("\nAjout du %s dans le tas: \n", cle_str);
	mhtree_ajout(cle, &mht_union);
	mhtree_print(mht_union);
	printf("l'arbre est il un tas? %d \n", is_mhtree(mht_union));

	// Liberation de la memoire
	free(tab1);
	free(tab2);
	mhtree_free(mht);
	mhtree_free(mht_cons);
	mhtree_free(mht_union);
	fclose(file);
	return 0;
}

/* -------------------------------------------------------------------------- */